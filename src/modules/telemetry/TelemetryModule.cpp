#include "TelemetryModule.h"

TelemetryModule::TelemetryModule() {
    attitudeConfValues = {
        OFFSET_ROLL, OFFSET_PITCH, OFFSET_YAW, 
        0, 
        PARAM_1, PARAM_2, 
        false};
    pidConfValues = {
        P_ROLL_PITCH, P_ROLL_PITCH, P_YAW,
        I_ROLL_PITCH, I_ROLL_PITCH, I_YAW,
        D_ROLL_PITCH, D_ROLL_PITCH, D_YAW,
        false
    };
    pidNavConfValues = {
        P_NAV, I_NAV, D_NAV,
        0, 0,
        0, 0,
        false
    };
    pidAltConfValues = {
        P_ALT, I_ALT, D_ALT,
        false
    };
    stateConf = { LEVEL };

    timestamp = 0;
    loopPeriod = 0;
    count = 0;
}

int8_t TelemetryModule::init() {
    commanderStateConfNode.set(stateConf);

    if(telemetry.init() != 0)
        return -1;

    while (!telemetry.isConfigDataAvailable()); //Wait for first data from ground station
    telemetry.resetRecvBuffer();

    sendConfigValues();
    return 0;
}

void TelemetryModule::run() {
    timestamp = get_ms_count();

    getDataFromNodes();
    sendTelemetryValues();
    processDataFromGroundStation();

    loopPeriod = get_ms_count() - timestamp;

    if(state.state != DISARMED) {
        count++;
    }

    wait(loopPeriod, TELEMETRY_LOOP_FREQ);
}

void TelemetryModule::sendConfigValues() {
    telemetry.sendConfigValues(
        attitudeConfValues,
        pidConfValues,
        pidAltConfValues,
        pidNavConfValues
    );
}

void TelemetryModule::getDataFromNodes() {
    receiverNode.get(receiverValues);
    attitudeNode.get(attitudeValues);
    positionNode.get(positionValues);
    altitudeNode.get(altitudeValues);
    motorsNode.get(motorsValues);
    commanderStateNode.get(state);
    pidOutputNode.get(pidOutputValues);
}

void TelemetryModule::sendTelemetryValues() {
    telemetry.sendTelemetryValues(
        attitudeValues, 
        altitudeValues, 
        positionValues, 
        pidOutputValues, 
        receiverValues, 
        motorsValues, 
        state, 
        count / TELEMETRY_LOOP_FREQ,
        loopPeriod);
}

void TelemetryModule::processDataFromGroundStation() {
    if(telemetry.isConfigDataAvailable()) {
        if(telemetry.getConfigData(
            &attitudeConfValues,
            &pidConfValues,
            &pidAltConfValues,
            &pidNavConfValues,
            &motorsSetpointValues,
            &navSetpointValues,
            &stateConf
        ) == 0) 
        {
            setDataToNodes();
        } else {
            sendConfigValues();
        }
    }
}

void TelemetryModule::setDataToNodes() {
    if(state.state == droneState::DISARMED || state.state == droneState::MANU) {
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