#ifndef __UARTDEVICE_H__
#define __UARTDEVICE_H__

#include <cstdint>
#include <cstddef>
#include <Arduino.h>

class UartDevice {
public:
    UartDevice();
    ~UartDevice();

    int8_t init(uint8_t uartNum, uint16_t txPin, uint16_t rxPin, unsigned long baud);
    int8_t deinit();

    size_t numBytesAvailable();
    char readByte();
    void readBytesUntil(char * buf, char endChar, size_t len);
    void readBytes(char * buf, size_t len);
    void writeByte(char value);
    void writeBytes(char * buf, size_t len);
private:
    HardwareSerial* serialPort;
};

#endif // __UARTDEVICE_H__