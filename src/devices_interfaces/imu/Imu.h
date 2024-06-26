//
// Created by lenny on 05/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_IMU_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_IMU_H

#include <cstdint>
#include <cstddef>
#include "../low-level/I2cDevice.h"
#include "devices/bmi088/BMI088.h"
#include "devices/bmm150/bmm150.h"
#include "devices/bmm150/bmm150_defs.h"
#include "../../structs.h"

class Imu {
public:
    Imu() {}
    Imu(I2cDevice *i2c);
    ~Imu();

    int8_t init();
    int8_t deinit();
    int8_t updateAndGetData(struct attitudeData &values);
    void imuCalibration(uint16_t calibNum);
    void magCalibration(uint16_t time);
private:
    I2cDevice* i2c;
    Bmi088Accel accel;
    Bmi088Gyro gyro;
    BMM150 mag;
    int16_t magMaxAxisX = 131, magMinAxisX = -117;
    int16_t magMaxAxisY = 114, magMinAxisY = -134;
    int16_t magMaxAxisZ = 112, magMinAxisZ = -129;
    float gyroRateOffsetRoll;
    float gyroRateOffsetPitch;
    float gyroRateOffsetYaw;
    float accRateOffsetRoll;
    float accRateOffsetPitch;
    float accRateOffsetYaw;
    float compass_scale_y, compass_scale_z;
    int16_t compass_offset_x, compass_offset_y, compass_offset_z;
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_IMU_H
