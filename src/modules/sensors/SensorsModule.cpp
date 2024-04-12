//
// Created by lenny on 14/01/24.
//

#include "SensorsModule.h"

SensorsModule::SensorsModule(I2cDevice *i2c) {
    imu = Imu(i2c);
    baro = Barometer(i2c);

    attitudeConfigNode.addCallback([this](struct attitudeConfig newConfig) -> void {
        ahrs.setConfig(newConfig.param1, newConfig.param2);

        imu.updateAndGetData(attitudeValues);

        ahrs.updateIMU(
            attitudeValues.gyroRateRoll,
            attitudeValues.gyroRatePitch,
            attitudeValues.gyroRateYaw,
            attitudeValues.accRateRoll,
            attitudeValues.accRatePitch,
            attitudeValues.accRateYaw
        );

        headingCorrection = computeHeading(attitudeValues.magX, attitudeValues.magY, attitudeValues.magZ, ahrs.getRoll(), ahrs.getPitch());
        headingCorrection = headingCorrection - ahrs.getYaw();

        altitudeOffset = altitudeValues.alt;
    });
}

int8_t SensorsModule::init() {
    config.offsetRoll = OFFSET_ROLL;
    config.offsetPitch = OFFSET_PITCH;
    config.offsetYaw = OFFSET_YAW;

    if(imu.init() != 0)
        return -1;
    // if(baro.init() != 0)
    //     return -1;

    delay_milis(3000);

    altitudeValues.alt = 0;
    altitudeValues.vertical_speed = 0;

    ahrs.begin(ATTITUDE_LOOP_FREQ);
    ahrs.setConfig(PARAM_1, PARAM_2);

    imu.updateAndGetData(attitudeValues);

    ahrs.updateIMU(
            attitudeValues.gyroRateRoll,
            attitudeValues.gyroRatePitch,
            attitudeValues.gyroRateYaw,
            attitudeValues.accRateRoll,
            attitudeValues.accRatePitch,
            attitudeValues.accRateYaw
    );

    headingCorrection = computeHeading(attitudeValues.magX, attitudeValues.magY, attitudeValues.magZ, ahrs.getRoll(), ahrs.getPitch());
    headingCorrection = headingCorrection - ahrs.getYaw();;

    return 0;
}

void SensorsModule::run() {
    timestamp = get_ms_count();

    getDataFromNodesAndSensors();

    computeData();

    attitudeNode.set(attitudeValues);
    altitudeNode.set(altitudeValues);

    attitudeValues.loopPeriod = get_ms_count() - timestamp;
    wait(attitudeValues.loopPeriod, ATTITUDE_LOOP_FREQ);
    count++;
}

void SensorsModule::getDataFromNodesAndSensors() {
    attitudeConfigNode.get(config);
    imu.updateAndGetData(attitudeValues);

    /* if(count >= (float(1.0f / ALTITUDE_LOOP_FREQ) / float(1.0f / ATTITUDE_LOOP_FREQ))) {
        struct altitudeData tempValues;
        baro.updateAndGetData(tempValues);

        tempValues.alt -= altitudeOffset;
        altitudeValues.alt = altitudeValues.alt * 0.9996f + tempValues.alt * 0.0004f; 
        float alt_diff = altitudeValues.alt - tempValues.alt;

        if (alt_diff > 8) alt_diff = 8;                                                    //If the difference is larger then 8 limit the difference to 8.
        if (alt_diff < -8) alt_diff = -8;                                                  //If the difference is smaller then -8 limit the difference to -8.
        //If the difference is larger then 1 or smaller then -1 the slow average is adjuste based on the error between the fast and slow average.
        if (alt_diff > 1 || alt_diff < -1) altitudeValues.alt -= alt_diff / 6.0;

        computeVerticalSpeed();
        
        count = 0;
    } */
}

void SensorsModule::computeData() {
    ahrs.updateIMU(
            attitudeValues.gyroRateRoll,
            attitudeValues.gyroRatePitch,
            attitudeValues.gyroRateYaw,
            attitudeValues.accRateRoll,
            attitudeValues.accRatePitch,
            attitudeValues.accRateYaw
    );

    attitudeValues.roll         = ahrs.getRoll()  - config.offsetRoll;
    attitudeValues.pitch        = ahrs.getPitch() - config.offsetPitch;
    attitudeValues.yaw          = ahrs.getYaw() + headingCorrection - config.offsetYaw;

    if(attitudeValues.yaw > 360)
        attitudeValues.yaw -= 360;
    if(attitudeValues.yaw < 0)
        attitudeValues.yaw += 360;
    if(attitudeValues.yaw > 180)
        attitudeValues.yaw -= 360;
}

float SensorsModule::computeHeading(int16_t magAxisX, int16_t magAxisY, int16_t magAxisZ, float roll, float pitch) {
    float compass_x_horizontal, compass_y_horizontal, actual_compass_heading;
    //The compass values change when the roll and pitch angle of the quadcopter changes. That's the reason that the x and y values need to calculated for a virtual horizontal position.
    //The 0.0174533 value is phi/180 as the functions are in radians in stead of degrees.
    compass_x_horizontal = (float)magAxisX * cos(pitch * -0.0174533) + (float)magAxisY * sin(roll * 0.0174533) * sin(pitch * -0.0174533) - (float)magAxisZ * cos(roll * 0.0174533) * sin(pitch * -0.0174533);
    compass_y_horizontal = (float)magAxisY * cos(roll * 0.0174533) + (float)magAxisZ * sin(roll * 0.0174533);

    //Now that the horizontal values are known the heading can be calculated. With the following lines of code the heading is calculated in degrees.
    //Please note that the atan2 uses radians in stead of degrees. That is why the 180/3.14 is used.
    if (compass_y_horizontal < 0)
        actual_compass_heading = 180 + (180 + ((atan2(compass_y_horizontal, compass_x_horizontal)) * (180 / 3.14)));
    else
        actual_compass_heading = (atan2(compass_y_horizontal, compass_x_horizontal)) * (180 / 3.14);

    actual_compass_heading += MAGNETIC_DECLINATION;     //Add the declination to the magnetic compass heading to get the geographic north.
    if (actual_compass_heading < 0)
        actual_compass_heading += 360;         //If the compass heading becomes smaller then 0, 360 is added to keep it in the 0 till 360 degrees range.
    else if (actual_compass_heading >= 360)
        actual_compass_heading -= 360;         //If the compass heading becomes larger then 360, 360 is subtracted to keep it in the 0 till 360 degrees range.

    actual_compass_heading = map_(actual_compass_heading, 0, 360, 360, 0);

    return actual_compass_heading;
}

float SensorsModule::computeVerticalSpeed() {
    altitudeValues.vertical_speed = (altitudeValues.alt - previousAlt) / (1.0f / ALTITUDE_LOOP_FREQ);
    previousAlt = altitudeValues.alt;
    return 0.0f;
}
