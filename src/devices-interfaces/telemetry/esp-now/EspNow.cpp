//
// Created by lenny on 03/01/24.
//
#ifdef ARDUINO

#include "EspNow.h"
#include "string.h"
#include "WiFi.h"

EspNow::EspNow() {
    numBytesAvailable = 0;
    index = 0;
}

EspNow::~EspNow() {

}

int8_t EspNow::init() {
    int8_t ret = 0;

    WiFi.mode(WIFI_STA);
    WiFi.setTxPower(WIFI_POWER_19_5dBm);
    if(esp_now_init() != 0)
        return -1;
    if(esp_wifi_config_espnow_rate(WIFI_IF_STA, WIFI_PHY_RATE_1M_L))
        return -1;
    if(esp_now_register_send_cb(&EspNow::OnDataSent) != 0)
        return -1;
    if(esp_now_register_recv_cb(&EspNow::OnDataRecv) != 0)
        return -1;

    return 0;
}

size_t EspNow::dataAvailable() {
    return numBytesAvailable;
}

size_t EspNow::readAllBytes(char *buf) {
    size_t len = rxBuffer.size();

    for (int i = 0; i < rxBuffer.size(); ++i) {
        buf[i] = rxBuffer.front();
        rxBuffer.pop();
    }

    return len;
}

void EspNow::sendBytes(char *buf, size_t len) {
    size_t numBytesToSend = len;
    size_t idx = 0;

    while(numBytesToSend > ESP_NOW_MAX_DATA_LEN) {
        esp_now_send(RECEIVER_ADDRESS, (uint8_t *)&buf[idx], ESP_NOW_MAX_DATA_LEN);
        numBytesToSend -= ESP_NOW_MAX_DATA_LEN;
        idx += ESP_NOW_MAX_DATA_LEN;
    }

    if(numBytesToSend > 0) {
        esp_now_send(RECEIVER_ADDRESS, (uint8_t *)&buf[idx], numBytesToSend);
    }
}

void EspNow::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {

}

void EspNow::OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    if(rxBuffer.size() >= MAX_BUFFER_SIZE)
        rxBuffer.pop();

    for (int i = 0; i < len; ++i) {
        rxBuffer.push((char)incomingData[i]);
    }
}

int8_t EspNow::deinit() {
    return 0;
}

#endif //ARDUINO