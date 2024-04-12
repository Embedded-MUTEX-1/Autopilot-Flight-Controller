#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_BAROMETER_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_BAROMETER_H

#include <cstdint>
#include <cstddef>
#include "../low-level/I2cDevice.h"
#include "devices/dps310/Dps3xx.h"
#include "../../structs.h"

class Barometer {
public:
    Barometer() {}
    Barometer(I2cDevice *i2c);
    ~Barometer();

    int8_t init();
    int8_t deinit();
    int8_t updateAndGetData(struct altitudeData &values);
private:
    I2cDevice *i2c;
    Dps3xx baro = Dps3xx();

    float computeAltitude(float pres);
};

#endif