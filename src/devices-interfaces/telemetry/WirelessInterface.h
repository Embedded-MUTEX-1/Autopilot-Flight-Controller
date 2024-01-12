//
// Created by lenny on 11/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_WIRELESSINTERFACE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_WIRELESSINTERFACE_H

#include <cstdint>
#include <cstddef>

struct WirelessInterface {
    virtual int8_t init() = 0;
    virtual int8_t deinit() = 0;
    virtual size_t dataAvailable() = 0;
    virtual size_t readAllBytes(char* buf) = 0;
    virtual void sendBytes(char * buf, size_t len) = 0;
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_WIRELESSINTERFACE_H
