#include"DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#define	  EN 	GpioDataRegs.GPBDAT.bit.GPIO33
#define	  RW 	GpioDataRegs.GPBDAT.bit.GPIO32
#define	  RS 	GpioDataRegs.GPADAT.bit.GPIO20
#define	  uchar 	unsigned char
extern uchar menu1[]={"选择电机定时设置"};
extern uchar menu2[]={"开步进电机A"};
extern uchar menu3[]={"开步进电机B"};
extern uchar menu4[]={"开步进电机C"};
void LCDInit(void);
void Write_order(Uint16 order);
void Write_data(Uint16 data);
void delay(Uint16 t);
void configio(void);
//void InitXintf(void);
void display(uchar *hz);

void LCD_DATA(uchar d){
   Uint32 i=0;
   i = GpioDataRegs.GPADAT.all;
   i |= (d<<6)&0x3FC0; 
   i = (~((d<<6)&0x3FC0))|(~i);
   GpioDataRegs.GPADAT.all = ~i;
} 
void LCDInit(void)
{
  delay(500);
  Write_order(0x30);// 功能设定：基本指令动作
  delay(5);
  Write_order(0x0c);//显示状态：开
  delay(5);
  Write_order(0x01);//清屏
  delay(6);
  Write_order(0x02);//地址归位：AC=0x00
  delay(4);
}

void Write_order(Uint16 order)
{
   RS=0;delay(1);
   RW=0;delay(1);
   EN=1;delay(1);
   LCD_DATA(order);
   delay(10);
   EN=0;delay(1);
}

void Write_data(Uint16 data)
{
   RS=1;delay(1);
   RW=0;delay(1);
   EN=1;delay(1);
   LCD_DATA(data);
   delay(10);
   EN=0;delay(1);
}

void delay(Uint16 t)
{
   Uint16 i;
   while(t--)
    {
      for(i=0;i<125;i++);
    }
}

void configio(void)
{
    EALLOW;
	GpioCtrlRegs.GPAMUX1.all &= 0xc03f; 
	GpioCtrlRegs.GPADIR.all |= 0x00003FC0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1; 
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1; 
    GpioCtrlRegs.GPAMUX2.bit.GPIO20= 0;
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 1; 
    EDIS;
}

void display(uchar *hz)
{
   while(*hz!='\0')
    {
       Write_data(*hz);
       hz++;
       delay(2);
    }
}

void main(void)
{
    InitSysCtrl();
  //  InitXintf();
    InitXintf16Gpio();
    DINT;
    InitPieCtrl();
    IER=0x0000;
    IFR=0x0000;
    
    configio();
    RS=0;
    delay(5);
    RW=0;
    delay(5);
    EN=0;
    LCDInit();
    delay(5);
    Write_order(0x01);
    delay(50);
    Write_order(0x80);
    delay(5);
    display(menu1);
   
    Write_order(0x91);
    delay(5);
    display(menu2);
    
    Write_order(0x89);
    delay(5);
    display(menu3);

    Write_order(0x99);
    delay(5);
    display(menu4);

    while(1);
}

//
//===========================================================================
// No more.
//===========================================================================
