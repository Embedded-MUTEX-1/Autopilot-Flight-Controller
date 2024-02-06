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
    gps.init();

    latitudePid.SetSampleTimeUs(1 / NAVIGATION_LOOP_FREQ);
    longitudePid.SetSampleTimeUs(1 / NAVIGATION_LOOP_FREQ);

    latitudePid.SetTunings(P_NAV, I_NAV, D_NAV);
    longitudePid.SetTunings(P_NAV, I_NAV, D_NAV);

    latitudePid.SetOutputLimits(-MAX_NAV_ANGLE, MAX_NAV_ANGLE);
    longitudePid.SetOutputLimits(-MAX_NAV_ANGLE, MAX_NAV_ANGLE);

    while(1) {
        timestamp = get_ms_count();

        commanderStateNode.get(state);
        pidNavConfigNode.get(config);
        navigationSetpointNode.get(setpoint);
        gps.updateAndGetData(values);

        if(config.newConfig) {
            latitudePid.SetTunings(config.pnav, config.inav, config.dnav);
            longitudePid.SetTunings(config.pnav, config.inav, config.dnav);

            latitudePid.Reset();
            longitudePid.Reset();

            config.newConfig = false;
        }

        if(state.state == droneState::NAVIGATION || state.state == droneState::POS_HOLD) {
            // TODO à modifier
            anglesSetpoint.pitch = latitudePid.Compute(setpoint.lat * 1e6, values.lat * 1e6);
            anglesSetpoint.roll = longitudePid.Compute(setpoint.lon * 1e6, values.lon * 1e6);

            pidSetpointNode.set(anglesSetpoint);
        }

        positionNode.set(values);

        values.loopPeriod = get_ms_count() - timestamp;
    }
}