#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_DEVICE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_DEVICE_H

#include <cstdint>

template <typename T> 
struct Device
{
    virtual int8_t init();
    virtual int8_t deinit();
    virtual int8_t updateAndGetData(T &values);
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_DEVICE_H
