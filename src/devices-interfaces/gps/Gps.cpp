//
// Created by lenny on 06/01/24.
//

#include "Gps.h"

Gps::Gps(UartDevice* uartDevice) {
    this->uartDevice = uartDevice;
    this->decoder = new MicroNMEA();
}

Gps::~Gps() {

}

int8_t Gps::init() {
    return 0;
}

int8_t Gps::deinit() {
    return 0;
}

int8_t Gps::updateAndGetData(gpsData &values) {
    char c;
    while(uartDevice->numBytesAvailable() > 0) {
        c = uartDevice->readByte();
        decoder->process(c);
    }
    if (decoder->isValid())
    {
        if(decoder->getNavSystem() == 'N') {
            values.lat = decoder->getLatitude() / 1e6;
            values.lon = decoder->getLongitude() / 1e6;
            return -1;
        }
    }
    return 0;
}