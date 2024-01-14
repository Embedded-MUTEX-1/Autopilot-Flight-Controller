//
// Created by lenny on 05/01/24.
//

#include "Imu.h"

Imu::~Imu() {

}

int8_t Imu::init() {
    if(accel->init() != 0)
        return -1;
    if(!gyro->init() != 0)
        return -1;
    if(!mag->init() != 0)
        return -1;

    return 0;
}

int8_t Imu::deinit() {
    return 0;
}

int8_t Imu::updateAndGetData(struct attitudeData &values) {
    gyro->updateAndGetData(values);
    accel->updateAndGetData(values);

    values.gyroRateRoll -= gyroRateOffsetRoll; // deg/s
    values.gyroRatePitch -= gyroRateOffsetPitch; // deg/s
    values.gyroRateYaw -= gyroRateOffsetYaw; // deg/s

    values.accRateRoll -= accRateOffsetRoll;
    values.accRatePitch -= accRateOffsetPitch;
    values.accRateYaw -= accRateOffsetYaw;

    if(mag->updateAndGetData(values)) {
        values.magY += compass_offset_y;                              //Add the y-offset to the raw value.
        values.magY *= compass_scale_y;                               //Scale the y-value so it matches the other axis.
        values.magZ += compass_offset_z;                              //Add the z-offset to the raw value.
        values.magZ *= compass_scale_z;                               //Scale the z-value so it matches the other axis.
        values.magX += compass_offset_x;                              //Add the x-offset to the raw value.
    }

    return 0;
}

Imu::Imu(I2cDevice *i2c) {
    accel = new Bmi088Accel(*i2c, 0x19);
    gyro = new Bmi088Gyro(*i2c, 0x69);
    mag = new IST8310(i2c);

    magMaxAxisX = 135; magMinAxisX = -151;
    magMaxAxisY = 150; magMinAxisY = -159;
    magMaxAxisZ = 131; magMinAxisZ = -166;

    gyroRateOffsetRoll  = 0;
    gyroRateOffsetPitch = 0;
    gyroRateOffsetYaw   = 0;
    accRateOffsetRoll   = 0;
    accRateOffsetPitch  = 0;
    accRateOffsetYaw    = 0;
}

void Imu::imuCalibration(uint16_t calibNum) {
    struct attitudeData values;
    for (size_t i = 0; i < calibNum; i++)
    {
        gyro->updateAndGetData(values);

        gyroRateOffsetRoll += values.gyroRateRoll;
        gyroRateOffsetPitch += values.gyroRatePitch;
        gyroRateOffsetYaw += values.gyroRateYaw;

        delay_milis(4);
    }
    gyroRateOffsetRoll /= calibNum;
    gyroRateOffsetPitch /= calibNum;
    gyroRateOffsetYaw /= calibNum;
}

void Imu::magCalibration(uint16_t time) {
    struct attitudeData values;

#if ENABLE_MAG_CALIBRATION == 1
	while(mag->updateAndGetData(values) != 0);        					   //Read the raw compass values.

	magMinAxisX = values.magX;
	magMaxAxisX = values.magX;

	magMinAxisY = values.magY;
	magMaxAxisY = values.magY;

	magMinAxisZ = values.magZ;
	magMaxAxisZ = values.magZ;

	for(int i = 0;i < time;i++) {                                                 //Stay in this loop until the pilot lowers the pitch stick of the transmitter.                                                 //Send telemetry data to the ground station.
	    while(mag->updateAndGetData(values) != 0);          					  //Read the raw compass values.

	    values.magX *= -1;
	    values.magY *= -1;
	    //In the following lines the maximum and minimum compass values are detected and stored.
	    if (values.magX < magMinAxisX)
	    	magMinAxisX = values.magX;
	    if (values.magX > magMaxAxisX)
	    	magMaxAxisX = values.magX;

	    if (values.magY < magMinAxisY)
	    	magMinAxisY = values.magY;
	    if (values.magY > magMaxAxisY)
	    	magMaxAxisY = values.magY;

	    if (values.magZ < magMinAxisZ)
	    	magMinAxisZ = values.magZ;
	    if (values.magZ > magMaxAxisZ)
	    	magMaxAxisZ = values.magZ;
	}
#endif

    compass_scale_y = ((float)magMaxAxisX - magMinAxisX) / (magMaxAxisY - magMinAxisY);
    compass_scale_z = ((float)magMaxAxisX - magMinAxisX) / (magMaxAxisZ - magMinAxisZ);

    compass_offset_x = (magMaxAxisX - magMinAxisX) / 2 - magMaxAxisX;
    compass_offset_y = (((float)magMaxAxisY - magMinAxisY) / 2 - magMaxAxisY) * compass_scale_y;
    compass_offset_z = (((float)magMaxAxisZ - magMinAxisZ) / 2 - magMaxAxisZ) * compass_scale_z;
}