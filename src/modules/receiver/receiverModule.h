//
// Created by lenny on 14/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_RECEIVERMODULE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_RECEIVERMODULE_H

#include <cstdint>

void receiverTask(void *args);
float computeAngleFromChannel(uint16_t channel);
float computeYawRateFromChannel(uint16_t channel);

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_RECEIVERMODULE_H
