//
// Created by lenny on 06/01/24.
//

#include "Gps.h"

Gps::Gps() {
    this->decoder = MicroNMEA(nmeaBuffer, sizeof(nmeaBuffer));
}

Gps::~Gps() {

}

int8_t Gps::init() {
    uart.init(GPS_UART_PORT, GPS_UART_TX, GPS_UART_RX, GPS_UART_BAUD);
    return 0;
}

int8_t Gps::deinit() {
    return 0;
}

int8_t Gps::updateAndGetData(positionData &values) {
    char c;
    while(uart.numBytesAvailable() > 0) {
        c = uart.readByte();
        if(decoder.process(c))
            break;
    }
    if (decoder.isValid())
    {
        if(decoder.getNavSystem() == 'N') {
            values.lat = decoder.getLatitude() / 1e6;
            values.lon = decoder.getLongitude() / 1e6;
            decoder.clear();
            return 0;
        }
    }
    return -1;
}