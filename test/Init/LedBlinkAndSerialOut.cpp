//
// Created by 86159 on 2023-05-31.
//
#include <Arduino.h>
#include "msp432p401r.h"
void setup() {
    pinMode(RED_LED,OUTPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(RED_LED, HIGH);       // sets the digital pin 13 on
    delay(1000);                  // waits for a second
    digitalWrite(RED_LED, LOW);        // sets the digital pin 13 off
    delay(1000);                  // waits for a second
    Serial.print("1\n");
}