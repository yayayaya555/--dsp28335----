#include"DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#define  K0   0
#define  K1   1
#define  K2   2
#define  K3   3
#define  K4   4
#define  K5   5
#define  K6   6
#define  K7   7
#define  K8   8
#define  K9   9
//#define  UP   10
//#define  DW   11
//#define  LF   12
//#define  RT   13
#define  AD   14   //+
#define  SB   15   //-

#define  L_O_V_I()     EALLOW;                             \
                       GpioCtrlRegs.GPBDIR.bit.GPIO54 = 1; \
					   GpioDataRegs.GPBDAT.bit.GPIO54 = 0; DELAY_US(1);\
                       GpioCtrlRegs.GPBDIR.bit.GPIO55 = 1; \
					   GpioDataRegs.GPBDAT.bit.GPIO55 = 0; DELAY_US(1);\
					   GpioCtrlRegs.GPBDIR.bit.GPIO56 = 1; \
					   GpioDataRegs.GPBDAT.bit.GPIO56 = 0; DELAY_US(1);\
					   GpioCtrlRegs.GPBDIR.bit.GPIO57 = 1; \
					   GpioDataRegs.GPBDAT.bit.GPIO57 = 0; DELAY_US(1);\
					   GpioCtrlRegs.GPBDIR.bit.GPIO48 = 0; \
					   GpioDataRegs.GPBDAT.bit.GPIO48 = 0; DELAY_US(1);\
					   \
					   \
					   GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0; \
					   GpioDataRegs.GPBDAT.bit.GPIO52 = 0; DELAY_US(1);\
					   GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0; \
					   GpioDataRegs.GPBDAT.bit.GPIO53 = 0; DELAY_US(1);\
					   EDIS;
#define  L_I_V_O()     EALLOW;                             \
                       GpioCtrlRegs.GPBDIR.bit.GPIO54 = 0; \
					   GpioDataRegs.GPBDAT.bit.GPIO54 = 0; DELAY_US(1);\
                       GpioCtrlRegs.GPBDIR.bit.GPIO55 = 0; \
					   GpioDataRegs.GPBDAT.bit.GPIO55 = 0; DELAY_US(1);\
					   GpioCtrlRegs.GPBDIR.bit.GPIO56 = 0; \
					   GpioDataRegs.GPBDAT.bit.GPIO56 = 0; DELAY_US(1);\
					   GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0; \
					   GpioDataRegs.GPBDAT.bit.GPIO57 = 0; DELAY_US(1);\
					   GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1; \
					   GpioDataRegs.GPBDAT.bit.GPIO48 = 0; DELAY_US(1);\
					   \
					   \
					   GpioCtrlRegs.GPBDIR.bit.GPIO52 = 1; \
					   GpioDataRegs.GPBDAT.bit.GPIO52 = 0; DELAY_US(1);\
					   GpioCtrlRegs.GPBDIR.bit.GPIO53 = 1; \
					   GpioDataRegs.GPBDAT.bit.GPIO53 = 0; DELAY_US(1);\
					   EDIS;   

#define	  V2 	GpioDataRegs.GPBDAT.bit.GPIO48
//#define	  V1 	GpioDataRegs.GPBDAT.bit.GPIO49
#define	  V4 	GpioDataRegs.GPBDAT.bit.GPIO52
#define	  V3 	GpioDataRegs.GPBDAT.bit.GPIO53

#define	  L1 	GpioDataRegs.GPBDAT.bit.GPIO57
#define	  L2 	GpioDataRegs.GPBDAT.bit.GPIO56
#define	  L3 	GpioDataRegs.GPBDAT.bit.GPIO54
#define	  L4 	GpioDataRegs.GPBDAT.bit.GPIO55
#define	  uchar 	unsigned char

#define	  EN 	GpioDataRegs.GPBDAT.bit.GPIO33
#define	  RW 	GpioDataRegs.GPBDAT.bit.GPIO32
#define	  RS 	GpioDataRegs.GPADAT.bit.GPIO20 
/*
unsigned char const table[]={//共阴极0~f数码管编码
0x3f,0x06,0x5b,0x4f,     //0~3
0x66,0x6d,0x7d,0x07,    //4~7
0x7f,0x6f,0x77,0x7c,    //8~b
0x39,0x5e,0x79,0x71    //c~f
}; */
void LCDInit(void);
void Write_order(Uint16 order);
void Write_data(Uint16 data);
void delay(Uint16 t);
void configio(void);
//void InitXintf(void);
void display(char *hz);

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
  Write_order(0x0e);//显示状态：开
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

