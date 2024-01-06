//
// Created by lenny on 05/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_IMU_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_IMU_H

#include <cstdint>
#include <cstddef>
#include "../low-level/I2cDevice.h"
#include "devices/bmi088/BMI088.h"
#include "devices/ist8310/IST8310.h"
#include "structs.h"

class Imu {
public:
    Imu(I2cDevice* i2c);
    ~Imu();

    uint8_t init();
    uint8_t deinit();
    uint8_t updateAndGetData(struct imuData &values);
    void imuCalibration(uint16_t calibNum);
    void magCalibration(uint16_t time);
private:
    Bmi088Accel* accel;
    Bmi088Gyro* gyro;
    IST8310* mag;
    int16_t magMaxAxisX, magMinAxisX;
    int16_t magMaxAxisY, magMinAxisY;
    int16_t magMaxAxisZ, magMinAxisZ;
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
