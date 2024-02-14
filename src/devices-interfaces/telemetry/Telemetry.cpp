//
// Created by lenny on 12/01/24.
//

#include "Telemetry.h"
#include "../../../lib/ArduinoJson/ArduinoJson.h"

Telemetry::Telemetry() {
    wifiManager = new WifiManager();
}

Telemetry::~Telemetry() {

}

int8_t Telemetry::init() {
    return wifiManager->init();
}

int8_t Telemetry::deinit() {
    return wifiManager->deinit();
}

int8_t Telemetry::sendConfigValues(
    struct attitudeConfig &attitudeConf,
    struct pidConfig &pidConf,
    struct pidAltitudeConfig &altitudeConf,
    struct pidNavigationConfig &navConf
) {
    StaticJsonDocument<1500> documentTx;

    documentTx["isInitConfig"].set(1);

    documentTx["roll"].set(attitudeConf.offsetRoll);
    documentTx["pitch"].set(attitudeConf.offsetPitch);
    documentTx["yaw"].set(attitudeConf.offsetYaw);

    documentTx["proll"].set(pidConf.proll);
    documentTx["ppitch"].set(pidConf.ppitch);
    documentTx["pyaw"].set(pidConf.pyaw);

    documentTx["iroll"].set(pidConf.iroll);
    documentTx["ipitch"].set(pidConf.ipitch);
    documentTx["iyaw"].set(pidConf.iyaw);;

    documentTx["droll"].set(pidConf.droll);
    documentTx["dpitch"].set(pidConf.dpitch);
    documentTx["dyaw"].set(pidConf.dyaw);

    documentTx["pAlt"].set(altitudeConf.pAltitude);
    documentTx["iAlt"].set(altitudeConf.iAltitude);
    documentTx["dAlt"].set(altitudeConf.dAltitude);

    documentTx["pnav"].set(navConf.pnav);
    documentTx["inav"].set(navConf.inav);
    documentTx["dnav"].set(navConf.dnav);

    documentTx["param1"].set(attitudeConf.param1);
    documentTx["param2"].set(attitudeConf.param2);

    char output[1500];
    serializeJson(documentTx, output);

    wifiManager->sendBytes(output, strlen(output));

    documentTx.clear();
    return 0;
}

int8_t Telemetry::sendTelemetryValues(
    struct attitudeData &attitude, 
    struct altitudeData &altitude, 
    struct positionData &position,
    struct pidOutput &pid, 
    struct receiverData &receiver, 
    struct motorsData &motors, 
    struct commanderState &commander, 
    uint64_t timestamp
) {
    StaticJsonDocument<1500> documentTx;

    documentTx["roll"].set(attitude.roll);
    documentTx["pitch"].set(attitude.pitch);
    documentTx["yaw"].set(attitude.yaw);

    documentTx["gyroRoll"].set(attitude.gyroRateRoll);
    documentTx["gyroPitch"].set(attitude.gyroRatePitch);
    documentTx["gyroYaw"].set(attitude.gyroRateYaw);

    documentTx["accRoll"].set(attitude.accRateRoll);
    documentTx["accPitch"].set(attitude.accRatePitch);
    documentTx["accYaw"].set(attitude.accRateYaw);

    documentTx["loopTime"].set(pid.loopPeriod);
    documentTx["timestamp"].set(timestamp);
    documentTx["alt"].set(altitude.alt);
    documentTx["vBat"].set(motors.vBat);

    documentTx["lat"].set(position.lat);
    documentTx["lon"].set(position.lon);

    documentTx["status"].set(commander.state);

    for (int i = 0;i < NUMBER_OF_MOTORS;i++) {
        documentTx["mot"][i] = motors.mot[i];
    }

    for (int i = 0;i < NUMBER_OF_CHANNELS;i++) {
        documentTx["ch"][i] = receiver.chan[i];
    }

    char output[1500];
    serializeJson(documentTx, output);

    wifiManager->sendBytes(output, strlen(output));

    documentTx.clear();
    return 0;
}

bool Telemetry::isConfigDataAvailable() {
    if(wifiManager->dataAvailable() > 0)
        return true;
    return false;
}

void Telemetry::resetRecvBuffer() {
    char recvBuffer[1000];
    wifiManager->readAllBytes(recvBuffer);
}

int8_t Telemetry::getConfigData(
    struct attitudeConfig *attitude,
    struct pidConfig *pid,
    struct pidAltitudeConfig *altitude,
    struct pidNavigationConfig *navConf,
    struct motorsSetpoint *motors,
    struct navigationSetpoint *navSetpoint,
    struct commanderState *commander) 
{
    char recvBuffer[1000];
    StaticJsonDocument<1200> documentRx;

    wifiManager->readAllBytes(recvBuffer);

    //ESP_LOGE("DEBUG", "Config received : %s", recvBuffer);

    DeserializationError err = deserializeJson(documentRx, recvBuffer);

    if(err != DeserializationError::Ok)
        return -1;

    attitude->newConfig = true;
    pid->newConfig = true;
    altitude->newConfig = true;
    navConf->newConfig = true;

    commander->state = (enum droneState)documentRx["status"].as<int>();

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

    altitude->pAltitude = documentRx["pAlt"].as<float>();
    altitude->iAltitude = documentRx["iAlt"].as<float>();
    altitude->dAltitude = documentRx["dAlt"].as<float>();

    navConf->pnav = documentRx["pnav"].as<float>();
    navConf->inav = documentRx["inav"].as<float>();
    navConf->dnav = documentRx["dnav"].as<float>();

    navSetpoint->lat = documentRx["lat"].as<float>();
    navSetpoint->lon = documentRx["lon"].as<float>();

    attitude->param1 = documentRx["param1"].as<float>();
    attitude->param2 = documentRx["param2"].as<float>();


    for(int i = 0;i < NUMBER_OF_MOTORS;i++)
        motors->mot[i] = documentRx["mot"][i].as<uint16_t>();

    return 0;
}
