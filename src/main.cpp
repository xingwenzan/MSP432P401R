// ���� ing

#include <Energia.h>

// ���Ⲩ����
volatile unsigned long freqCount = 0;
unsigned long lastCount = 0;
unsigned long frequency = 0;
const int countPin = 2; // the pin where we read the frequency
// բ�Ų�����
volatile unsigned long gateFreqCount = 0;
unsigned long gateLastCount = 0;
unsigned long gateFrequency = 0;
const int gateCountPin = 3; // the pin where we read the frequency

void countPulse()
{
    freqCount++;
}

void gateCountPulse()
{
    gateFreqCount++;
}

void setup()
{
    Serial.begin(9600); // Start serial communication at 9600 bps
    pinMode(countPin, INPUT_PULLUP);
    pinMode(gateCountPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(countPin), countPulse, RISING);   // �����ж�
    attachInterrupt(digitalPinToInterrupt(gateCountPin), gateCountPulse, RISING);   // բ���ж�
}

void loop()
{
    delay(1000); // Wait for 1000 millisecond(s)
    detachInterrupt(digitalPinToInterrupt(countPin));   // ��ͣ�����ж�
    detachInterrupt(digitalPinToInterrupt(gateCountPin));   // ��ͣբ���ж�
    frequency = freqCount - lastCount;   // ���Ⲩ�ġ�Ƶ�ʡ�
    gateFrequency = gateFreqCount - gateLastCount;   // բ�Ų��ġ�Ƶ�ʡ�
    unsigned long ans = frequency/gateFrequency*gateFrequency;
    lastCount = freqCount;
    gateLastCount = gateFreqCount;
    // ���
    Serial.print("AnsFrequency: ");
    Serial.println(ans);
    Serial.print("Frequency: ");
    Serial.println(frequency);
    Serial.print("GateFrequency: ");
    Serial.println(gateFrequency);
    Serial.println(" ");
    attachInterrupt(digitalPinToInterrupt(countPin), countPulse, RISING);   // ���������ж�
    attachInterrupt(digitalPinToInterrupt(gateCountPin), gateCountPulse, RISING);   // ����բ���ж�
}
