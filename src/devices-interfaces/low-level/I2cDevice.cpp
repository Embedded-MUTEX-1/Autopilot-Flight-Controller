#include "I2cDevice.h"
#include <Arduino.h>
#include <Wire.h>

I2cDevice::I2cDevice()
{
    
}

I2cDevice::~I2cDevice()
{
    deinit();
}

int8_t I2cDevice::init()
{
    bool ret = Wire.begin(21, 22, 400000);
    return ret ? 0 : -1;
}

int8_t I2cDevice::deinit()
{
    Wire.end();
    return 0;
}

int8_t I2cDevice::readByte(uint8_t addr, char * value, bool stop)
{
    int8_t ret;

    ret = Wire.requestFrom(addr, 1);  
    while(Wire.available()) {
        *value = Wire.read();    // Receive a byte as character
    }
    return ret;
}

int8_t I2cDevice::readBytes(uint8_t addr, char * buf, size_t len, bool stop)
{
    int8_t ret;
    unsigned int count = 0;
    ret = Wire.requestFrom(addr, len);  
    while(Wire.available()) {
        buf[count] = Wire.read();    // Receive a byte as character
        count++;
    }
    return ret;
}

int8_t I2cDevice::writeByte(uint8_t addr, char value, bool stop)
{
    Wire.beginTransmission(addr); // transmit to device #4
    Wire.write(value);
    return Wire.endTransmission();    // stop transmitting
}

int8_t I2cDevice::writeBytes(uint8_t addr, char * buf, size_t len, bool stop)
{
    Wire.beginTransmission(addr); // transmit to device #4
    for (size_t i = 0; i < len; i++)
    {
        Wire.write(buf[i]);
    }
    return Wire.endTransmission();    // stop transmitting
}
