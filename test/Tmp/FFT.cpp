//
// Created by 86159 on 2023-06-12.
//
#include "Arduino.h"
#include "../lib/arduinoFFT/src/arduinoFFT.h"

#define SAMPLES 128  //FFT库需要的样本数量，必须为2的次幂
#define SAMPLING_FREQUENCY 1000 //最大测量频率的两倍

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES]; //创建存储实部和虚部的数组
double vImag[SAMPLES]; //只有在FFT后才会使用

arduinoFFT FFT = arduinoFFT();

void setup() {
    Serial.begin(9600);
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

void loop() {
    /*收集样本数据*/
    for(int i=0; i<SAMPLES; i++) {
        microseconds = micros();//当前时间
        vReal[i] = analogRead(A11);
        vImag[i] = 0;
        /*等待满足采样频率的时间*/
        while(micros() - microseconds < sampling_period_us){
            //等待...
        }
    }

    /*执行FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

    /*打印结果*/
    Serial.println(peak); //输出最大的频率

    delay(2000); //等待2秒
}
