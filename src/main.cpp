#include <Energia.h>

volatile unsigned long pulseCount = 0;
unsigned long lastCount = 0;
unsigned long frequency = 0;

const int signalPin = 2; // 测量信号的引脚
const int gatePin = 3; // 闸门信号的引脚

void countPulse()
{
    pulseCount++;
}

void resetCounter()
{
    frequency = pulseCount - lastCount;
    lastCount = pulseCount;
    Serial.print("Frequency: ");
    Serial.println(frequency);
}

void setup()
{
    Serial.begin(9600);
    pinMode(signalPin, INPUT_PULLUP);
    pinMode(gatePin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(signalPin), countPulse, RISING);
    attachInterrupt(digitalPinToInterrupt(gatePin), resetCounter, RISING);
}

void loop()
{
    // 这里不需要做任何事情，所有的工作都在中断服务例程中完成
}
