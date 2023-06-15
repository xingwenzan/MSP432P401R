//
// Created by 86159 on 2023-06-12.
//
#include <Arduino.h>
#include "../lib/ili9320Test/ili9320.h"
#include "../lib/ili9320Test/ili9320_api.h"
#include "../lib/Keypad/src/Keypad.h"

#define LED_BUILTIN 78
u8 test1[] = {"0123456789ABCDEF"};
u8 sineWave[256];
u8 keyOut[30];
u8 blank[30];
int idx = 0;

const byte ROWS = 4; // 4行
const byte COLS = 4; // 4列

// 定义键盘上的按键字符
char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
};

// 将行引脚连接到 Arduino Nano 的数字引脚
byte rowPins[ROWS] = {23, 24, 25, 26};

// 将列引脚连接到 Arduino Nano 的数字引脚
byte colPins[COLS] = {27, 28, 29,30};

// 初始化键盘
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void lcdText(){
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
    ili9320_Clear(WHITE);   // 清屏
    for (int i = 0; i < 256; ++i) {   // 记录波
        sineWave[i] = 120*sin(2*PI*i/256)+120;
    }
    for (int i = 0; i < 255; ++i) {   // 画波
        GUI_Line(i,sineWave[i],i+1,sineWave[i+1],RED);
    }
    u8 string[] = {"!@#$%^&*()[]{};:'',.<>/?"};
    GUI_Text(0,120,string,24,RED,GREEN,0);
    LCD_ShowString(0,30,300,100,12,string,RED,GREEN,0);
}

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
    lcdText();
    for (int i = 0; i < 30; ++i) {
        blank[i] = ' ';
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    u8 key = keypad.getKey();
    if(key && key!='D'){
        keyOut[idx++] = key;
        GUI_Text(0,0,keyOut,idx,BLACK,WHITE,0);   //ascii字符显示
    } else if (key=='D'){
        GUI_Text(0,0,blank,idx,BLACK,WHITE,0);   //ascii字符显示
        idx = 0;
    }
}
