//
// Created by lenny on 06/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_GPS_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_GPS_H

#include <cstdint>
#include <cstddef>
#include "structs.h"
#include "devices-interfaces/low-level/UartDevice.h"
#include "NMEA-parsers/MicroNMEA.h"

class Gps {
public:
    Gps();
    ~Gps();

    int8_t init();
    int8_t deinit();
    int8_t updateAndGetData(struct positionData &values);
private:
    MicroNMEA decoder;
    UartDevice uart;
    char nmeaBuffer[500];
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_GPS_H
