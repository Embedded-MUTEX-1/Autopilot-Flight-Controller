//
// Created by lenny on 14/01/24.
//

#include "attitudeModule.h"
#include "devices-interfaces/low-level/I2cDevice.h"
#include "devices-interfaces/imu/Imu.h"
#include "modules/attitude/attitude-estimators/mahony/MahonyAHRS.h"
#include "config.h"
#include "utils/utils.h"
#include "resources/nodes.h"

void attitudeTask(void *args) {
    I2cDevice i2c;
    Imu imu(&i2c);
    Mahony ahrs;
    struct attitudeData values;
    struct attitudeConfig config;
    uint64_t timestamp = 0;

    i2c.init();
    if(imu.init() != 0)
        while(1) { delay_milis(100); }
        
    ahrs.begin(ATTITUDE_LOOP_FREQ);

    while(1) {
        timestamp = get_ms_count();

        attitudeConfigNode.get(config);
        imu.updateAndGetData(values);

        ahrs.update(
                values.gyroRateRoll,
                values.gyroRatePitch,
                values.gyroRateYaw,
                values.accRateRoll,
                values.accRatePitch,
                values.accRateYaw,
                values.magX,
                values.magY,
                values.magZ
        );

        values.heading  = computeHeading(values.magX, values.magY, values.magZ, ahrs.getRoll(), ahrs.getPitch(), ahrs.getYaw());
        values.roll     = ahrs.getRoll()  - config.offsetRoll;
        values.pitch    = ahrs.getPitch() - config.offsetPitch;
        values.yaw      = ahrs.getYaw()   - config.offsetYaw;

        if(config.newConfig) {
            ahrs.setConfig(config.param1, config.param2);
            config.newConfig = false;
        }

        attitudeNode.set(values);

        values.loopPeriod = get_ms_count() - timestamp;
        wait(values.loopPeriod, ATTITUDE_LOOP_FREQ);
    }
}

float computeHeading(int16_t magAxisX, int16_t magAxisY, int16_t magAxisZ, float roll, float pitch, float yaw) {
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
