#include <Arduino.h>
#include "utils/utils.h"

#define LED_BUILTIN 2

void setup() {
    // TODO Init and start tasks
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay_milis(100); 
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay_milis(100);   
}