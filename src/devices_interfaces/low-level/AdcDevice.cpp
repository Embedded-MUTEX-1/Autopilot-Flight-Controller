//
// Created by lenny on 28/01/24.
//

#include "AdcDevice.h"
#include "Arduino.h"

int8_t AdcDevice::init() {
    analogReadResolution(12);
    return 0;
}

int8_t AdcDevice::initPin(uint16_t pinNum) {
    return 0;
}

int16_t AdcDevice::getValue(uint8_t pinNum) {
    return analogRead(pinNum);
}