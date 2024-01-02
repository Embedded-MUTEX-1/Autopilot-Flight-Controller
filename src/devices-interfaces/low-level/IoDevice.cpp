//
// Created by lenny on 01/01/24.
//

#include "IoDevice.h"

IoDevice::IoDevice() {

}

int8_t IoDevice::init() {
    return 0;
}

void IoDevice::setPinMode(uint16_t pinNum, bool mode) {
    pinMode(pinNum, mode ? INPUT : OUTPUT);
}

void IoDevice::setPin(uint16_t pinNum, bool state)  {
    digitalWrite(pinNum, state);
}

bool IoDevice::getPin(uint16_t pinNum)  {
    return digitalRead(pinNum);
}