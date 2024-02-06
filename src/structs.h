//
// Created by lenny on 05/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_STRUCTS_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_STRUCTS_H

#include <cstdint>
#include <cstddef>
#include <string>
#include "config.h"

enum droneState {
    DISARMED = 0, MANU, LEVEL, POS_HOLD, NAVIGATION
};

struct attitudeData {
    float gyroRateRoll;
    float gyroRatePitch;
    float gyroRateYaw;
    float accRateRoll;
    float accRatePitch;
    float accRateYaw;
    int16_t magX;
    int16_t magY;
    int16_t magZ;
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
    bool newConfig;
};

struct pidSetpoint {
    float roll;
    float pitch;
    float yawRate;
};

struct pidOutput {
    std::string status;
    int16_t out_roll;
    int16_t out_pitch;
    int16_t out_yaw;
    int16_t out_alt;
    int16_t outBatteryCompensation;
    uint64_t loopRate;
};

struct positionData {
    std::string status;
    float latitude_home = 0.0f;
    float longitude_home = 0.0f;
    unsigned long TOW;
    bool isPositionFix;
    double vn;
    double ve;
    double vd;
    double lat;
    double lon;
    double alt;
    uint64_t loopPeriod;
};

struct pidConfig {
    float proll, ppitch, pyaw;
    float iroll, ipitch, iyaw;
    float droll, dpitch, dyaw;
    bool newConfig;
};

struct pidNavigationConfig {
    float pnav, inav, dnav;
    float maxRollAngle, maxPitchAngle;
    float minRollAngle, minPitchAngle;
    bool newConfig;
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
    bool newConfig;
};

struct motorsData {
    std::string status;
    uint16_t mot[NUMBER_OF_MOTORS];
    float vBat;
    uint64_t loopPeriod;
};

struct motorsSetpoint {
    uint16_t mot[NUMBER_OF_MOTORS];
    bool enable;
};

struct navigationSetpoint
{
    double lat;
    double lon;
};


struct commanderState {
    enum droneState state;
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_STRUCTS_H
