//
// Created by lenny on 14/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ATTITUDEMODULE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ATTITUDEMODULE_H

#include <cstdint>
#include "../../devices-interfaces/low-level/I2cDevice.h"
#include "../../devices-interfaces/imu/Imu.h"
#include "attitude-estimators/mahony/MahonyAHRS.h"
#include "../../config.h"
#include "../../utils/utils.h"
#include "../../resources/nodes.h"

class AttitudeModule {
public:
    AttitudeModule();
    int8_t init();
    void run();
private:
    Imu imu;
    Mahony ahrs;
    struct attitudeData values;
    struct attitudeConfig config;
    uint64_t timestamp = 0;

    void getFromNodesAndDataSensors();
    void computeData();
    float computeHeading(int16_t magX, int16_t magY, int16_t magZ, float roll, float pitch, float yaw);
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ATTITUDEMODULE_H
