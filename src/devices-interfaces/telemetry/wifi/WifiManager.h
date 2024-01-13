//
// Created by lenny on 13/01/24.
//

#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_WIFIMANAGER_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_WIFIMANAGER_H

#include "../WirelessInterface.h"
#include <string>

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
    int8_t startAccesPoint(std::string ssid, std::string password);
    bool waitDataFromWifiApAvailable();
    void readDataFromWifiAp(char* buf);
    void extractSsidAndPasswd(char* buf, std::string ssid, std::string password);
    void connectToWifiStation(std::string ssid, std::string password);
};


#endif //AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_WIFIMANAGER_H
