//
// Created by lenny on 13/01/24.
//

#include "WifiManager.h"
#include "../../../config.h"

WifiManager::WifiManager() {
    udp = WiFiUDP();
}

WifiManager::~WifiManager() {

}

int8_t WifiManager::init() {
    char* ssid = NULL;
    char* password = NULL;
    char* recvPacket = NULL;

    do {
        startAccesPoint(WIFI_AP_SSID, WIFI_AP_PASSWD);
        waitDataFromWifiApAvailable();
        readDataFromWifiAp(recvPacket);
        extractSsidAndPasswd(recvPacket, ssid, password);
    } while (!connectToWifiStation(ssid, password));

    udp = WiFiUDP(); // For test
    if(udp.begin(UDP_PORT) != 1)
        return -1;

    return 0;
}

int8_t WifiManager::deinit() {
    return 0;
}

size_t WifiManager::dataAvailable() {
    return udp.parsePacket();
}

size_t WifiManager::readAllBytes(char *buf) {
    return udp.readBytesUntil('\n', buf, MAX_SIZE);;
}

void WifiManager::sendBytes(char *buf, size_t len) {
    udp.write((const uint8_t *)buf, len);
}

int8_t WifiManager::startAccesPoint(const char *ssid, const char *password) {
    if(!WiFi.softAPConfig(LOCAL_IP, GATEWAY, SUBNET))
        return -1;
    if(!WiFi.softAP(ssid, password))
        return -1;
    udp.begin(UDP_PORT);
    return 0;
}

void WifiManager::waitDataFromWifiApAvailable() {
    while(udp.parsePacket() == 0);
}

void WifiManager::readDataFromWifiAp(char *buf) {
    size_t len = udp.parsePacket();
    udp.readBytesUntil('\n', buf, len);
}

void WifiManager::extractSsidAndPasswd(char *buf, char *ssid, char *password) {
    strcpy(ssid, strtok(buf, ","));
    strcpy(password, strtok(NULL, ","));
}

bool WifiManager::connectToWifiStation(const char *ssid, const char *password) {
    uint16_t timeout = WIFI_CONNECTING_TIMEOUT;

    WiFi.softAPdisconnect();
    WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED) {
        if(timeout <= 0)
            return false;
        delay_milis(1);
        timeout--;
    }

    udp.stop();

    return true;
}
