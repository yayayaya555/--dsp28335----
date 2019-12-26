#include"DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
/*#define	  SEG_DATA(d)	\
GpioDataRegs.GPADAT.all = 
GpioDataRegs.GPADAT.all |= (d<<6)&0x3FC0; \
GpioDataRegs.GPADAT.all = (~((d<<6)&0x3FC0))|(~GpioDataRegs.GPADAT.all);\
                        GpioDataRegs.GPADAT.all = ~GpioDataRegs.GPADAT.all; */
/*#define	  SEG_DATA(d)	GpioDataRegs.GPADAT.bit.GPIO6 = (d>>0) & 0x01;  \
                        GpioDataRegs.GPADAT.bit.GPIO7 = (d>>1) & 0x01;  \
						GpioDataRegs.GPADAT.bit.GPIO8 = (d>>2) & 0x01;  \
						GpioDataRegs.GPADAT.bit.GPIO9 = (d>>3) & 0x01;  \
						GpioDataRegs.GPADAT.bit.GPIO10 = (d>>4) & 0x01;  \
						GpioDataRegs.GPADAT.bit.GPIO11 = (d>>5) & 0x01;  \
						GpioDataRegs.GPADAT.bit.GPIO12 = (d>>6) & 0x01;  \
						GpioDataRegs.GPADAT.bit.GPIO13 = (d>>7) & 0x01;*/  
#define	  SBIT3 	GpioDataRegs.GPBDAT.bit.GPIO32
#define	  SBIT2 	GpioDataRegs.GPBDAT.bit.GPIO33
#define	  SBIT1 	GpioDataRegs.GPBDAT.bit.GPIO49
#define	  SBIT0 	GpioDataRegs.GPADAT.bit.GPIO20
#define	  uchar 	unsigned char

unsigned char const table[]={//共阴极0~f数码管编码
0x3f,0x06,0x5b,0x4f,     //0~3
0x66,0x6d,0x7d,0x07,    //4~7
0x7f,0x6f,0x77,0x7c,    //8~b
0x39,0x5e,0x79,0x71    //c~f
}; 
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

void delay(Uint16 t)
{
   Uint16 i;
   while(t--)
    {
      for(i=0;i<125;i++);
    }
}

void SEG_DATA(uchar d){
   Uint32 i=0;
   i = GpioDataRegs.GPADAT.all;
   i |= (d<<6)&0x3FC0; 
   i = (~((d<<6)&0x3FC0))|(~i);
   GpioDataRegs.GPADAT.all = ~i;
}

void configio(void)
{
    EALLOW;
	GpioCtrlRegs.GPAMUX1.all &= 0xc03f; 
	GpioCtrlRegs.GPADIR.all |= 0x00003FC0;
	//GpioCtrlRegs.GPAPUD.all |= 0xFFFFc03f;
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1; 
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1; 
    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1; 
//	GpioCtrlRegs.GPAPUD.bit.GPIO49=0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO20= 0;
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;
//    GpioCtrlRegs.GPAPUD.bit.GPIO20=0; 
    EDIS;
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
SBIT1=1;
SBIT0=1;
SBIT2=1;
SBIT3=1;
//GpioDataRegs.GPBSET.bit.GPIO33=1;
//SBIT0=1;
SEG_DATA(0);	   
    while(1){	  
         
      SEG_DATA(table[0]);
      SBIT0=0;
      SBIT2=1;
      SBIT1=1;     
      SBIT3=1;      
	  DELAY_US(200);
	  SBIT0=1;
	  SEG_DATA(0);

      
      SEG_DATA(table[1]);
      SBIT1=0;
      SBIT2=1;
      SBIT3=1;
      SBIT0=1; 
	  DELAY_US(200);
	  SBIT1=1;
	  SEG_DATA(0);

      
      SEG_DATA(table[2]);
      SBIT2=0;
      SBIT1=1;     
      SBIT3=1;
      SBIT0=1; 
	  DELAY_US(200);
	  SBIT2=1;
	  SEG_DATA(0);

      
      SEG_DATA(table[3]);
	  SBIT3=0;
      SBIT1=1;
      SBIT2=1;      
      SBIT0=1; 
	  DELAY_US(200);
	  SBIT3=1;
	  SEG_DATA(0);

	}
}

//
//===========================================================================
// No more.
//===========================================================================
