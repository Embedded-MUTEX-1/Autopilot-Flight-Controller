//
// Created by lenny on 15/01/24.
//

#include "AltitudeModule.h"


AltitudeModule::AltitudeModule()
{
    
}

int8_t AltitudeModule::init()
{
    return lidar.init();
}

void AltitudeModule::run()
{
    timestamp = get_ms_count();

    lidar.updateAndGetData(values);
    altitudeNode.set(values);

    values.loopPeriod = get_ms_count() - timestamp;
    wait(values.loopPeriod, ALTITUDE_LOOP_FREQ);
}
