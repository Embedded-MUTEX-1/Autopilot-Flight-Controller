//
// Created by lenny on 01/01/24.
//

#include "PwmDevice.h"

PwmDevice::PwmDevice() {

}

int8_t PwmDevice::init() {
    return 0;
}

int8_t PwmDevice::initPin(uint8_t channel, uint8_t pinNum, float pwmFreq) {
    ledcSetup(channel, pwmFreq, 12);
    ledcAttachPin(pinNum, channel);
    return 0;
}

void PwmDevice::setPin(uint8_t channel, uint8_t pinNum, uint16_t dutyCycle) {
    ledcWrite(channel, dutyCycle);
}