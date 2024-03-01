//
// Created by lenny on 12/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_LIDAR_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_LIDAR_H

#include <cstdint>
#include <cstddef>
#include "devices-interfaces/low-level/UartDevice.h"
#include "devices/tf-mini-plus/TFMPlus.h"
#include "structs.h"

class Lidar {
public:
    Lidar();
    ~Lidar();

    int8_t init();
    int8_t deinit();
    int8_t updateAndGetData(altitudeData &values);
private:
    UartDevice uart;
    TFMPlus lidar;
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_LIDAR_H
