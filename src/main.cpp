#include "app_tasks.h"
#include "utils/utils.h"
#include "resources/nodes.h"
#include "devices-interfaces/low-level/IoDevice.h"
#include <Arduino.h>

IoDevice iOpins;
struct commanderState state;

void setup() {
    iOpins.init();
    iOpins.setPinMode(LED_PIN, false);

    xTaskCreatePinnedToCore(
        receiverTask,   /* Function to implement the task */
        "receiver",         /* Name of the task */
        10000,          /* Stack size in words */
        nullptr,           /* Task input parameter */
        2,              /* Priority of the task */
        nullptr,
        0);

    xTaskCreatePinnedToCore(
        attitudeTask,   /* Function to implement the task */
        "attitude",         /* Name of the task */
        10000,          /* Stack size in words */
        nullptr,           /* Task input parameter */
        2,              /* Priority of the task */
        nullptr,
        0);

    xTaskCreatePinnedToCore(
        altitudeTask,   /* Function to implement the task */
        "altitude",         /* Name of the task */
        10000,          /* Stack size in words */
        nullptr,           /* Task input parameter */
        2,              /* Priority of the task */
        nullptr,
        0);

    xTaskCreatePinnedToCore(
        navigationTask,   /* Function to implement the task */
        "navigation",         /* Name of the task */
        10000,          /* Stack size in words */
        nullptr,           /* Task input parameter */
        1,              /* Priority of the task */
        nullptr,
        0);

    xTaskCreatePinnedToCore(
        commanderTask,   /* Function to implement the task */
        "commander",         /* Name of the task */
        10000,          /* Stack size in words */
        nullptr,           /* Task input parameter */
        2,              /* Priority of the task */
        nullptr,
        1);
    
    xTaskCreatePinnedToCore(
        controllerTask,   /* Function to implement the task */
        "controller",         /* Name of the task */
        10000,          /* Stack size in words */
        nullptr,           /* Task input parameter */
        2,              /* Priority of the task */
        nullptr,
        1);

    xTaskCreatePinnedToCore(
        motorsTask,   /* Function to implement the task */
        "motors",         /* Name of the task */
        10000,          /* Stack size in words */
        nullptr,           /* Task input parameter */
        2,              /* Priority of the task */
        nullptr,
        1);

    xTaskCreatePinnedToCore(
        telemetryTask,   /* Function to implement the task */
        "telemetry",         /* Name of the task */
        10000,          /* Stack size in words */
        nullptr,           /* Task input parameter */
        1,              /* Priority of the task */
        nullptr,
        1);
}

void loop() {
    commanderStateNode.get(state);
    if(state.state != DISARMED) {
        iOpins.setPin(LED_PIN, true);
        delay_milis(100);
        iOpins.setPin(LED_PIN, false);
        delay_milis(100); 
    }
}