//
// Created by lenny on 12/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_RECEIVERINTERFACE_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_RECEIVERINTERFACE_H

#include <cstdint>
#include <cstddef>

struct ReceiverInterface {
    virtual int8_t init() = 0;
    virtual int8_t deinit() = 0;
    virtual size_t update() = 0;
    virtual uint16_t readChannel(uint8_t channelNr) = 0;
};

#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_RECEIVERINTERFACE_H
