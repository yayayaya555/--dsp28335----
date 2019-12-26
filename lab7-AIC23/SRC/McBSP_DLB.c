//###########################################################################
//
// Original Author: S.S.
//
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################



#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

     

Uint16	volume,tAicRegs;
int ADbuf[500];
int DA_wptr,DA_rptr,y;
Uint16 play_mode=0;

void main(void)
{
	Uint16	temp,i;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   	InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example
// For this example, only enable the GPIO for McBSP-A
	InitXintf16Gpio();
   	InitMcbspaGpio();

	EALLOW;
     GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0; //aic_dat	 
	 GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	 GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;
     GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0; //aic_CS	 
	 GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;
	 GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;
	 GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0; //aic_clk	 
	 GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1; 
	 GpioCtrlRegs.GPBPUD.bit.GPIO61 = 0;
	 EDIS; 

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   	DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   	IER = 0x0000;
   	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
   	InitPieVectTable();

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals();     // Not required for this example
   	InitMcbspa();          // Initalize the Mcbsp-A in loopback test mode

//	tAicRegs = 0xFF;
//	SysReg = tAicRegs;

	InitAic23();	
	delay(500);
    volume=108;
  WriteAic23(L_HEADPHONE_VOLUME,0x0180+volume);   
	
	EALLOW;	// This is needed to write to EALLOW protected registers
	PieVectTable.MRINTA = &ISRMcbspSend;
	EDIS;   // This is needed to disable write to EALLOW protected registers

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER6.bit.INTx5=1;     // Enable PIE Group 6, INT 5
    IER |= M_INT6;                            // Enable CPU INT6

	EINT;   // Enable Global interrupt INTM


	while(1)
	{
    	for(temp=30000;temp>0;temp-=100)
		{
      		for(i=0;i<2;i++)
      		{
         		y=5000;       
         		delay(temp); 
         	//	McbspaRegs.DXR1.all = y;
         		y=-5000;       
         		delay(temp);
         	  //  McbspaRegs.DXR1.all = y;
      		}
		}
	}

}
interrupt void  ISRMcbspSend(void)
{
      int temp;

	  PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
      temp=McbspaRegs.DRR1.all;
        
      DA_rptr++;
      if(DA_rptr>=500)
            DA_rptr=0;

      ADbuf[DA_rptr]=temp;   //保存录音数据
     
      if(play_mode==0)
        McbspaRegs.DXR1.all = y;
                   //警报声的幅值
      else
        McbspaRegs.DXR1.all = temp;        //放音

}


//===========================================================================
// No more.
//===========================================================================

