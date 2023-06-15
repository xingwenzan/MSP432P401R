//
// Created by 86159 on 2023-06-15.
// 调节 ing
//
#include "Arduino.h"
#include "../lib/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "../lib/Keypad/src/Keypad.h"
#include "../lib/arduinoFFT/src/arduinoFFT.h"
//#include "../lib/ili9320Test/ili9320.h"
//#include "../lib/ili9320Test/ili9320_api.h"

typedef struct {
    int waveType;
    float waveFreq;
    float samplingFreq;
    float waveDc;
    float waveAmpl;
    int waveSamples;
    int photo;
} WaveformParameters;   // 波形参数结构体

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

// 初始化 1602 设置 1602 液晶显示屏的 I2C 地址，宽度和高度
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 初始化波形参数
WaveformParameters wp;

// 波形储存
double wave[128];
int idx = 0;

// 参数输入方法
String parameterRead() {
    /*
     * 按键字符含义定义
     * 数字 - 数字
     * A - 加/上（加减/上下）
     * B - 右（左右）
     * C - 清空/归零/恢复默认值
     * D - 退格/删除（backspace/delete)
     * * - 小数点/正负号
     * # - 确认
     */
    digitalWrite(RED_LED, LOW);
    // 解析输入命令
    String tmp = "";
    int point = 0;   // tmp 的索引
    while (true) {
        lcd.setCursor(point, 1);
        lcd.blink();
        lcd.cursor();
        // 读取按键输入，赋值的主体部分
        char key = keypad.getKey();
        // 判定输入进行操作
        if (isdigit(key)) {
            if (point < tmp.length()) {
                tmp[point] = key;
            } else {
                tmp += key;
            }
            lcd.setCursor(point, 1);
            lcd.print(key);
            point++;
        } else {
            switch (key) {
                case 'A':
                    tmp[point] = (tmp[point] + 1 - '0') % 10 + '0';
                    lcd.setCursor(point, 1);
                    lcd.print(tmp[point]);
                    break;
                case 'B':
                    point = (point + 1) % (tmp.length() + 1);
                    break;
                case 'C':
                    tmp = "";
                    point = 0;
                    lcd.clear();
                    break;
                case 'D':
                    point--;
                    for (int j = point; j < tmp.length(); ++j) {
                        lcd.setCursor(j, 1);
                        lcd.print(" ");
                    }
                    tmp = tmp.substring(0, point);
                    break;
                case '*':
                    if (point == 0) {
                        if (point < tmp.length()) {
                            tmp[point] = '-';
                        } else {
                            tmp += '-';
                        }
                        lcd.setCursor(point, 1);
                        lcd.print('-');
                        point++;
                    } else {
                        if (point < tmp.length()) {
                            tmp[point] = '.';
                        } else {
                            tmp += '.';
                        }
                        lcd.setCursor(point, 1);
                        lcd.print('.');
                        point++;
                    }

                    break;
                case '#':
                    lcd.clear();
                    digitalWrite(RED_LED, HIGH);
                    return tmp;
                default:
                    break;
            }
        }
    }
}

// 频谱图数据获得
void fft() {   // 结果有误
    // 初始化 FFT 对象
    double vImag[wp.waveSamples];
    memset(vImag, 0, wp.waveSamples * sizeof(double));
    arduinoFFT FFT = arduinoFFT(wave, vImag, wp.waveSamples, wp.samplingFreq);
//    int availableMemory = freeMemory();
//    Serial.print("Free memory: ");
//    Serial.print(availableMemory);
//    Serial.println(" bytes");
    /* 对数据执行 FFT */
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();

//    Serial.print("Free memory: ");
//    Serial.print(availableMemory);
//    Serial.println(" bytes");
    /* 输出频谱图数据到串口绘图器 */
    for (int i = 0; i < (wp.waveSamples >> 1); i++) {
//        double frequency = (i * 1.0 * samplingFreq) / waveSamples;
//        Serial.print(frequency);
//        Serial.print(",");
        Serial.println(wave[i]);
    }
//    Serial.println(FFT.MajorPeak());
//    while (1);
}

