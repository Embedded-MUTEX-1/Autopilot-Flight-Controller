//
// Created by lenny on 05/01/24.
//

#include "Imu.h"

Imu::~Imu() {

}

uint8_t Imu::init() {
    if(!accel->begin())
        return -1;
    if(!gyro->begin())
        return -1;
    if(!gyro->setRange(Bmi088Gyro::RANGE_1000DPS))
        return -1;
    if(!accel->setRange(Bmi088Accel::RANGE_6G))
        return -1;
    if(!gyro->setOdr(Bmi088Gyro::ODR_400HZ_BW_47HZ))
        return -1;
    if(!accel->setOdr(Bmi088Accel::ODR_400HZ_BW_40HZ))
        return -1;
    if(!mag->init())
        return -1;

    return 0;
}

uint8_t Imu::deinit() {
    return 0;
}

uint8_t Imu::updateAndGetData(struct imuData &values) {
    int16_t magAxisX = 0;
    int16_t magAxisY = 0;
    int16_t magAxisZ = 0;

    gyro->readSensor();
    accel->readSensor();

    values.gyroRateRoll = gyro->getGyroX_deg() - gyroRateOffsetRoll; // deg/s
    values.gyroRatePitch = gyro->getGyroY_deg() - gyroRateOffsetPitch; // deg/s
    values.gyroRateYaw = gyro->getGyroZ_deg() - gyroRateOffsetYaw; // deg/s

    values.accRateRoll = (accel->getAccelX_mss()) - accRateOffsetRoll;
    values.accRatePitch = (accel->getAccelY_mss()) - accRateOffsetPitch;
    values.accRateYaw = (accel->getAccelZ_mss()) - accRateOffsetYaw;

    if(mag->isDataRdy()) {
        mag->read(&magAxisX, &magAxisY, &magAxisZ);

        magAxisY += compass_offset_y;                              //Add the y-offset to the raw value.
        magAxisY *= compass_scale_y;                               //Scale the y-value so it matches the other axis.
        magAxisZ += compass_offset_z;                              //Add the z-offset to the raw value.
        magAxisZ *= compass_scale_z;                               //Scale the z-value so it matches the other axis.
        magAxisX += compass_offset_x;                              //Add the x-offset to the raw value.

        values.magX = magAxisX;
        values.magY = magAxisY;
        values.magZ = magAxisZ;
    }

    return 0;
}

Imu::Imu(I2cDevice *i2c) {
    accel = new Bmi088Accel(*i2c, 0x19);
    gyro = new Bmi088Gyro(*i2c, 0x69);
    mag = new IST8310();
    mag->setI2cInterface(i2c);

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
    for (size_t i = 0; i < calibNum; i++)
    {
        gyro->readSensor();

        gyroRateOffsetRoll += gyro->getGyroX_deg();
        gyroRateOffsetPitch += gyro->getGyroY_deg();
        gyroRateOffsetYaw += gyro->getGyroZ_deg();

        delay_milis(4);
    }
    gyroRateOffsetRoll /= calibNum;
    gyroRateOffsetPitch /= calibNum;
    gyroRateOffsetYaw /= calibNum;
}

void Imu::magCalibration(uint16_t time) {
    int16_t magAxisX = 0;
    int16_t magAxisY = 0;
    int16_t magAxisZ = 0;

#if ENABLE_MAG_CALIBRATION == 1
    mag->dataRequest();
	while(!mag->isDataRdy());
	mag->read(&magAxisX, &magAxisY, &magAxisZ);           					   //Read the raw compass values.

	magMinAxisX = magAxisX;
	magMaxAxisX = magAxisX;

	magMinAxisY = magAxisY;
	magMaxAxisY = magAxisY;

	magMinAxisZ = magAxisZ;
	magMaxAxisZ = magAxisZ;

	for(int i = 0;i < time;i++) {                                                 //Stay in this loop until the pilot lowers the pitch stick of the transmitter.                                                 //Send telemetry data to the ground station.
	    mag->dataRequest();
	    while(!mag->isDataRdy());
		mag->read(&magAxisX, &magAxisY, &magAxisZ);           					   //Read the raw compass values.

	    magAxisX *= -1;
	    magAxisY *= -1;
	    //In the following lines the maximum and minimum compass values are detected and stored.
	    if (magAxisX < magMinAxisX)
	    	magMinAxisX = magAxisX;
	    if (magAxisX > magMaxAxisX)
	    	magMaxAxisX = magAxisX;

	    if (magAxisY < magMinAxisY)
	    	magMinAxisY = magAxisY;
	    if (magAxisY > magMaxAxisY)
	    	magMaxAxisY = magAxisY;

	    if (magAxisZ < magMinAxisZ)
	    	magMinAxisZ = magAxisZ;
	    if (magAxisZ > magMaxAxisZ)
	    	magMaxAxisZ = magAxisZ;
	}
#endif

    compass_scale_y = ((float)magMaxAxisX - magMinAxisX) / (magMaxAxisY - magMinAxisY);
    compass_scale_z = ((float)magMaxAxisX - magMinAxisX) / (magMaxAxisZ - magMinAxisZ);

    compass_offset_x = (magMaxAxisX - magMinAxisX) / 2 - magMaxAxisX;
    compass_offset_y = (((float)magMaxAxisY - magMinAxisY) / 2 - magMaxAxisY) * compass_scale_y;
    compass_offset_z = (((float)magMaxAxisZ - magMinAxisZ) / 2 - magMaxAxisZ) * compass_scale_z;
}