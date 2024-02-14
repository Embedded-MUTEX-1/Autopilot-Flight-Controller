//
// Created by lenny on 02/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_UTILS_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_UTILS_H

#include <cstdint>
#include <cstddef>

#define RAD_TO_DEG (180 / 3.14159265358979323846)
#define DEG_TO_RAD (3.14159265358979323846 / 180)

void delay_milis(uint32_t milis);
void wait(uint32_t currentLoopDuration, uint16_t loopFreq);
uint32_t get_ms_count();
float map_(float x, float in_min, float in_max, float out_min, float out_max);
long map_(long x, long in_min, long in_max, long out_min, long out_max);
long constrain_(long value, long min, long max);
uint16_t constrain_(uint16_t value, uint16_t min, uint16_t max);
float constrain_(float value, float min, float max);

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_UTILS_H
