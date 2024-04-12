//
// Created by lenny on 28/01/24.
//

#include "NavigationModule.h"

NavigationModule::NavigationModule()
{
    latitudePid = FastPID(P_NAV, I_NAV, D_NAV, NAVIGATION_LOOP_FREQ, 16, true);
    longitudePid = FastPID(P_NAV, I_NAV, D_NAV, NAVIGATION_LOOP_FREQ, 16, true);
    pidNavConfigNode.addCallback([this](struct pidNavigationConfig config) -> void {
        this->latitudePid.setCoefficients(config.pnav, config.inav, config.dnav, NAVIGATION_LOOP_FREQ);
        this->longitudePid.setCoefficients(config.pnav, config.inav, config.dnav, NAVIGATION_LOOP_FREQ);

        this->latitudePid.clear();
        this->longitudePid.clear();
    });
}

int8_t NavigationModule::init()
{
    if(gps.init() != 0)
        return -1;

    latitudePid.setOutputRange(-MAX_NAV_ANGLE, MAX_NAV_ANGLE);
    longitudePid.setOutputRange(-MAX_NAV_ANGLE, MAX_NAV_ANGLE);

    return 0;
}

void NavigationModule::run()
{
    timestamp = get_ms_count();

    getDataFromNodesAndGps();
    processDataAndSetToNodes();

    values.loopPeriod = get_ms_count() - timestamp;
    wait(values.loopPeriod, NAVIGATION_LOOP_FREQ);
}

void NavigationModule::getDataFromNodesAndGps()
{
    commanderStateNode.get(state);
    gps.updateAndGetData(values);

    if(state.state == droneState::LEVEL) {
        setpoint.lat = values.lat;
        setpoint.lon = values.lon;
    } else if(state.state == droneState::NAVIGATION) {
        navigationSetpointNode.get(setpoint);
    }
}

void NavigationModule::processDataAndSetToNodes()
{
    if(state.state == droneState::NAVIGATION || state.state == droneState::POS_HOLD) {
        // TODO à modifier (ajuster au nord)
        anglesSetpoint.pitch = latitudePid.step(int16_t(setpoint.lat * LAT_LON_PRECISION), int16_t(values.lat * LAT_LON_PRECISION));
        anglesSetpoint.roll = longitudePid.step(int16_t(setpoint.lon * LAT_LON_PRECISION), int16_t(values.lon * LAT_LON_PRECISION));

        pidSetpointNode.set(anglesSetpoint);
    }
    positionNode.set(values);
}
