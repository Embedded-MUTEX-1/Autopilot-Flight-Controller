#ifndef AUTOPILOT_FLIGHT_CONTROLLER_IODEVICE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_IODEVICE_H

#include <cstdint>
#include <cstddef>

class IoDevice {
public:
    IoDevice();
    int8_t init();
    void setPinMode(uint16_t pinNum, bool mode);
    void setPin(uint16_t pinNum, bool state);
    bool getPin(uint16_t pinNum);
};

#endif // AUTOPILOT_FLIGHT_CONTROLLER_IODEVICE_H