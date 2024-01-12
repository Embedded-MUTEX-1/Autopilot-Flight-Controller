//
// Created by lenny on 12/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TELEMETRY_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TELEMETRY_H

#include <cstdint>
#include <cstddef>
#include "../../structs.h"

class Telemetry {
    Telemetry();
    ~Telemetry();

    int8_t init();
    int8_t deinit();

    int8_t sendTelemetryValues(
            struct imuData &imu,
            struct attitudeData &attitude,
            struct altitudeData &altitude,
            struct gpsData &gps,
            struct naviagtionData &navigation,
            struct receiverData &receiver,
            struct motorsData &motors);

    bool isConfigDataAvailable();

    void getConfigData(
            struct attitudeConfig *attitude,
            struct pidConfig *pid,
            struct pidAltitudeConfig *altitude,
            struct pidNavigationConfig *nav);
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TELEMETRY_H
