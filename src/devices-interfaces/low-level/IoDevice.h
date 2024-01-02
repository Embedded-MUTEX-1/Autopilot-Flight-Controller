#ifndef __UARTDEVICE_H__
#define __UARTDEVICE_H__

#include <cstdint>
#include <cstddef>
#include <Arduino.h>

class IoDevice {
    IoDevice();
    int8_t init();
    void setPinMode(uint16_t pinNum, bool mode);
    void setPin(uint16_t pinNum, bool state);
    bool getPin(uint16_t pinNum);
};

#endif // __UARTDEVICE_H__