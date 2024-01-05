//
// Created by lenny on 03/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ESPNOW_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ESPNOW_H
#ifdef ARDUINO

#include <cstdint>
#include <cstddef>
#include "esp_now.h"

// TODO REPLACE WITH YOUR RECEIVER MAC Address
const uint8_t RECEIVER_ADDRESS[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

class EspNow {
public:
    EspNow();
    ~EspNow();

    int8_t init();
    size_t dataAvailable();
    void readAllBytes(char * buf);
    void sendBytes(char * buf, size_t len);
private:
    static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

    static char rxBuffer[1000];
    static unsigned int index;
    static size_t numBytesAvailable;
};

#endif //ARDUINO
#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ESPNOW_H
