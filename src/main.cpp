#include "Arduino.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    int v = digitalRead(2);
    Serial.println(v);
    delay(2000); //µÈ´ý2Ãë
}
