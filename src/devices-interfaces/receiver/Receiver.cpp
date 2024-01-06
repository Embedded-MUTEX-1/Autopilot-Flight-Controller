//
// Created by lenny on 06/01/24.
//

#include "Receiver.h"

Receiver::Receiver(UartDevice& serial) {
    ibus = new IBusBM();
    ibus->begin(serial);
}

Receiver::~Receiver() {
    deinit();
}

uint8_t Receiver::init() {
    return 0;
}

uint8_t Receiver::deinit() {
    return 0;
}

uint8_t Receiver::updateAndGetData(receiverData &values) {
    ibus->loop();
    for (int i = 0;i < NUMBER_OF_CHANNELS;i++) {
        values.chan[i] = ibus->readChannel(i);
    }
    return 0;
}
