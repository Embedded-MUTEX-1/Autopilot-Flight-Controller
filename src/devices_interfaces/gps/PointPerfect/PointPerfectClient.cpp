#include "PointPerfectClient.h"
#include "mqtt_config.h"
#include "esp_log.h"
#include "config.h"
#include "utils/utils.h"

PointPerfectClient::PointPerfectClient() {

}

PointPerfectClient::~PointPerfectClient() {

}

int8_t PointPerfectClient::init() {
    while(!WiFi.isConnected());

    wiFiClientSecure.setCACert(CA_CERT);
    wiFiClientSecure.setCertificate(CERT);
    wiFiClientSecure.setPrivateKey(CLIENT_KEY);

    client.setId(CLIENT_ID);
    client.connect(SERVER_URI, SERVER_PORT);

    subscribeToTopics();

    return 0;
}

void PointPerfectClient::process() {
    memset(buf, '\0', sizeof(buf));
    messageSize = client.parseMessage();
    if(messageSize) {
        while (client.available()) {
            client.read(buf, messageSize);
        }
    }
}

int8_t PointPerfectClient::subscribeToTopics() {
    client.subscribe(DATA_TOPIC);
    return 0;
}

int PointPerfectClient::getMessageLen() {
    return messageSize;
}

uint8_t* PointPerfectClient::getMessage() {
    return buf;
}