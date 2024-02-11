#include <Arduino.h>
#include "utils/utils.h"
#include "resources/nodes.h"
#include "modules/altitude/altitudeModule.h"
#include "modules/attitude/attitudeModule.h"
#include "modules/motors/motorsModule.h"
#include "modules/navigation/navigationModule.h"
#include "modules/receiver/receiverModule.h"
#include "modules/telemetry/telemetryModule.h"
#include "modules/commander/commanderModule.h"
#include "modules/controller/controllerModule.h"

#define LED_BUILTIN 2

void setup() {
    pinMode(LED_PIN, OUTPUT);

    xTaskCreatePinnedToCore(
        receiverTask,   /* Function to implement the task */
        "receiver",         /* Name of the task */
        10000,          /* Stack size in words */
        NULL,           /* Task input parameter */
        2,              /* Priority of the task */
        NULL,
        0);

    xTaskCreatePinnedToCore(
        attitudeTask,   /* Function to implement the task */
        "attitude",         /* Name of the task */
        10000,          /* Stack size in words */
        NULL,           /* Task input parameter */
        2,              /* Priority of the task */
        NULL,
        0);

    xTaskCreatePinnedToCore(
        navigationTask,   /* Function to implement the task */
        "navigation",         /* Name of the task */
        10000,          /* Stack size in words */
        NULL,           /* Task input parameter */
        1,              /* Priority of the task */
        NULL,
        0);

    xTaskCreatePinnedToCore(
        commanderTask,   /* Function to implement the task */
        "commander",         /* Name of the task */
        10000,          /* Stack size in words */
        NULL,           /* Task input parameter */
        2,              /* Priority of the task */
        NULL,
        1);
    
    xTaskCreatePinnedToCore(
        controllerTask,   /* Function to implement the task */
        "controller",         /* Name of the task */
        10000,          /* Stack size in words */
        NULL,           /* Task input parameter */
        2,              /* Priority of the task */
        NULL,
        1);

    xTaskCreatePinnedToCore(
        motorsTask,   /* Function to implement the task */
        "motors",         /* Name of the task */
        10000,          /* Stack size in words */
        NULL,           /* Task input parameter */
        2,              /* Priority of the task */
        NULL,
        1);

    xTaskCreatePinnedToCore(
        telemtryTask,   /* Function to implement the task */
        "telemetry",         /* Name of the task */
        10000,          /* Stack size in words */
        NULL,           /* Task input parameter */
        1,              /* Priority of the task */
        NULL,
        1);
}

void loop() {
    struct commanderState state;
    commanderStateNode.get(state);

    if(state.state != DISARMED) {
        digitalWrite(LED_PIN, HIGH);
        delay_milis(100); 
        digitalWrite(LED_PIN, LOW);
        delay_milis(100); 
    }
}