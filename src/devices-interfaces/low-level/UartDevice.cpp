#include "UartDevice.h"

UartDevice::UartDevice()
{

}

UartDevice::~UartDevice()
{
    deinit();
}

int8_t UartDevice::init(uint8_t uart_num, uint16_t txPin, uint16_t rxPin, unsigned long baud)
{
    switch (uart_num)
    {
        case 0:
            serialPort = &Serial0;
            break;
        case 1:
            serialPort = &Serial1;
            break;
        case 2:
            serialPort = &Serial2;
            break;
    }
    serialPort->setPins(rxPin, txPin);
    serialPort->begin(baud);
    return 0;
}

int8_t UartDevice::deinit()
{
    serialPort->end();
    return 0;
}

void UartDevice::flush() {
    serialPort->flush();
}

size_t UartDevice::numBytesAvailable()
{
    return serialPort->available();
}

char UartDevice::readByte()
{
    return serialPort->read();
}

void UartDevice::readBytesUntil(char * buf, char endChar, size_t len)
{
    serialPort->readBytesUntil(endChar, (uint8_t *)buf, len);
}

void UartDevice::readBytes(char * buf, size_t len)
{
    serialPort->readBytes(buf, len);
}

void UartDevice::writeByte(char value)
{
    serialPort->write(value);
}

void UartDevice::writeBytes(char * buf, size_t len)
{
    serialPort->write(buf, len);
}
