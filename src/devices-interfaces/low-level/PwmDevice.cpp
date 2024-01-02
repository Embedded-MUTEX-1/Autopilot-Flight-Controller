//
// Created by lenny on 01/01/24.
//

#include "PwmDevice.h"

PwmDevice::PwmDevice() {

}

int8_t PwmDevice::init() {
    return 0;
}

int8_t PwmDevice::initPin(uint16_t channel, uint16_t pinNum, float pwmFreq) {
    ledcSetup(channel, pwmFreq, 10);
    ledcAttachPin(pinNum, channel);
    return 0;
}

void PwmDevice::setPin(uint16_t channel, uint16_t pinNum, uint16_t dutyCycle) {
    ledcWrite(channel, dutyCycle);
}