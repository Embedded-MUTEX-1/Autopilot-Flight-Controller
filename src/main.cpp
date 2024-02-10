#include <Arduino.h>
#include "utils/utils.h"
#include "modules/altitude/altitudeModule.h"
#include "modules/attitude/attitudeModule.h"
#include "modules/motors/motorsModule.h"
#include "modules/navigation/navigationModule.h"
#include "modules/receiver/receiverModule.h"
#include "modules/telemetry/telemetryModule.h"

#define LED_BUILTIN 2

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    xTaskCreate(
        receiverTask,   /* Function to implement the task */
        "test",         /* Name of the task */
        10000,          /* Stack size in words */
        NULL,           /* Task input parameter */
        1,              /* Priority of the task */
        NULL);
}

void loop() {
    delay_milis(10000000); 
}