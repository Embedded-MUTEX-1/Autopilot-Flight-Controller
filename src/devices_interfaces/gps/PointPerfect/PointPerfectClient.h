#ifndef AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_POINTPERFECT_CLIENT_H
#define AUTOPILOT_FLIGHT_CONTROLLER_SOFTWARE_POINTPERFECT_CLIENT_H

#include <cstdint>
#include <cstddef>
#include <Arduino.h>
#include "WiFiClientSecure.h"
#include "ArduinoMqttClient.h"

class PointPerfectClient {
public:
    PointPerfectClient();
    ~PointPerfectClient();

    int8_t init();
    void process();
    int getMessageLen();
    uint8_t* getMessage();
private:
    int8_t subscribeToTopics();
    int messageSize = 0;
    uint8_t buf[5000];

    WiFiClientSecure wiFiClientSecure;
    MqttClient client = MqttClient(&wiFiClientSecure);
};

#endif

