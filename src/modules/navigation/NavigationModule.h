//
// Created by lenny on 28/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_POSITIONMODULE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_POSITIONMODULE_H

#include "../../devices_interfaces/gps/Gps.h"
#include "../../resources/nodes.h"
#include "../../utils/utils.h"
#include "../../../lib/FastPID/src/FastPID.h"

class NavigationModule {
public:
    NavigationModule();
    int8_t init();
    void run();
private:
    Gps gps;

    struct positionData values;
    struct commanderState state;
    struct navigationSetpoint setpoint;
    struct pidSetpoint anglesSetpoint;
    
    FastPID latitudePid;
    FastPID longitudePid;

    uint64_t timestamp = 0;

    void getDataFromNodesAndGps();
    void processDataAndSetToNodes();
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_POSITIONMODULE_H