void display(char *hz)
{
   while(*hz!='\0')
    {
       Write_data(*hz);
       hz++;
       delay(2);
    }
} 

Uint16 Scan_Button(void){
   Uint16 i=0, num=0xFFFF, x=0, y=0;
   i = V2&V3&V4;  //如果列读取到有低电平说明有按键按下
   if(i == 0){
     DELAY_US(1000);//延时消抖
     i = V2&V3&V4;  
	 if(i == 0){	//如果列读取到仍然有低电平说明有按键按下
       // if(!V1) x= 0x10;
		if(!V2) x= 0x20;
		if(!V3) x= 0x30;
		if(!V4) x= 0x40;
		L_I_V_O();DELAY_US(200); //行与列输入输出反转		
		if(!L2) y= 0x02;
		if(!L3) y= 0x03;
		if(!L4) y= 0x04;
		if(!L1) y= 0x01;
		x |= y;	
        L_O_V_I();	
		switch(x){
          case 0x21: num = K1;break;
		  case 0x22: num = K4;break;
		  case 0x23: num = SB;break;
		  case 0x24: num = K7;break;
		  case 0x31: num = K2;break;
		  case 0x32: num = K5;break;
		  case 0x33: num = K0;break;
		  case 0x34: num = K8;break;
		  case 0x41: num = K3;break;
		  case 0x42: num = K6;break;
		  case 0x43: num = AD;break;
		  case 0x44: num = K9;break;
		        
          default: num=0xFFFF; 
		}
		
	 }
   }
   return num;
}

void Configio_Button(void)
{
    EALLOW;
	GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;
//    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 0; 
//    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;
//	GpioCtrlRegs.GPBDIR.bit.GPIO49 = 0;
	GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;
//	GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;
	GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;
//	GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;
	GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 0;
//	GpioCtrlRegs.GPBDIR.bit.GPIO54 = 0;
	GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0;
//	GpioCtrlRegs.GPBDIR.bit.GPIO55 = 0;
	GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;
//	GpioCtrlRegs.GPBDIR.bit.GPIO56 = 0;
	GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;
//	GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0;   
    EDIS;
	L_O_V_I();  //行设置为输出（输出低电平）列设置为输入
}

void main(void)
{
    Uint16 u=0;
	Uint16 start=0x86;
    InitSysCtrl();
  //  InitXintf();
    InitXintf16Gpio();
    DINT;
    InitPieCtrl();
    IER=0x0000;
    IFR=0x0000;
    
    Configio_Button();
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
  delay(5);
 // Write_order(0x34);//显示状态：开
  delay(5); 
//    Write_order(0x04);
    delay(50);
	delay(5);
  Write_order(0x30);//显示状态：开
  delay(5);
    Write_order(0x80);
    delay(5);
	 
    display("您的按键为：");
   
/*    Write_order(0x91);
    delay(5);
    display(menu2);
    
    Write_order(0x89);
    delay(5);
    display(menu3);

    Write_order(0x99);
    delay(5);
    display(menu4); */
  
    while(1){
       u = Scan_Button();  
      if( u != 0xFFFF ){
        switch(u){
		  case AD: Write_order(start);delay(5);display("+");break;
		  case SB: Write_order(start);delay(5);display("-");break;
		  case K0: Write_order(start);delay(5);display("0");break;
		  case K1: Write_order(start);delay(5);display("1");break;
		  case K2: Write_order(start);delay(5);display("2");break;
		  case K3: Write_order(start);delay(5);display("3");break;
		  case K4: Write_order(start);delay(5);display("4");break;
		  case K5: Write_order(start);delay(5);display("5");break;
		  case K6: Write_order(start);delay(5);display("6");break;
		  case K7: Write_order(start);delay(5);display("7");break;
		  case K8: Write_order(start);delay(5);display("8");break;
		  case K9: Write_order(start);delay(5);display("9");break;
          default: break;       
		}
	  }
	}
}

//
//===========================================================================
// No more.
//===========================================================================
