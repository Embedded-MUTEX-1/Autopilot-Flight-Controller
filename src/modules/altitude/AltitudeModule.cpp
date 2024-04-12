//
// Created by lenny on 15/01/24.
//

#include "AltitudeModule.h"


AltitudeModule::AltitudeModule(I2cDevice *i2c)
{
    // baro = Barometer(i2c);
}

int8_t AltitudeModule::init()
{
    // if(baro.init() != 0)
    //     return -1;

    // baro.updateAndGetData(values);
    // previousAlt = values.alt;

    return 0;
}

void AltitudeModule::run()
{
    // timestamp = get_ms_count();

    // baro.updateAndGetData(values);
    // //computeVerticalSpeed();
    // altitudeNode.set(values);

    // values.loopPeriod = get_ms_count() - timestamp;
    // wait(values.loopPeriod, ALTITUDE_LOOP_FREQ);
}

float AltitudeModule::computeVerticalSpeed() {
    // values.vertical_speed = (values.alt - previousAlt) / (1 / ALTITUDE_LOOP_FREQ);
    // previousAlt = values.alt;
}