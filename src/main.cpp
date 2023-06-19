// 调整 ing

#include <Energia.h>

// 被测波参数
volatile unsigned long freqCount = 0;
unsigned long lastCount = 0;
unsigned long frequency = 0;
const int countPin = 2; // the pin where we read the frequency
// 闸门波参数
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
    attachInterrupt(digitalPinToInterrupt(countPin), countPulse, RISING);   // 被测中断
    attachInterrupt(digitalPinToInterrupt(gateCountPin), gateCountPulse, RISING);   // 闸门中断
}

void loop()
{
    delay(1000); // Wait for 1000 millisecond(s)
    detachInterrupt(digitalPinToInterrupt(countPin));   // 暂停被测中断
    detachInterrupt(digitalPinToInterrupt(gateCountPin));   // 暂停闸门中断
    frequency = freqCount - lastCount;   // 被测波的“频率”
    gateFrequency = gateFreqCount - gateLastCount;   // 闸门波的“频率”
    unsigned long ans = frequency/gateFrequency*gateFrequency;
    lastCount = freqCount;
    gateLastCount = gateFreqCount;
    // 输出
    Serial.print("AnsFrequency: ");
    Serial.println(ans);
    Serial.print("Frequency: ");
    Serial.println(frequency);
    Serial.print("GateFrequency: ");
    Serial.println(gateFrequency);
    Serial.println(" ");
    attachInterrupt(digitalPinToInterrupt(countPin), countPulse, RISING);   // 重启被测中断
    attachInterrupt(digitalPinToInterrupt(gateCountPin), gateCountPulse, RISING);   // 重启闸门中断
}
