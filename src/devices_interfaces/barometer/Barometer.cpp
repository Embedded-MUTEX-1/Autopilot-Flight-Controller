#include "Barometer.h"

Barometer::Barometer(I2cDevice *i2c) {
    this->i2c = i2c;
}

Barometer::~Barometer() {

}

int8_t Barometer::init() {
    if(i2c->init())
        return  -1;
    baro.begin(*i2c);
    return baro.startMeasureBothCont(DPS__MEASUREMENT_RATE_64, DPS__OVERSAMPLING_RATE_2, DPS__MEASUREMENT_RATE_64, DPS__OVERSAMPLING_RATE_2);
}

int8_t Barometer::deinit() {
    return 0;
}

int8_t Barometer::updateAndGetData(struct altitudeData &values) {
    uint8_t pressureCount = 20;
    float pressure[pressureCount];
    uint8_t temperatureCount = 20;
    float temperature[temperatureCount];
    
    baro.getContResults(temperature, temperatureCount, pressure, pressureCount);

    float pres = pressure[0] / 100;
    values.alt = 44330 * (1 - pow(pres / 1013.25, 1 / 5.255f));
    
    return 0;
}

float computeAltitude(float pres) {
    return 0.0f;
}