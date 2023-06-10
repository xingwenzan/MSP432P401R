#include "Arduino.h"
void setup() {
    // 初始化串行通信
    Serial.begin(9600);
    pinMode(A8,INPUT);
}

void loop() {
    int tmp = analogRead(A8);
    Serial.println(tmp);
    delay(1000);
}
