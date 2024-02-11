//
// Created by lenny on 28/01/24.
//

#include "navigationModule.h"
#include "../../devices-interfaces/low-level/UartDevice.h"
#include "../../devices-interfaces/gps/Gps.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"
#include "../../../lib/QuickPID/src/QuickPID.h"

void navigationTask(void *args) {
    UartDevice uart;
    Gps gps(&uart);

    struct positionData values;
    struct commanderState state;
    struct pidNavigationConfig config;
    struct navigationSetpoint setpoint;
    struct pidSetpoint anglesSetpoint;
    
    QuickPID latitudePid;
    QuickPID longitudePid;

    uint64_t timestamp = 0;

    uart.init(GPS_UART_PORT, GPS_UART_TX, GPS_UART_RX, GPS_UART_BAUD);
    if(gps.init() != 0)
        while(1) { delay_milis(100); }

    latitudePid.SetSampleTimeUs((1 / NAVIGATION_LOOP_FREQ) * 1000);
    longitudePid.SetSampleTimeUs((1 / NAVIGATION_LOOP_FREQ) * 1000);

    latitudePid.SetTunings(P_NAV, I_NAV, D_NAV);
    longitudePid.SetTunings(P_NAV, I_NAV, D_NAV);

    latitudePid.SetOutputLimits(-MAX_NAV_ANGLE, MAX_NAV_ANGLE);
    longitudePid.SetOutputLimits(-MAX_NAV_ANGLE, MAX_NAV_ANGLE);

    while(1) {
        timestamp = get_ms_count();

        commanderStateNode.get(state);
        pidNavConfigNode.get(config);
        gps.updateAndGetData(values);

        if(state.state == droneState::LEVEL) {
            setpoint.lat = values.lat;
            setpoint.lon = values.lon;
        } else if(state.state == droneState::NAVIGATION) {
            navigationSetpointNode.get(setpoint);
        }

        if(config.newConfig) {
            latitudePid.SetTunings(config.pnav, config.inav, config.dnav);
            longitudePid.SetTunings(config.pnav, config.inav, config.dnav);

            latitudePid.Reset();
            longitudePid.Reset();

            config.newConfig = false;
        }

        if(state.state == droneState::NAVIGATION || state.state == droneState::POS_HOLD) {
            // TODO à modifier (ajuster au nord)
            anglesSetpoint.pitch = latitudePid.Compute(setpoint.lat * LAT_LON_PRECISION, values.lat * LAT_LON_PRECISION);
            anglesSetpoint.roll = longitudePid.Compute(setpoint.lon * LAT_LON_PRECISION, values.lon * LAT_LON_PRECISION);

            pidSetpointNode.set(anglesSetpoint);
        }

        positionNode.set(values);

        values.loopPeriod = get_ms_count() - timestamp;
        wait(values.loopPeriod, NAVIGATION_LOOP_FREQ);
    }
}