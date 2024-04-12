#include "ControllerModule.h"

ControllerModule::ControllerModule() {
    rateRollPid = FastPID(P_ROLL_PITCH, I_ROLL_PITCH, D_ROLL_PITCH, PID_LOOP_FREQ, 16, true);
    ratePitchPid = FastPID(P_ROLL_PITCH, I_ROLL_PITCH, D_ROLL_PITCH, PID_LOOP_FREQ, 16, true);
    rateYawPid = FastPID(P_YAW, I_YAW, D_YAW, PID_LOOP_FREQ, 16, true);
    altitudePid = FastPID(P_ALT, I_ALT, D_ALT, PID_LOOP_FREQ, 16, true);

    pidConfigNode.addCallback([this](struct pidConfig pidConfValues) -> void {
        rateRollPid.setCoefficients(pidConfValues.proll, pidConfValues.iroll, pidConfValues.droll, PID_LOOP_FREQ);
        ratePitchPid.setCoefficients(pidConfValues.ppitch, pidConfValues.ipitch, pidConfValues.dpitch, PID_LOOP_FREQ);
        rateYawPid.setCoefficients(pidConfValues.pyaw, pidConfValues.iyaw, pidConfValues.dyaw, PID_LOOP_FREQ);

        rateRollPid.clear();
        ratePitchPid.clear();
        rateYawPid.clear();
    });

    pidAltConfigNode.addCallback([this](struct pidAltitudeConfig pidAltConfValues) -> void {
        altitudePid.setCoefficients(pidAltConfValues.pAltitude, pidAltConfValues.iAltitude, pidAltConfValues.dAltitude, PID_LOOP_FREQ);
        altitudePid.clear();
    });
}

int8_t ControllerModule::init() {
    rateRollPid.setOutputRange(-400, 400);
    ratePitchPid.setOutputRange(-400, 400);
    rateYawPid.setOutputRange(-400, 400);
    altitudePid.setOutputRange(-400, 400);

    return 0;
}

void ControllerModule::run() {
    timestamp = get_ms_count();

    getDataFromNodes();
    computeSetpoints();
    processStateFromCommander();
    computeOutputValuesAndSendValuesToNode();

    values.loopPeriod = get_ms_count() - timestamp;
    wait(values.loopPeriod, PID_LOOP_FREQ);
}

void ControllerModule::getDataFromNodes() {
    pidSetpointNode.get(anglesSetpoint);
    commanderStateNode.get(state);
    attitudeNode.get(attitudeValues);
    altitudeNode.get(altitudeValues);
    receiverNode.get(receiverValues);
}

void ControllerModule::computeSetpoints() {
    rollRateSetpoint = (anglesSetpoint.roll  - attitudeValues.roll)  * 5.0f;
    pitchRateSetpoint = (anglesSetpoint.pitch - attitudeValues.pitch) * 5.0f;
    verticalSpeedSetpoint = (altitudeSetpoint - altitudeValues.alt) * 2.0f;
}

void ControllerModule::processStateFromCommander() {
    if(state.state == LEVEL) {
        if(receiverValues.chan[YAW_CHAN] < MAX_YAW_CHAN_THRESHOLD && receiverValues.chan[YAW_CHAN] > MIN_YAW_CHAN_THRESHOLD) {
            attitudeValues.yaw -= offsetYaw;
            yawRateSetpoint = (0 - attitudeValues.yaw) * 5.0f;
        } else {
            offsetYaw = attitudeValues.yaw;
            yawRateSetpoint = anglesSetpoint.yawRate;
        }
        altitudeSetpoint = altitudeValues.alt;
    } else if(state.state == NAVIGATION || state.state == POS_HOLD) {
        attitudeValues.yaw -= offsetYaw;
        yawRateSetpoint = (0 - attitudeValues.yaw) * 5.0f;
    } else if(state.state == DISARMED) {
        rateRollPid.clear();
        ratePitchPid.clear();
        rateYawPid.clear();
        offsetYaw = attitudeValues.yaw;
    }
}

void ControllerModule::computeOutputValuesAndSendValuesToNode() {
    values.out_roll  = rateRollPid.step(rollRateSetpoint, attitudeValues.gyroRateRoll);
    values.out_pitch = ratePitchPid.step(pitchRateSetpoint, attitudeValues.gyroRatePitch);
    values.out_yaw   = rateYawPid.step(yawRateSetpoint, attitudeValues.gyroRateYaw);
    // values.out_alt   = state.state == POS_HOLD ? altitudePid.step(verticalSpeedSetpoint, altitudeValues.vertical_speed) : 0;
    values.out_alt   = 0;
    if(abs(altitudeSetpoint - altitudeValues.alt) <= ALTITUDE_ATTENUATOR_THRESOLD)
        values.out_alt /= ALTITUDE_ATTENUATOR_VALUE;

    pidOutputNode.set(values);
}
