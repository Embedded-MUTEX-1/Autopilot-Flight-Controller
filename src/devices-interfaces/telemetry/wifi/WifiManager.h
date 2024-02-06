//
// Created by lenny on 13/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_WIFIMANAGER_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_WIFIMANAGER_H

#include "../WirelessInterface.h"
#include <string>
#include <WiFiServer.h>
#include <WiFi.h>
#include "../../../utils/utils.h"

const IPAddress LOCAL_IP(192, 168, 1, 100);
const IPAddress GATEWAY( 192, 168, 1, 100);
const IPAddress SUBNET(  255, 255, 255, 0);

const size_t MAX_SIZE = 600;

class WifiManager : public WirelessInterface {
public:
    WifiManager();
    ~WifiManager();

    int8_t init() override;
    int8_t deinit() override;

    size_t dataAvailable() override;
    size_t readAllBytes(char* buf) override;
    void sendBytes(char * buf, size_t len) override;
private:
    /* Allow to connect to a WIFI station by providing SSID and password in AP mode */
    int8_t startAccesPoint(const char *ssid, const char *password);
    void waitDataFromWifiApAvailable();
    void readDataFromWifiAp(char* buf);
    void extractSsidAndPasswd(char* buf, char *ssid, char *password);
    bool connectToWifiStation(const char *ssid, const char *password);
    WiFiUDP udp;
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_WIFIMANAGER_H
