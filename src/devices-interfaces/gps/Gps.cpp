//
// Created by lenny on 06/01/24.
//

#include "Gps.h"

Gps::Gps(UartDevice* uartDevice) {
    this->uartDevice = uartDevice;
    this->decoder = new MicroNMEA(nmeaBuffer, sizeof(nmeaBuffer));
}

Gps::~Gps() {

}

int8_t Gps::init() {
    return 0;
}

int8_t Gps::deinit() {
    return 0;
}

int8_t Gps::updateAndGetData(positionData &values) {
    char c;
    while(uartDevice->numBytesAvailable() > 0) {
        c = uartDevice->readByte();
        if(decoder->process(c))
            break;
    }
    if (decoder->isValid())
    {
        if(decoder->getNavSystem() == 'N') {
            values.lat = decoder->getLatitude() / 1e6;
            values.lon = decoder->getLongitude() / 1e6;
            decoder->clear();
            return 0;
        }
    }
    return -1;
}