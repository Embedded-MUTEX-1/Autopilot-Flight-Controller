//
// Created by lenny on 12/01/24.
//

#include "Telemetry.h"
#include "../../../lib/ArduinoJson/ArduinoJson.h"

Telemetry::Telemetry() {

}

Telemetry::~Telemetry() {

}

int8_t Telemetry::init() {
    return wifiManager.init();
}

int8_t Telemetry::deinit() {
    return wifiManager.deinit();
}

int8_t Telemetry::sendTelemetryValues(imuData &imu, attitudeData &attitude, altitudeData &altitude, gpsData &gps,
                                      naviagtionData &navigation, struct pidOutput &pid, receiverData &receiver, motorsData &motors, struct commanderState commander) {
    StaticJsonDocument<1200> documentTx;

    documentTx["roll"].set(attitude.roll);
    documentTx["pitch"].set(attitude.pitch);
    documentTx["yaw"].set(attitude.yaw);

    documentTx["gyroRoll"].set(imu.gyroRateRoll);
    documentTx["gyroPitch"].set(imu.gyroRatePitch);
    documentTx["gyroYaw"].set(imu.gyroRateYaw);

    documentTx["accRoll"].set(imu.accRateRoll);
    documentTx["accPitch"].set(imu.accRatePitch);
    documentTx["accYaw"].set(imu.accRateYaw);

    documentTx["loopTime"].set(pid.loopRate);
    documentTx["alt"].set(altitude.alt);
    documentTx["vBat"].set(motors.vBat);

    documentTx["lat"].set(gps.lat);
    documentTx["lon"].set(gps.lon);

    documentTx["lat_home"].set(navigation.latitude_home);
    documentTx["lon_home"].set(navigation.longitude_home);

    documentTx["status"].set(commander.state);

    for (int i = 0;i < NUMBER_OF_MOTORS;i++) {
        documentTx["mot"][i] = motors.mot[i];
    }

    for (int i = 0;i < NUMBER_OF_CHANNELS;i++) {
        documentTx["ch"][i] = receiver.chan[i];
    }

    char output[800];
    serializeJson(documentTx, output);

    wifiManager.sendBytes(output, strlen(output));

    documentTx.clear();
    return 0;
}

bool Telemetry::isConfigDataAvailable() {
    if(wifiManager.dataAvailable() > 0)
        return true;

    return false;
}

int8_t Telemetry::getConfigData(struct attitudeConfig *attitude, struct pidConfig *pid, struct pidAltitudeConfig *altitude,
                         struct pidNavigationConfig *nav, struct motorsConfig *motors, struct commanderState commander) {
    char recvBuffer[800];
    StaticJsonDocument<1200> documentRx;

    wifiManager.readAllBytes(recvBuffer);

    DeserializationError err = deserializeJson(documentRx, recvBuffer);

    if(err != DeserializationError::Ok)
        return -1;

    commander.state = (enum droneState)documentRx["state"].as<int>();

    attitude->offsetRoll = documentRx["roll"].as<float>();
    attitude->offsetPitch = documentRx["pitch"].as<float>();
    attitude->offsetYaw = documentRx["yaw"].as<float>();

    pid->proll = documentRx["proll"].as<float>();
    pid->ppitch = documentRx["ppitch"].as<float>();
    pid->pyaw = documentRx["pyaw"].as<float>();

    pid->iroll = documentRx["iroll"].as<float>();
    pid->ipitch = documentRx["ipitch"].as<float>();
    pid->iyaw = documentRx["iyaw"].as<float>();

    pid->droll = documentRx["droll"].as<float>();
    pid->dpitch = documentRx["dpitch"].as<float>();
    pid->dyaw = documentRx["dyaw"].as<float>();

    attitude->param1 = documentRx["param1"].as<float>();
    attitude->param2 = documentRx["param2"].as<float>();


    for(int i = 0;i < NUMBER_OF_MOTORS;i++)
        motors->mot[i] = documentRx["mot"][i].as<uint16_t>();

    return 0;
}
