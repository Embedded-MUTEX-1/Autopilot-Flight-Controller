#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TELEMETRYRMODULE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_TELEMETRYRMODULE_H

#include <cstdint>
#include "../../devices_interfaces/telemetry/Telemetry.h"
#include "../../devices_interfaces/telemetry/WirelessInterface.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"

class TelemetryModule {
public:
    TelemetryModule();
    int8_t init();
    void run();

private:
    Telemetry telemetry;
    // Drone -> Telemetry
    struct receiverData receiverValues;
    struct attitudeData attitudeValues;
    struct positionData positionValues;
    struct altitudeData altitudeValues;
    struct motorsData motorsValues;
    struct pidOutput pidOutputValues;
    struct commanderState state;

    // Telemetry -> Drone
    struct navigationSetpoint navSetpointValues;
    struct motorsSetpoint motorsSetpointValues;
    struct attitudeConfig attitudeConfValues;
    struct pidConfig pidConfValues;
    struct pidNavigationConfig pidNavConfValues;
    struct pidAltitudeConfig pidAltConfValues;
    struct commanderState stateConf;
    
    uint64_t timestamp, loopPeriod, count;
    bool isFirstDataReceived = false;

    void sendConfigValues();
    void getDataFromNodes();
    void sendTelemetryValues();
    void processDataFromGroundStation();
    void setDataToNodes();
};

#endif