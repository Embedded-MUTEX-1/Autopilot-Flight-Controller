//
// Created by lenny on 14/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ATTITUDE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ATTITUDE_H

#include <cstdint>

void attitudeTask(void *args);
float computeHeading(int16_t magX, int16_t magY, int16_t magZ, float roll, float pitch, float yaw);

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ATTITUDE_H
