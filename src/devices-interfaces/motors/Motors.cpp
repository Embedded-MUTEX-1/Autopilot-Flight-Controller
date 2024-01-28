//
// Created by lenny on 28/01/24.
//

#include "Motors.h"

int8_t Motors::init() {
    for(int i = 0; i < NUMBER_OF_MOTORS; i++) {
        pwmDevices[i].init();
        pwmDevices[i].initPin(i, pins[i], PWM_FREQ);
        setPulse(i, MIN_THROTTLE_VALUE);
    }
}

void Motors::setMotors(struct motorsSetpoint setpoint) {
    for(int i = 0; i < NUMBER_OF_MOTORS; i++)
        setPulse(i, setpoint.mot[i]);
}

int8_t Motors::initPin(uint8_t motorIndex, uint8_t pin, float pwmFreq) {
    pwmDevices[motorIndex].initPin(motorIndex, pin, pwmFreq);
}

void Motors::setPulse(uint8_t motorIndex, uint16_t pulseDuration) {
    pwmDevices[motorIndex].setPin(motorIndex, 0, pulseDuration * 1.638f); // 1.638 for 12 bits and 400 Hz
}

int8_t Motors::deinit() {
    return 0;
}