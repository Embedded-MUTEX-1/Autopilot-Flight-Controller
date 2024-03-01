#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_COMMANDERMODULE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_COMMANDERMODULE_H

#include <cstdint>
#include "../../resources/nodes.h"
#include "../../utils/utils.h"

class CommanderModule {
public:
    CommanderModule();
    void run();
private:
    struct commanderState state;
    struct commanderState stateFromTelemetry;
    struct receiverData receiverValues;
    uint64_t timestamp = 0, loopPeriod = 0;

    void getDataFromNodes();
    void processState();
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_COMMANDERMODULE_H