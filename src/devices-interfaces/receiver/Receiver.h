//
// Created by lenny on 06/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_RECEIVER_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_RECEIVER_H

#include <cstdint>
#include <cstddef>
#include "structs.h"
#include "devices-interfaces/low-level/UartDevice.h"
#include "devices-interfaces/receiver/ibus-driver/IBusBM.h"

class Receiver {
public:
    Receiver(UartDevice& serial);
    ~Receiver();

    uint8_t init();
    uint8_t deinit();
    uint8_t updateAndGetData(struct receiverData &values);
private:
    IBusBM* ibus;
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_RECEIVER_H
