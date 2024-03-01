//
// Created by lenny on 28/01/24.
//

#include "NavigationModule.h"

NavigationModule::NavigationModule()
{
    pidNavConfigNode.addCallback([this](struct pidNavigationConfig config) -> void {
        this->latitudePid.SetTunings(config.pnav, config.inav, config.dnav);
        this->longitudePid.SetTunings(config.pnav, config.inav, config.dnav);

        this->latitudePid.Reset();
        this->longitudePid.Reset();
    });
}

int8_t NavigationModule::init()
{
    if(gps.init() != 0)
        return -1;

    latitudePid.SetSampleTimeUs((1 / NAVIGATION_LOOP_FREQ) * 1000);
    longitudePid.SetSampleTimeUs((1 / NAVIGATION_LOOP_FREQ) * 1000);

    latitudePid.SetTunings(P_NAV, I_NAV, D_NAV);
    longitudePid.SetTunings(P_NAV, I_NAV, D_NAV);

    latitudePid.SetOutputLimits(-MAX_NAV_ANGLE, MAX_NAV_ANGLE);
    longitudePid.SetOutputLimits(-MAX_NAV_ANGLE, MAX_NAV_ANGLE);

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
        anglesSetpoint.pitch = latitudePid.Compute(setpoint.lat * LAT_LON_PRECISION, values.lat * LAT_LON_PRECISION);
        anglesSetpoint.roll = longitudePid.Compute(setpoint.lon * LAT_LON_PRECISION, values.lon * LAT_LON_PRECISION);

        pidSetpointNode.set(anglesSetpoint);
    }
    positionNode.set(values);
}
