//
// Created by 86159 on 2023-06-12.
//
#include <Arduino.h>
#include "../lib/ili9320Test/ili9320.h"
#include "../lib/ili9320Test/ili9320_api.h"

#define LED_BUILTIN 78
u8 test1[] = {"0123456789ABCDEF"};
u8 sineWave[256];

void setup() {
    // put your setup code here, to run once:
    //Serial.begin(9600);
    //Serial.print("Serial OK");

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Lcd_Configuration();
    //Serial.print("Lcd_Configuration() OK");
    ili9320_Initializtion();
    digitalWrite(LED_BUILTIN, LOW);
    //Serial.print("ili9320_Initializtion() OK");
    for (int i = 0; i < 256; ++i) {
        sineWave[i] = 120*sin(2*PI*i/256)+120;
    }
}

void loop() {
    // put your main code here, to run repeatedly:

    ili9320_Test();
    GUI_Text(0,0,test1,16,BLACK,WHITE,0);   //ascii字符显示
    GUI_Square(20,30,40,YELLOW,0);          //正方形
    GUI_Rectangle(70,30,120,70,YELLOW,1);
    GUI_Line(0,0,240,240,GREEN);
    GUI_Circle(240,140,50,MAGENTA,1);
    LCD_ShowString(0,100,300,100,12,test1,BLACK,WHITE,0);
    LCD_ShowString(0,115,300,100,16,test1,BLUE2,GREY,0);
    LCD_ShowString(0,135,300,100,24,test1,RED,MAGENTA,1);
    LCD_ShowString(0,165,300,100,32,test1,YELLOW,CYAN,1);
    delay(1000);
    ili9320_Clear(WHITE);
    for (int i = 0; i < 255; ++i) {
        GUI_Line(i,sineWave[i],i+1,sineWave[i+1],RED);
    }
    while(1)
    {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(1000);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(1000);                       // wait for a second
    }
}
