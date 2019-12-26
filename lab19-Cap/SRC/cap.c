#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


Uint16    *ExRamStart = (Uint16 *)0x100000;
Uint32 t1=0,t2=0,t3=0,t4=0,T1=0,T2=0,t5,t6,t7,t8,T3,T4;
interrupt void ISRCap1(void);
interrupt void ISRCap2(void);

Uint16  i;


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
   InitXintf16Gpio();	//zq

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

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable. ECAP1_INT = &ISRCap1;
   PieVectTable. ECAP2_INT = &ISRCap2; 
   //PieVectTable.XINT13 = &cpu_timer1_isr;
   //PieVectTable.TINT2 = &cpu_timer2_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize the Device Peripheral. This function can be
//         found in DSP2833x_CpuTimers.c
  // InitCpuTimers();   // For this example, only initialize the Cpu Timers

// Configure CPU-Timer 0, 1, and 2 to interrupt every second:
// 150MHz CPU Freq, 1 second Period (in uSeconds)

   //ConfigCpuTimer(&CpuTimer0, 150, 1000000);
   //ConfigCpuTimer(&CpuTimer1, 150, 1000000);
   //ConfigCpuTimer(&CpuTimer2, 150, 1000000);
//	StartCpuTimer0();
    InitCapl(); 
// Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
// cap1 is connected to CPU-int 4, and CPU int 14, which is connected
// to CPU-Timer 2:
    IER |= M_INT4;
   //IER |= M_INT13;
   //IER |= M_INT14;

// Enable TINT0 in the PIE: Group 4 interrupt1
    PieCtrlRegs.PIEIER4.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER4.bit.INTx2 = 1;
// Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM
	i = 0;
    for(; ;)
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
interrupt void ISRCap2(void)
{
   

   // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    ECap2Regs.ECCLR.all=0xFFFF;//clare all flag
	t5= ECap2Regs.CAP1;
	t6= ECap2Regs.CAP2;
	t7= ECap2Regs.CAP3;
  	t8= ECap2Regs.CAP4;  
    T3=t6-t5;T4=t8-t7;

    
}

//===========================================================================
// No more.
//===========================================================================
