//
// Created by lenny on 12/01/24.
//

#include "Telemetry.h"

Telemetry::Telemetry() {

}

Telemetry::~Telemetry() {

}

int8_t Telemetry::init() {
    return 0;
}

int8_t Telemetry::deinit() {
    return 0;
}

int8_t Telemetry::sendTelemetryValues(imuData &imu, attitudeData &attitude, altitudeData &altitude, gpsData &gps,
                                      naviagtionData &navigation, receiverData &receiver, motorsData &motors) {
    return 0;
}

bool Telemetry::isConfigDataAvailable() {
    return false;
}

void
Telemetry::getConfigData(struct attitudeConfig *attitude, struct pidConfig *pid, struct pidAltitudeConfig *altitude,
                         struct pidNavigationConfig *nav) {

}
