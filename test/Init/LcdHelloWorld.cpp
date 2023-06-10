//
// Created by 86159 on 2023-06-10.
// y*x = 240*320
//
#include <Arduino.h>
#include "../lib/ili9320Test/ili9320.h"
#include "../lib/ili9320Test/ili9320_api.h"

#define LED_BUILTIN 78
u8 test1[] = {"0123456789ABCDEF"};
//u8 test2[] = {"2017年7月4日测试通过8/16位模式，2023年5月29日测试通过4线SPI位模式——辽宁大学李皓宇。"};
//u8 test3[] = {"完整区位码16*16字库，可以显示特殊字符：★●αβγⅠⅡⅢさしす∑∏≈≠"};

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
}

void loop() {
    // put your main code here, to run repeatedly:

    ili9320_Test();
    GUI_Text(0,0,test1,16,BLACK,WHITE,0);   //ascii字符显示
    GUI_Square(20,30,40,YELLOW,0);          //正方形
    GUI_Rectangle(70,30,120,70,YELLOW,1);
    GUI_Line(0,0,240,240,GREEN);
    GUI_Circle(240,140,50,MAGENTA,1);
    //GUI_Message(test2,150,5,150,310,WHITE,BLACK,0);
    //GUI_Message(test3,20,200,0,320,BLUE,YELLOW,0);
    LCD_ShowString(0,100,300,100,12,test1,BLACK,WHITE,0);
    LCD_ShowString(0,115,300,100,16,test1,BLUE2,GREY,0);
    LCD_ShowString(0,135,300,100,24,test1,RED,MAGENTA,1);
    LCD_ShowString(0,165,300,100,32,test1,YELLOW,CYAN,1);

    while(1)
    {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        //delay(1000);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        //delay(1000);                       // wait for a second
    }
}
