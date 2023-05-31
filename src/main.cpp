#include <Arduino.h>
#include "msp432p401r.h"
void setup() {
    pinMode(GREEN_LED,OUTPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(GREEN_LED, HIGH);       // sets the digital pin 13 on
    delay(1000);                  // waits for a second
    digitalWrite(GREEN_LED, LOW);        // sets the digital pin 13 off
    delay(1000);                  // waits for a second
    Serial.print("1\n");
}