// 波形获取
void getWave() {
    idx = 0;
    for (int i = 0; i < wp.waveSamples; i++) {
        float t = (float) i / wp.samplingFreq;  // 计算当前时间
        double v = wp.waveDc;  // 加上直流分量
        if (wp.waveType == 0) {   // 正弦波
            v += sin(2 * PI * t * wp.waveFreq) * wp.waveAmpl;
        } else if (wp.waveType == 1) {   // 方波
            v += wp.waveAmpl * (fmod(t * wp.waveFreq, 1) < 0.5 ? -1 : 1);
        } else if (wp.waveType == 2) {   // 三角波
            double trianglePhase = fmod(t * wp.waveFreq, 1);
            v += wp.waveAmpl * (2 * fabs(2 * trianglePhase - 1) - 1);
//            v += waveAmpl * (trianglePhase < 0.5 ? 4 * trianglePhase - 1 : 3 - 4 * trianglePhase);
        } else if (wp.waveType == 3) {   // 锯齿波
            double sawtoothPhase = fmod(t * wp.waveFreq, 1);
            v += wp.waveAmpl * (2 * sawtoothPhase - 1);
        }
        wave[idx++] = v;
//        Serial.println(v);
    }
}

// 波形绘制
void draw() {
    if (wp.photo == 0) {
        digitalWrite(BLUE_LED, LOW);
        for (int i = 0; i < idx; ++i) {
            Serial.println(wave[i]);
        }
    } else {
        digitalWrite(BLUE_LED, HIGH);
        fft();
    }
}

// 波形参数输入
void waveSet() {
    // 解析输入命令
    int parameter = 0;   //正在输入的参数 0~6 分别对应变量定义里的七个参数
    while (parameter <= 6) {
        // lcd 显示当前正在读取的参数
        lcd.clear();
        lcd.setCursor(0, 0);
        switch (parameter) {
            case 0:
                lcd.print("Wave Type:");
                break;
            case 1:
                lcd.print("Wave Freq:");
                break;
            case 2:
                lcd.print("Samp Freq:");
                break;
            case 3:
                lcd.print("Wave Dc:  ");
                break;
            case 4:
                lcd.print("Wave Ampl:");
                break;
            case 5:
                lcd.print("Wave Samp:");
                break;
            case 6:
                lcd.print("Img Mode: ");
                break;
            default:
                break;
        }
        String tmp = parameterRead();
        switch (parameter) {
            case 0:
                wp.waveType = tmp[tmp.length() - 1]-'0';
                break;
            case 1:
                wp.waveFreq = tmp.toFloat();
                break;
            case 2:
                wp.samplingFreq = tmp.toFloat();
                break;
            case 3:
                wp.waveDc = tmp.toFloat();
                break;
            case 4:
                wp.waveAmpl = tmp.toFloat();
                break;
            case 5:
                wp.waveSamples = (int) tmp.toFloat();
                break;
            case 6:
                wp.photo = (int) tmp.toFloat();
                break;
            default:
                break;
        }
        parameter++;
    }
}

void setup() {
    // 初始化串行通信
    Serial.begin(9600);
    // 初始化 LCD
    lcd.init();
    lcd.backlight();
    // 在 LCD 上显示按键字符
    lcd.setCursor(0, 0);
    // 初始化 LED 灯
    pinMode(GREEN_LED, OUTPUT);
    digitalWrite(GREEN_LED, HIGH);
    pinMode(RED_LED, OUTPUT);
    digitalWrite(RED_LED, HIGH);
    pinMode(BLUE_LED, OUTPUT);
    digitalWrite(BLUE_LED, HIGH);
    pinMode(YELLOW_LED, OUTPUT);
    digitalWrite(YELLOW_LED, HIGH);
    // 参数设置
    waveSet();
}

void loop() {
    getWave();
    draw();
}