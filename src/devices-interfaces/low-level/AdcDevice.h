//
// Created by lenny on 28/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ADCDEVICE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ADCDEVICE_H

#include <cstdint>
#include <cstddef>
#include <Arduino.h>

class AdcDevice {
public:
    int8_t init();
    int8_t initPin(uint16_t pinNum);
    int16_t getValue(uint8_t pinNum);
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ADCDEVICE_H
