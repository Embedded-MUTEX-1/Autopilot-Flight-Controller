#include "telemetryModule.h"
#include "../../devices-interfaces/telemetry/Telemetry.h"
#include "../../devices-interfaces/telemetry/WirelessInterface.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"

void telemtryTask(void *args) {
    Telemetry telemtry;
    // Drone -> Telemetry
    struct receiverData receiverValues;
    struct attitudeData attitudeValues;
    struct positionData positionValues;
    struct altitudeData altitudeValues;
    struct motorsData motorsValues;
    struct pidOutput pidOutputValues;
    struct commanderState state;

    // Telemetry -> Drone
    struct navigationSetpoint navSetpointValues;
    struct motorsSetpoint motorsSetpointValues;
    struct attitudeConfig attitudeConfValues = {
        OFFSET_ROLL, OFFSET_PITCH, OFFSET_YAW, 
        0, 
        PARAM_1, PARAM_2, 
        false};
    struct pidConfig pidConfValues {
        P_ROLL_PITCH, P_ROLL_PITCH, P_YAW,
        I_ROLL_PITCH, I_ROLL_PITCH, I_YAW,
        D_ROLL_PITCH, D_ROLL_PITCH, D_YAW,
        false
    };
    struct pidNavigationConfig pidNavConfValues {
        P_NAV, I_NAV, D_NAV,
        0, 0,
        0, 0,
        false
    };
    struct pidAltitudeConfig pidAltConfValues {
        P_ALT, I_ALT, D_ALT,
        false
    };
    struct commanderState stateConf;
    
    uint64_t timestamp(0), loopPeriod(0);
    bool isFirstDataReceived = false;

    if(telemtry.init() != 0)
        while(1) { delay_milis(100); }

    while (!telemtry.isConfigDataAvailable());
    
    telemtry.sendConfigValues(
        attitudeConfValues,
        pidConfValues,
        pidAltConfValues,
        pidNavConfValues
    );

    while(1) {
        timestamp = get_ms_count();

        receiverNode.get(receiverValues);
        attitudeNode.get(attitudeValues);
        positionNode.get(positionValues);
        altitudeNode.get(altitudeValues);
        motorsNode.get(motorsValues);
        commanderStateNode.get(state);

        telemtry.sendTelemetryValues(
            attitudeValues, 
            altitudeValues, 
            positionValues, 
            pidOutputValues, 
            receiverValues, 
            motorsValues, 
            state, 
            timestamp);

        if(telemtry.isConfigDataAvailable()) {
            if(telemtry.getConfigData(
                &attitudeConfValues,
                &pidConfValues,
                &pidAltConfValues,
                &pidNavConfValues,
                &motorsSetpointValues,
                &navSetpointValues,
                &stateConf
            ) == 0) 
            {
                if(state.state == droneState::DISARMED && state.state == droneState::MANU) {
                    attitudeConfigNode.set(attitudeConfValues);
                    pidConfigNode.set(pidConfValues);
                    pidAltConfigNode.set(pidAltConfValues);
                    pidNavConfigNode.set(pidNavConfValues);
                    motorsConfigNode.set(motorsSetpointValues);
                    commanderStateConfNode.set(stateConf);
                } else if(state.state == droneState::NAVIGATION) {
                    navigationSetpointNode.set(navSetpointValues);
                }
            }
        }

        loopPeriod = get_ms_count() - timestamp;
        wait(loopPeriod, TELEMETRY_LOOP_FREQ);
    }
}