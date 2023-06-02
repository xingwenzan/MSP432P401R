#include <Arduino.h>
#include "msp432p401r.h"
void setup() {
    pinMode(13,INPUT);
    pinMode(BLUE_LED,OUTPUT);
    Serial.begin(9600);
}

void loop() {
//    int i = analogRead(13)/1023;   // 模拟信号读取需要滤杂波
    int i = digitalRead(13);   // 数字信号读取无须滤杂波
    digitalWrite(BLUE_LED,i);
    Serial.println(i);
//    delay(1000);   // 有 三角波   无 方波（占空比不是 0.5 且低电平存在杂波，滤去后正常）
}