//
// Created by lenny on 03/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ESPNOW_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ESPNOW_H
#ifdef ARDUINO

#include <cstdint>
#include <cstddef>
#include "esp_now.h"
#include "devices-interfaces/telemetry/WirelessInterface.h"
#include <queue>

// TODO REPLACE WITH YOUR RECEIVER MAC Address
const uint8_t RECEIVER_ADDRESS[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const size_t MAX_BUFFER_SIZE = 1000;

class EspNow : public WirelessInterface {
public:
    EspNow();
    ~EspNow();

    int8_t init() override;
    int8_t deinit() override;
    size_t dataAvailable() override;
    size_t readAllBytes(char * buf) override;
    void sendBytes(char * buf, size_t len) override;
private:
    static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

    static std::queue<char> rxBuffer;
    static unsigned int index;
    static size_t numBytesAvailable;
};

#endif //ARDUINO
#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_ESPNOW_H
