//
// Created by lenny on 02/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_UTILS_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_UTILS_H

#include <cstdint>
#include <cstddef>

void delay_milis(uint32_t milis);
uint32_t get_ms_count();
float map_(float x, float in_min, float in_max, float out_min, float out_max);
long map_(long x, long in_min, long in_max, long out_min, long out_max);
long constrain_(long value, long min, long max);
float constrain_(float value, float min, float max);

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_UTILS_H
