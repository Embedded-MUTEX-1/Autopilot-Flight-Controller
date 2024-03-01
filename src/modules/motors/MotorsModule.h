//
// Created by lenny on 28/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_MOTORSMODULE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_MOTORSMODULE_H

#include "../../devices-interfaces/motors/Motors.h"
#include "../../devices-interfaces/low-level/AdcDevice.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"
#include "../../config.h"

class MotorsModule {
public:
    MotorsModule();
    int8_t init();
    void run();
private:
    Motors motors;
    AdcDevice vBatPin;
    struct pidOutput pidValues;
    struct commanderState state;
    struct motorsSetpoint setpoint;
    struct receiverData receiverValues;
    struct motorsData values;
    uint64_t timestamp = 0;

    void getDataFromNodesAndSensor();
    void computeMotorsValues();
    void processStateFromCommander();
    void sendValuesToMotorsAndNodes();
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_MOTORSMODULE_H
