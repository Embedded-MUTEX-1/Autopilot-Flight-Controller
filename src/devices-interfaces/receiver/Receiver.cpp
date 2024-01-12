//
// Created by lenny on 06/01/24.
//

#include "Receiver.h"

Receiver::Receiver(UartDevice& serial) {
    ibus = new IBusBM(serial);
    ibus->init();
}

Receiver::~Receiver() {
    deinit();
}

int8_t Receiver::init() {
    return 0;
}

int8_t Receiver::deinit() {
    return ibus->deinit();
}

int8_t Receiver::updateAndGetData(struct receiverData &values) {
    ibus->update();
    for (int i = 0;i < NUMBER_OF_CHANNELS;i++) {
        values.chan[i] = ibus->readChannel(i);
    }
    return 0;
}
