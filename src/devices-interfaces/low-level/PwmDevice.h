//
// Created by lenny on 01/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_PWMDEVICE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_PWMDEVICE_H

#include <cstdint>
#include <cstddef>
#include <Arduino.h>

class PwmDevice {
public:
    PwmDevice();
    int8_t init();
    int8_t initPin(uint8_t channel, uint8_t pinNum, float pwmFreq);
    void setPin(uint8_t channel, uint8_t pinNum, uint16_t dutyCycle);
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_PWMDEVICE_H
