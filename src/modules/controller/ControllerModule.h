#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_CONTROLLERMODULE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_CONTROLLERMODULE_H

#include <cstdint>
#include "../../resources/nodes.h"
#include "../../utils/utils.h"
#include "../../../lib/QuickPID/src/QuickPID.h"
#include "../../../lib/FastPID/src/FastPID.h"
#include <esp_log.h>

class ControllerModule {
public:
    ControllerModule();
    int8_t init();
    void run();
private:
    struct pidOutput values;
    struct commanderState state;
    struct attitudeData attitudeValues;
    struct altitudeData altitudeValues;
    struct pidSetpoint anglesSetpoint;
    struct receiverData receiverValues;

    FastPID rateRollPid;
    FastPID ratePitchPid;
    FastPID rateYawPid;
    FastPID altitudePid;

    uint64_t timestamp = 0;
    float offsetYaw = 0;
    float yawRateSetpoint, rollRateSetpoint, pitchRateSetpoint, altitudeSetpoint, verticalSpeedSetpoint;

    void getDataFromNodes();
    void computeSetpoints();
    void processStateFromCommander();
    void computeOutputValuesAndSendValuesToNode();
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_CONTROLLERMODULE_H