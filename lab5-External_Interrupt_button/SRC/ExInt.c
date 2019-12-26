#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define	  LED4	GpioDataRegs.GPADAT.bit.GPIO0
#define	  LED3	GpioDataRegs.GPADAT.bit.GPIO1
#define	  LED1	GpioDataRegs.GPADAT.bit.GPIO6
#define	  LED2	GpioDataRegs.GPADAT.bit.GPIO7 

#define	  BUZZ_C	GpioDataRegs.GPBSET.bit.GPIO60=1; 
#define	  BUZZ_O	GpioDataRegs.GPBCLEAR.bit.GPIO60=1;

interrupt void ISRExint1(void);
void configtestled(void);
void InitExInt(void);

void main(void)
{
   InitSysCtrl();
   DINT;

  InitPieCtrl();
// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

   InitPieVectTable();
   InitExInt();
	EALLOW;  // This is needed to write to EALLOW protected registers
   	PieVectTable.XINT1 = &ISRExint1;
   	EDIS;    // This is needed to disable write to EALLOW protected registers

   	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
	PieCtrlRegs.PIEIER1.bit.INTx4= 1; 
	 
   	IER |= M_INT1;                              // Enable CPU int1

    EINT;   // 中断使能
    ERTM;   // Enable Global realtime interrupt DBGM
    configtestled();
	
    LED1=0;
	DELAY_US(10);
	LED2=0;
	DELAY_US(10);
	LED3=1;
	DELAY_US(10);
	LED4=1;
	DELAY_US(10); 
    while(1);
}
interrupt void ISRExint1(void){
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
	DELAY_US(1000);
	if(GpioDataRegs.GPADAT.bit.GPIO13 == 0){
        LED1=~LED1;
    	LED2=~LED2;
	    LED3=~LED3;
    	LED4=~LED4;
    	BUZZ_O
    	DELAY_US(50000);
    	BUZZ_C
    }	
}

void InitExInt(void){
     EALLOW;
     GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;	 
	 GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;
	 GpioCtrlRegs.GPAQSEL1.bit.GPIO13= 0;	 
     GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 13;//选择GPIO13为外部输入XINT3输入引脚  	 
	 XIntruptRegs.XINT1CR.bit.POLARITY= 0;//下降沿触发中断	
	 XIntruptRegs.XINT1CR.bit.ENABLE = 1; //使能XINT3中断
	 EDIS;
} 

void configtestled(void)
{
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // GPIO0复用为GPIO功能
   GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;  // GPIO0设置为输出
   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0; // GPIO1 = GPIO1
   GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0; // 
   GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0; // 
   GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;
   GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0; //
   GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0; 
   GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;
   BUZZ_C 
   EDIS; 
}

//===========================================================================
// No more.
//===========================================================================
