# MSP432P401R

> 为了电赛而学习的Ti家的MSP432P401R板子开发

## 目录

- [include](include) &#x2002; 待定
- [lib](lib) &#x2002; 外部下载库
    - [TM1638](lib/TM1638)
- [src](src) &#x2002; 主程序所在文件夹
- [test](test) &#x2002; 测试代码
    - [初始化类程序](test/Init)
        - [LED 灯闪烁及串口输出](test/Init/LedBlinkAndSerialOut.cpp)
        - [TM1638 LED & KEY 测试代码](test/Init/TM1638helloWorld.cpp)
        - [3.5 TFT Color LCD Module Rev 1.0 测试例程](test/Init/LcdHelloWorld.cpp)
        - [4*4 键盘及 LCD1602 初始化测试](test/Init/KeypadAndLcd1602Init.cpp)
        - [正弦波绘制](test/Init/SinDraw.cpp)
    - [通信类程序](test/Communication) &#x2002; 与 ArduinoNano 通信运行的程序，程序另一半见 ArduinoNano 项目同名程序
        - [LED 闪烁及串口通信](test/Communication/LedBlinkAndSerial.cpp)
        - [方波测频](test/Communication/SquareWaveFrequencyMeasurement.cpp)
    - [待定程序](test/Tmp)