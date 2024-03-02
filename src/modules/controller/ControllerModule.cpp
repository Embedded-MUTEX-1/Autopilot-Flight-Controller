#include "ControllerModule.h"

ControllerModule::ControllerModule() {
    pidConfigNode.addCallback([this](struct pidConfig pidConfValues) -> void {
        rateRollPid.SetTunings(pidConfValues.proll, pidConfValues.iroll, pidConfValues.droll);
        ratePitchPid.SetTunings(pidConfValues.ppitch, pidConfValues.ipitch, pidConfValues.dpitch);
        rateYawPid.SetTunings(pidConfValues.pyaw, pidConfValues.iyaw, pidConfValues.dyaw);
    });

    pidAltConfigNode.addCallback([this](struct pidAltitudeConfig pidAltConfValues) -> void {
        altitudePid.SetTunings(pidAltConfValues.pAltitude, pidAltConfValues.iAltitude, pidAltConfValues.dAltitude);
    });
}

int8_t ControllerModule::init() {
    rateRollPid.SetTunings(P_ROLL_PITCH, I_ROLL_PITCH, D_ROLL_PITCH);
    ratePitchPid.SetTunings(P_ROLL_PITCH, I_ROLL_PITCH, D_ROLL_PITCH);
    rateYawPid.SetTunings(P_YAW, I_YAW, D_YAW);
    altitudePid.SetTunings(P_ALT, I_ALT, D_ALT);

    rateRollPid.SetSampleTimeUs((1 / PID_LOOP_FREQ) * 1000);
    ratePitchPid.SetSampleTimeUs((1 / PID_LOOP_FREQ) * 1000);
    rateYawPid.SetSampleTimeUs((1 / PID_LOOP_FREQ) * 1000);
    altitudePid.SetSampleTimeUs((1 / PID_LOOP_FREQ) * 1000);

    rateRollPid.SetOutputLimits(-400, 400);
    ratePitchPid.SetOutputLimits(-400, 400);
    rateYawPid.SetOutputLimits(-400, 400);
    altitudePid.SetOutputLimits(-400, 400);

    return 0;
}

void ControllerModule::run() {
    timestamp = get_ms_count();

    getDataFromNodes();
    computeSetpointAngleRate();
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

void ControllerModule::computeSetpointAngleRate() {
    rollRateSetpoint = (anglesSetpoint.roll  - attitudeValues.roll)  * 5.0f;
    pitchRateSetpoint = (anglesSetpoint.pitch - attitudeValues.pitch) * 5.0f;
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
        rateRollPid.Reset();
        ratePitchPid.Reset();
        rateYawPid.Reset();
        offsetYaw = attitudeValues.yaw;
    }
}

void ControllerModule::computeOutputValuesAndSendValuesToNode() {
    values.out_roll  = rateRollPid.Compute(rollRateSetpoint, attitudeValues.gyroRateRoll);
    values.out_pitch = ratePitchPid.Compute(pitchRateSetpoint, attitudeValues.gyroRatePitch);
    values.out_yaw   = rateYawPid.Compute(yawRateSetpoint, attitudeValues.gyroRateYaw);
    values.out_alt   = altitudePid.Compute(altitudeSetpoint, altitudeValues.alt);
    pidOutputNode.set(values);
}
