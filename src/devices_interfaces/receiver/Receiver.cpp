//
// Created by lenny on 06/01/24.
//

#include "Receiver.h"

Receiver::Receiver() {
    ibus = IBusBM(uart);
}

Receiver::~Receiver() {
    deinit();
}

int8_t Receiver::init() {
    uart.init(RECEIVER_UART_PORT, RECEIVER_UART_TX, RECEIVER_UART_RX, RECEIVER_UART_BAUD);
    return ibus.init();
}

int8_t Receiver::deinit() {
    return ibus.deinit();
}

int8_t Receiver::updateAndGetData(struct receiverData &values) {
    ibus.update();
    for (int i = 0;i < NUMBER_OF_CHANNELS;i++) {
        values.chan[i] = ibus.readChannel(i);
    }
    return 0;
}
