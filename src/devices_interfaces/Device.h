#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_DEVICE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_DEVICE_H

#include <cstdint>

template <typename T> 
struct Device
{
    virtual int8_t init() = 0;
    virtual int8_t deinit() = 0;
    virtual int8_t updateAndGetData(T &values) = 0;
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_DEVICE_H
