#include <Energia.h>

volatile unsigned long pulseCount = 0;
unsigned long lastCount = 0;
unsigned long frequency = 0;

const int signalPin = 2; // �����źŵ�����
const int gatePin = 3; // բ���źŵ�����

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
    // ���ﲻ��Ҫ���κ����飬���еĹ��������жϷ������������
}
