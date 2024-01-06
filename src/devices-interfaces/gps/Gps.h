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
    Gps(UartDevice* uartDevice);
    ~Gps();

    uint8_t init();
    uint8_t deinit();
    uint8_t updateAndGetData(struct gpsData &values);
private:
    MicroNMEA* decoder;
    UartDevice* uartDevice;
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_GPS_H
