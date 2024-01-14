//
// Created by lenny on 12/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TELEMETRY_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TELEMETRY_H

#include <cstdint>
#include <cstddef>
#include "../../structs.h"
#include "devices-interfaces/telemetry/wifi/WifiManager.h"

class Telemetry {
public:
    Telemetry();
    ~Telemetry();

    int8_t init();
    int8_t deinit();

    int8_t sendTelemetryValues(
            struct attitudeData &attitude,
            struct altitudeData &altitude,
            struct positionData &position,
            struct pidOutput &pid,
            struct receiverData &receiver,
            struct motorsData &motors,
            struct commanderState commander);

    bool isConfigDataAvailable();

    int8_t getConfigData(
            struct attitudeConfig *attitude,
            struct pidConfig *pid,
            struct pidAltitudeConfig *altitude,
            struct pidNavigationConfig *nav,
            struct motorsConfig *motors,
            struct commanderState commander);
private:
    WifiManager wifiManager;
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TELEMETRY_H
