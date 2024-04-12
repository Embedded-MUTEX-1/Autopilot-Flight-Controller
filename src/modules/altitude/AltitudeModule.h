//
// Created by lenny on 15/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ALTITUDEMODULE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ALTITUDEMODULE_H

#include <cstdint>
#include "../../devices_interfaces/barometer/Barometer.h"
#include "../../config.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"

void altitudeTask(void *args);
class AltitudeModule {
public:
    AltitudeModule(I2cDevice *i2c);
    int8_t init();
    void run();
private:
    // Barometer baro;
    // struct altitudeData values;
    // uint64_t timestamp = 0;
    // float previousAlt = 0;

    float computeVerticalSpeed();
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ALTITUDEMODULE_H
