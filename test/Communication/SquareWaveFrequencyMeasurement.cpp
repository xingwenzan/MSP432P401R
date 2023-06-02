//
// Created by 86159 on 2023-06-02.
// 方波测频   信号接收及计算部分
//

#include <Arduino.h>
#include "msp432p401r.h"

volatile int cnt;

// 得到脉冲数
void getPulse(){
    cnt++;
}

int getF(){
    int f1,f2;
    cnt = 0;
    delay(1000);
    noInterrupts();
    f1 = cnt;
    interrupts();
    delay(1000);
    f2 = cnt;
    return f2-f1;
}

// 直接测周期    单位 (1e-3)s
unsigned long getT() {
    unsigned long t1, t2;
    int u1, u2;
    u1 = digitalRead(13);
    delay(1);
    u2 = digitalRead(13);
    while (!(u1 == HIGH && u2 == LOW)) {
        u1 = digitalRead(13);
        delay(1);
        u2 = digitalRead(13);
    }
    t1 = micros();

    u1 = digitalRead(13);
    delay(1);
    u2 = digitalRead(13);
    while (!(u1 == HIGH && u2 == LOW)) {
        u1 = digitalRead(13);
        delay(1);
        u2 = digitalRead(13);
    }
    t2 = micros();
    return t2 - t1;
}

void setup() {
    pinMode(13, INPUT);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(13),getPulse,FALLING);
}

void loop() {
    unsigned long t = getT();
    int f = getF();
    Serial.println(t);
    Serial.println(f);
    Serial.println(" ");
//    delay(3000);
}