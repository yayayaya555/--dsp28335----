#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


Uint32 t1=0,t2=0,t3=0,t4=0,T1=0,T2=0;
interrupt void ISRCap1(void);

void main(void)
{

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();
// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// For this case only init GPIO for eQEP1 and ePWM1
// 

//   InitEQep1Gpio();
//   EALLOW;
//   GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;    // GPIO4 as output simulates Index signal
//   GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;  // Normally low
//   EDIS;
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
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
   
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable. ECAP1_INT = &ISRCap1;
   EDIS; 								 
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//   EALLOW;  // This is needed to write to EALLOW protected registers
//   PieVectTable.EPWM1_INT= &prdTick;
//   EDIS;    // This is needed to disable write to EALLOW protected registers
	PieCtrlRegs.PIEIER4.bit.INTx1 = 1;
	IER |= M_INT4;

// Step 4. Initialize all the Device Peripherals:
//   InitEPwm();
	InitECap();			 //This function is found in DSP2833x_ECap.c
// Step 5. User specific code, enable interrupts:
// Enable CPU INT1 which is connected to CPU-Timer 0:
//   IER |= M_INT3;

// Enable TINT0 in the PIE: Group 3 interrupt 1
//   PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM


	for(;;)
	{
	}

}

interrupt void ISRCap1(void)
{
   

   // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    ECap1Regs.ECCLR.all=0xFFFF;//clare all flag
	t1= ECap1Regs.CAP1;
	t2= ECap1Regs.CAP2;
	t3= ECap1Regs.CAP3;
  	t4= ECap1Regs.CAP4;  
    T1=t2-t1;T2=t4-t3;
}



