//
// Created by lenny on 12/01/24.
//

#include "Lidar.h"

Lidar::Lidar(UartDevice &uartDevice) {
    lidar = new TFMPlus(&uartDevice);
}

Lidar::~Lidar() {
    deinit();
}

int8_t Lidar::init() {
    return lidar->init();
}

int8_t Lidar::deinit() {
    return 0;
}

int8_t Lidar::updateAndGetData(altitudeData &values) {
    return lidar->updateAndGetData(values);
}