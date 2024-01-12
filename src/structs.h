//
// Created by lenny on 05/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_STRUCTS_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_STRUCTS_H

#include <cstdint>
#include <cstddef>
#include <string>
#include "config.h"

struct imuData {
    std::string status;
    float gyroRateRoll;
    float gyroRatePitch;
    float gyroRateYaw;
    float accRateRoll;
    float accRatePitch;
    float accRateYaw;
    int16_t magX;
    int16_t magY;
    int16_t magZ;
    uint64_t loopPeriod;
};

struct attitudeData {
    float roll;
    float pitch;
    float yaw;
    float offsetRoll;
    float offsetPitch;
    float offsetYaw;
    float heading;
    float param1, param2;
    uint64_t loopPeriod;
};

struct attitudeConfig {
    float offsetRoll;
    float offsetPitch;
    float offsetYaw;
    float heading;
    float param1, param2;
};

struct imuSetpoint {
    float roll;
    float pitch;
    float yaw;
};

struct pidOutput {
    std::string status;
    int16_t outRoll;
    int16_t outPitch;
    int16_t outYaw;
    int16_t outAltitude;
    int16_t outBatteryCompensation;
};

struct naviagtionData {
    std::string status;
    float latitude_home = 0.0f;
    float longitude_home = 0.0f;
    float setpoint_lat = 0.0f;
    float setpoint_lon = 0.0f;
    uint64_t loopPeriod;
};

struct pidConfig {
    float proll, ppitch, pyaw;
    float iroll, ipitch, iyaw;
    float droll, dpitch, dyaw;
};

struct pidNavigationConfig {
    float pnav, inav, dnav;
    float maxRollAngle, maxPitchAngle;
    float minRollAngle, minPitchAngle;
};

struct receiverData {
    std::string status;
    uint16_t chan[NUMBER_OF_CHANNELS];
    uint64_t loopPeriod;
};

struct altitudeData {
    std::string status;
    float vertical_speed;
    float alt;
    uint64_t loopPeriod;
};

struct pidAltitudeConfig {
    float pAltitude, iAltitude, dAltitude;
};

struct gpsData {
    std::string status;
    unsigned long TOW;
    double vn;
    double ve;
    double vd;
    double lat;
    double lon;
    double alt;
    uint64_t loopPeriod;
};

struct motorsData {
    std::string status;
    uint16_t mot[NUMBER_OF_MOTORS];
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_STRUCTS_H
