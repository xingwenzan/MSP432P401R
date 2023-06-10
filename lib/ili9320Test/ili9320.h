//#include "stm32f10x.h"
#include <Arduino.h>
#include "Type.h"
//Ӳ����ص��Ӻ���

//ֻ�ܶ���һ��.ע�⣺8Ϊģʽʹ�õ���Һ����DB8-DB15!!!!!!!!!!!!!!!!!!!!!!!!
//#define nData16Bits		1	//16λģʽ
//#define nData8Bits		1	//8λģʽ 
#define nData4Bits			1	//4��SPIλģʽ

/*
#define nData16Pins		GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15
#define nData8Pins		GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7	
#define nDataPort 		GPIOD
#define nDataClk 		RCC_APB2Periph_GPIOD

#define ConPinNum	5	//����������

#define nCsPin  		GPIO_Pin_9
#define nCsPort 		GPIOB
#define nCsClk 			RCC_APB2Periph_GPIOB

#define RsPin   		GPIO_Pin_7
#define RsPort 			GPIOC
#define RsClk 			RCC_APB2Periph_GPIOC

#define nWrPin  		GPIO_Pin_15
#define nWrPort 		GPIOB
#define nWrClk 			RCC_APB2Periph_GPIOB

#define nRdPin  		GPIO_Pin_13
#define nRdPort 		GPIOB
#define nRdClk 			RCC_APB2Periph_GPIOB

#define nRstPin 		GPIO_Pin_12
#define nRstPort 		GPIOB
#define nRstClk 		RCC_APB2Periph_GPIOB


//#define Lcd_LightPin 	GPIOB,GPIO_Pin_13

#define Set_Cs  GPIO_SetBits(nCsPort,nCsPin);
#define Clr_Cs  GPIO_ResetBits(nCsPort,nCsPin);

#define Set_Rs  GPIO_SetBits(RsPort,RsPin);
#define Clr_Rs  GPIO_ResetBits(RsPort,RsPin);

#define Set_nWr GPIO_SetBits(nWrPort,nWrPin);
#define Clr_nWr GPIO_ResetBits(nWrPort,nWrPin);
#define Set_Clk Set_nWr			//spi clk
#define Clr_Clk Clr_nWr

#define Set_nRd GPIO_SetBits(nRdPort,nRdPin);
#define Clr_nRd GPIO_ResetBits(nRdPort,nRdPin);
#define Set_Dat Set_nRd			//spi dat
#define Clr_Dat Clr_nRd

#define Set_Rst GPIO_SetBits(nRstPort,nRstPin);
#define Clr_Rst GPIO_ResetBits(nRstPort,nRstPin);
*/
#define nCsPin 	12
#define nRsPin	11
#define nClkPin	13
#define nDatPin 14
#define nRstPin 15


#define Set_Cs  digitalWrite(nCsPin, HIGH);
#define Clr_Cs  digitalWrite(nCsPin, LOW);

#define Set_Rs  digitalWrite(nRsPin, HIGH);
#define Clr_Rs  digitalWrite(nRsPin, LOW);

#define Set_nWr digitalWrite(nClkPin, HIGH);
#define Clr_nWr digitalWrite(nClkPin, LOW);
#define Set_Clk Set_nWr			//spi clk
#define Clr_Clk Clr_nWr

#define Set_nRd digitalWrite(nDatPin, HIGH);
#define Clr_nRd digitalWrite(nDatPin, LOW);
#define Set_Dat Set_nRd			//spi dat
#define Clr_Dat Clr_nRd

#define Set_Rst digitalWrite(nRstPin, HIGH);
#define Clr_Rst digitalWrite(nRstPin, LOW);


#define      BACKGROUND		               BLACK   //Ĭ�ϱ�����ɫ

#define      WHITE		 		           			 0xFFFF	   //��ɫ
#define      BLACK                         0x0000	   //��ɫ 
#define      GREY                          0xF7DE	   //��ɫ 
#define      BLUE                          0x001F	   //��ɫ 
#define      BLUE2                         0x051F	   //ǳ��ɫ 
#define      RED                           0xF800	   //��ɫ 
#define      MAGENTA                       0xF81F	   //����ɫ�����ɫ 
#define      GREEN                         0x07E0	   //��ɫ 
#define      CYAN                          0x7FFF	   //����ɫ����ɫ 
#define      YELLOW                        0xFFE0	   //��ɫ 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF


u16 CheckController(void);
void Lcd_Configuration(void);
void ili9320_Initializtion(void);
void ili9320_Reset(void);
void ili9320_WriteRegister(u16 index,u16 dat);
void ili9320_SetCursor(u16 x,u16 y);
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY);
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic);
void ili9320_SetPoint(u16 x,u16 y,u16 point);
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor,u8 mode);
void ili9320_Clear(u16 dat);
void ili9320_Delay(u32 nCount);
void ili9320_Test(void);
u16 ili9320_GetCode(void);
void ili9320_WriteData(u16 dat);
void ili9320_WriteIndex(u16 idx);

void ili9320_BackLight(u8 status);

u16 ili9320_BGR2RGB(u16 c);

u16 ili9320_GetPoint(u16 x,u16 y);
u16 ili9320_ReadData(void);
u16 ili9320_ReadRegister(u16 index);

u16 GUI_Color565(u32 RGB);  											// RGB��ɫתΪ16λ(565)


//void Touch_Initializtion(void);
//u16  Touch_GetPhyX(void);
//u16  Touch_GetPhyY(void);
//u16  Touch_MeasurementX(void);
//u16  Touch_MeasurementY(void);
