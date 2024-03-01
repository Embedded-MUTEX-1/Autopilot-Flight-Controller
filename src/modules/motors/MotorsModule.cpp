//
// Created by lenny on 28/01/24.
//

#include "MotorsModule.h"

MotorsModule::MotorsModule() {

}

int8_t MotorsModule::init() {
    if(motors.init() != 0)
        return -1;

    vBatPin.init();
    vBatPin.initPin(VBAT_PIN);
    return 0;
}

void MotorsModule::run() {
    timestamp = get_ms_count();

    getDataFromNodesAndSensor();
    computeMotorsValues();
    processStateFromCommander();
    sendValuesToMotorsAndNodes();

    values.loopPeriod = get_ms_count() - timestamp;
    wait(values.loopPeriod, MOTORS_LOOP_FREQ);
}

void MotorsModule::getDataFromNodesAndSensor() {
    pidOutputNode.get(pidValues);
    commanderStateNode.get(state);
    receiverNode.get(receiverValues);
    values.vBat = vBatPin.getValue(VBAT_PIN) * (3.3f / 4095.0f) * 13.631f;
}

void MotorsModule::computeMotorsValues() {
#if NUMBER_OF_MOTORS == 4
    setpoint.mot[0] = receiverValues.chan[THROTTLE_CHAN] + pidValues.out_roll - pidValues.out_pitch - pidValues.out_yaw + pidValues.out_alt;
    setpoint.mot[1] = receiverValues.chan[THROTTLE_CHAN] - pidValues.out_roll - pidValues.out_pitch + pidValues.out_yaw + pidValues.out_alt;
    setpoint.mot[2] = receiverValues.chan[THROTTLE_CHAN] + pidValues.out_roll + pidValues.out_pitch + pidValues.out_yaw + pidValues.out_alt;
    setpoint.mot[3] = receiverValues.chan[THROTTLE_CHAN] - pidValues.out_roll + pidValues.out_pitch - pidValues.out_yaw + pidValues.out_alt;
#else //NUMBER_OF_MOTORS == 6
    setpoint.mot[0] = receiverValues.chan[THROTTLE_CHAN] + int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_LEFT_RIGHT : 0)                                                                                    + int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
    setpoint.mot[1] = receiverValues.chan[THROTTLE_CHAN] + int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_FRONT_REAR : 0) - int16_t(pidValues.out_pitch != 0 ? pidValues.out_pitch * C_PITCH_FRONT_REAR : 0) - int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
    setpoint.mot[2] = receiverValues.chan[THROTTLE_CHAN] - int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_FRONT_REAR : 0) - int16_t(pidValues.out_pitch != 0 ? pidValues.out_pitch * C_PITCH_FRONT_REAR : 0) + int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
    setpoint.mot[3] = receiverValues.chan[THROTTLE_CHAN] - int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_LEFT_RIGHT : 0)                                                                                    - int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
    setpoint.mot[4] = receiverValues.chan[THROTTLE_CHAN] - int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_FRONT_REAR : 0) + int16_t(pidValues.out_pitch != 0 ? pidValues.out_pitch * C_PITCH_FRONT_REAR : 0) + int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
    setpoint.mot[5] = receiverValues.chan[THROTTLE_CHAN] + int16_t(pidValues.out_roll != 0 ? pidValues.out_roll * COEFF_ROLL_FRONT_REAR : 0) + int16_t(pidValues.out_pitch != 0 ? pidValues.out_pitch * C_PITCH_FRONT_REAR : 0) - int16_t(pidValues.out_yaw != 0 ? pidValues.out_yaw * C_YAW : 0) + pidValues.out_alt;
#endif
}

void MotorsModule::processStateFromCommander() {
    if(state.state == MANU) {
        motorsConfigNode.get(setpoint);
    } else if(state.state == DISARMED) {
        for (int i = 0; i < NUMBER_OF_MOTORS; i++)
            setpoint.mot[i] = MIN_THROTTLE_VALUE;
    }
}

void MotorsModule::sendValuesToMotorsAndNodes() {
    for (size_t i = 0; i < NUMBER_OF_MOTORS; i++)
    {
        setpoint.mot[i] = constrain_(setpoint.mot[i], MIN_CHANNEL_VALUE, MAX_CHANNEL_VALUE);
        values.mot[i] = setpoint.mot[i];
    }

    motors.setMotors(setpoint);
    motorsNode.set(values);
}
