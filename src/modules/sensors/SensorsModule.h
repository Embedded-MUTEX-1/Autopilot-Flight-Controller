//
// Created by lenny on 14/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ATTITUDEMODULE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ATTITUDEMODULE_H

#include <cstdint>
#include "../../devices_interfaces/low-level/I2cDevice.h"
#include "../../devices_interfaces/imu/Imu.h"
#include "../../devices_interfaces/barometer/Barometer.h"
#include "attitude_estimators/mahony/MahonyAHRS.h"
#include "../../config.h"
#include "../../utils/utils.h"
#include "../../resources/nodes.h"

class SensorsModule {
public:
    SensorsModule(I2cDevice *i2c);
    int8_t init();
    void run();
private:
    Imu imu;
    Mahony ahrs;
    Barometer baro;

    struct altitudeData altitudeValues;
    struct attitudeData attitudeValues;
    struct attitudeConfig config;
    uint64_t timestamp = 0;
    float previousAlt = 0;
    uint16_t count = 0;
    float altitudeOffset = 0;
    float headingCorrection = 0;
    
    void getDataFromNodesAndSensors();
    void computeData();
    float computeHeading(int16_t magX, int16_t magY, int16_t magZ, float roll, float pitch);
    float computeVerticalSpeed();
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ATTITUDEMODULE_H
