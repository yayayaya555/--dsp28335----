// TI File $Revision: /main/2 $
// Checkin $Date: April 4, 2007   14:25:27 $
//###########################################################################
//
// FILE:    DSP2833x_SWPrioritizedDefaultIsr.c
//
// TITLE:   DSP2833x Device Default Software Prioritized Interrupt Service Routines.
//
//###########################################################################
//
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################


#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DSP2833x_SWPrioritizedIsrLevels.h" 


// Connected to INT13 of CPU (use MINT13 mask):
// Note CPU-Timer1 is reserved for TI use, however XINT13
// ISR can be used by the user. 
#if (INT13PL != 0)
interrupt void INT13_ISR(void)     // INT13 or CPU-Timer1
{
	 IER |= MINT13;                 // Set "global" priority
	 EINT;

  // Insert ISR Code here
  
  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
     asm ("      ESTOP0");
     for(;;);
}
#endif

// Connected to INT14 of CPU (use MINT14 mask):
#if (INT14PL != 0)
interrupt void INT14_ISR(void)     // CPU-Timer2
{
   IER |= MINT14;                  // Set "global" priority
   EINT;

   // Insert ISR Code here.......
  
   // Next two lines for debug only to halt the processor here
   // Remove after inserting ISR Code
   asm ("      ESTOP0");
   for(;;);
}
#endif

// Connected to INT15 of CPU (use MINT15 mask):
#if (INT15PL != 0)
interrupt void DATALOG_ISR(void)   // Datalogging interrupt
{
	IER |= MINT15;                 // Set "global" priority
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}
#endif

// Connected to INT16 of CPU (use MINT16 mask):
#if (INT16PL != 0)
interrupt void RTOSINT_ISR(void)   // RTOS interrupt
{
	IER |= MINT16;                 // Set "global" priority
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}
#endif

// Connected to EMUINT of CPU (non-maskable):
interrupt void EMUINT_ISR(void)    // Emulation interrupt
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}


// Connected to NMI of CPU (non-maskable):
interrupt void NMI_ISR(void)      // Non-maskable interrupt
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void ILLEGAL_ISR(void)   // Illegal operation TRAP
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}


interrupt void USER1_ISR(void)     // User Defined trap 1
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER2_ISR(void)     // User Defined trap 2
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER3_ISR(void)     // User Defined trap 3
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER4_ISR(void)     // User Defined trap 4
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER5_ISR(void)     // User Defined trap 5
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER6_ISR(void)     // User Defined trap 6
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER7_ISR(void)     // User Defined trap 7
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER8_ISR(void)     // User Defined trap 8
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER9_ISR(void)     // User Defined trap 9
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER10_ISR(void)    // User Defined trap 10
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER11_ISR(void)    // User Defined trap 11
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

interrupt void USER12_ISR(void)     // User Defined trap 12
{
	EINT;

  	// Insert ISR Code here.......
  
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}


// -----------------------------------------------------------
// PIE Group 1 - MUXed into CPU INT1
// -----------------------------------------------------------

// Connected to PIEIER1_1 (use MINT1 and MG11 masks):
#if (G11PL != 0)
interrupt void SEQ1INT_ISR( void )     // ADC
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
	IER |= M_INT1;
	IER	&= MINT1;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER1.all &= MG11;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;
    
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER1_2 (use MINT1 and MG12 masks):
#if (G12PL != 0)
interrupt void SEQ2INT_ISR( void )    // ADC
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
	IER |= M_INT1;
	IER	&= MINT1;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER1.all &= MG12;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
  	


	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif


// Connected to PIEIER1_4 (use MINT1 and MG14 masks):
#if (G14PL != 0)
interrupt void  XINT1_ISR(void)
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
	IER |= MINT1;                      // Set "global" priority
	PieCtrlRegs.PIEIER1.all &= MG14;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;


	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}     
#endif

// Connected to PIEIER1_5 (use MINT1 and MG15 masks):
#if (G15PL != 0)
interrupt void  XINT2_ISR(void)
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
	IER |= MINT1;                      // Set "global" priority
	PieCtrlRegs.PIEIER1.all &= MG15;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
  	

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}
#endif


// Connected to PIEIER1_6 (use MINT1 and MG16 masks):
#if (G16PL != 0)
interrupt void  ADCINT_ISR(void)     // ADC
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT1;
	IER	&= MINT1;                      // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG16;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER1_7 (use MINT1 and MG17 masks):
#if (G17PL != 0)
interrupt void  TINT0_ISR(void)      // CPU-Timer 0
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
	IER |= M_INT1;
	IER	&= MINT1;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER1.all &= MG17;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
  	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;
      
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}     
#endif

// Connected to PIEIER1_8 (use MINT1 and MG18 masks):
#if (G18PL != 0)
interrupt void  WAKEINT_ISR(void)      // WD/LPM
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
	IER |= M_INT1;
	IER	&= MINT1;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER1.all &= MG18;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
  	
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;
	
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}     
#endif


// -----------------------------------------------------------
// PIE Group 2 - MUXed into CPU INT2
// -----------------------------------------------------------

// Connected to PIEIER2_1 (use MINT2 and MG21 masks):
#if (G21PL != 0)
interrupt void EPWM1_TZINT_ISR(void)    // ePWM1 Trip Zone
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
	IER |= M_INT2;
	IER	&= MINT2;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER2.all &= MG21;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER2.all = TempPIEIER;
    
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}     
#endif

// Connected to PIEIER2_2 (use MINT2 and MG22 masks):
#if (G22PL != 0)
interrupt void EPWM2_TZINT_ISR(void)    // ePWM2 Trip Zone
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
	IER |= M_INT2;
	IER	&= MINT2;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER2.all &= MG22;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER2.all = TempPIEIER;
	
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}     
#endif

// Connected to PIEIER2_3 (use MINT2 and MG23 masks):
#if (G23PL != 0)
interrupt void EPWM3_TZINT_ISR(void)    // ePWM3 Trip Zone
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
	IER |= M_INT2;
	IER	&= MINT2;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER2.all &= MG23;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER2.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER2_4 (use MINT2 and MG24 masks):
#if (G24PL != 0)
interrupt void EPWM4_TZINT_ISR(void)    // ePWM4 Trip Zone
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
	IER |= M_INT2;
	IER	&= MINT2;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER2.all &= MG24;    // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER2.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER2_5 (use MINT2 and MG25 masks):
#if (G25PL != 0)
interrupt void EPWM5_TZINT_ISR(void)    // ePWM5 Trip Zone
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
	IER |= M_INT2;
	IER	&= MINT2;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER2.all &= MG25;    // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER2.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER2_6 (use MINT2 and MG26 masks):
#if (G26PL != 0)
interrupt void EPWM6_TZINT_ISR(void)    // ePWM6 Trip Zone
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
	IER |= M_INT2;
	IER	&= MINT2;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER2.all &= MG26;    // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER2.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif


// -----------------------------------------------------------
// PIE Group 3 - MUXed into CPU INT3
// -----------------------------------------------------------


// Connected to PIEIER3_1 (use MINT3 and MG31 masks):
#if (G31PL != 0)
interrupt void EPWM1_INT_ISR(void)     // ePWM1 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
	IER |= M_INT3;
	IER	&= MINT3;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER3.all &= MG31;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}     
#endif

// Connected to PIEIER3_2 (use MINT3 and MG32 masks):
#if (G32PL != 0)
interrupt void EPWM2_INT_ISR(void)     // ePWM2 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
	IER |= M_INT3;
	IER	&= MINT3;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER3.all &= MG32;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;
    
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif
      
// Connected to PIEIER3_3 (use MINT3 and MG33 masks):
#if (G33PL != 0)
interrupt void EPWM3_INT_ISR(void)     // ePWM3 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
	IER |= M_INT3;
	IER	&= MINT3;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER3.all &= MG33;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;
      
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER3_4 (use MINT3 and MG34 masks):
#if (G34PL != 0)
interrupt void EPWM4_INT_ISR(void)     // ePWM4 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
	IER |= M_INT3;
	IER	&= MINT3;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER3.all &= MG34;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;
      
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER3_5 (use MINT3 and MG35 masks):
#if (G35PL != 0)
interrupt void EPWM5_INT_ISR(void)     // ePWM5 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
	IER |= M_INT3;
	IER	&= MINT3;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER3.all &= MG35;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER3_6 (use MINT3 and MG36 masks):
#if (G36PL != 0)
interrupt void EPWM6_INT_ISR(void)     // ePWM6 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
	IER |= M_INT3;
	IER	&= MINT3;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER3.all &= MG36;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}     
#endif


// -----------------------------------------------------------
// PIE Group 4 - MUXed into CPU INT4
// -----------------------------------------------------------


// Connected to PIEIER4_1 (use MINT4 and MG41 masks):
#if (G41PL != 0)
interrupt void ECAP1_INT_ISR(void)     // eCAP1 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
	IER |= M_INT4;
	IER	&= MINT4;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER4.all &= MG41;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER4_2 (use MINT4 and MG42 masks):
#if (G42PL != 0)
interrupt void ECAP2_INT_ISR(void)     // eCAP2 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
	IER |= M_INT4;
	IER	&= MINT4;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER4.all &= MG42;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER4_3 (use MINT4 and MG43 masks):
#if (G43PL != 0)
interrupt void ECAP3_INT_ISR(void)     // eCAP3 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
	IER |= M_INT4;
	IER	&= MINT4;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER4.all &= MG43;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER4_4 (use MINT4 and MG44 masks):
#if (G44PL != 0)
interrupt void ECAP4_INT_ISR(void)     // eCAP4 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
	IER |= M_INT4;
	IER	&= MINT4;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER4.all &= MG44;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
 
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif


// -----------------------------------------------------------
// PIE Group 5 - MUXed into CPU INT5
// -----------------------------------------------------------

// Connected to PIEIER5_1 (use MINT5 and MG51 masks):
#if (G51PL != 0)
interrupt void EQEP1_INT_ISR(void)     // eQEP1 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
	IER |= M_INT5;
	IER	&= MINT5;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER5.all &= MG51;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER5.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER5_2 (use MINT5 and MG52 masks):
#if (G52PL != 0)
interrupt void EQEP2_INT_ISR(void)     // eQEP2 Interrupt
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
	IER |= M_INT5;
	IER	&= MINT5;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER5.all &= MG52;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER5.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif
      
// -----------------------------------------------------------
// PIE Group 6 - MUXed into CPU INT6
// -----------------------------------------------------------

// Connected to PIEIER6_1 (use MINT6 and MG61 masks):
#if (G61PL != 0)
interrupt void SPIRXINTA_ISR(void)    // SPI-A
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
	IER |= M_INT6;
	IER	&= MINT6;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG61;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER6_2 (use MINT6 and MG62 masks):
#if (G62PL != 0)
interrupt void SPITXINTA_ISR(void)     // SPI-A
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
	IER |= M_INT6;
	IER	&= MINT6;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG62;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}     
#endif

// Connected to PIEIER6_3 (use MINT6 and MG63 masks):
#if (G63PL != 0)
interrupt void SPIRXINTB_ISR(void)    // SPI-B
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
	IER |= M_INT6;
	IER	&= MINT6;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG63;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;
	
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER6_4 (use MINT6 and MG64 masks):
#if (G64PL != 0)
interrupt void SPITXINTB_ISR(void)     // SPI-B
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
	IER |= M_INT6;
	IER	&= MINT6;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG64;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
 
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif



// Connected to PIEIER6_5 (use MINT6 and MG65 masks):
#if (G65PL != 0)
interrupt void SPIRXINTC_ISR(void)     // SPI-C
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
	IER |= M_INT6;
	IER	&= MINT6;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG65;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER6_6 (use MINT6 and MG66 masks):
#if (G66PL != 0)
interrupt void SPITXINTC_ISR(void)     // SPI-C
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
	IER |= M_INT6;
	IER	&= MINT6;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG66;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER6_7 (use MINT6 and MG67 masks):
#if (G65PL != 0)
interrupt void SPIRXINTD_ISR(void)     // SPI-D
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
	IER |= M_INT6;
	IER	&= MINT6;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG67;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
 	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER6_8 (use MINT6 and MG68 masks):
#if (G66PL != 0)
interrupt void SPITXINTD_ISR(void)     // SPI-D
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
	IER |= M_INT6;
	IER	&= MINT6;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG68;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif



// -----------------------------------------------------------
// PIE Group 7 - MUXed into CPU INT7
// -----------------------------------------------------------

// -----------------------------------------------------------
// PIE Group 8 - MUXed into CPU INT8
// -----------------------------------------------------------

// Connected to PIEIER8_1 (use MINT8 and MG81 masks):
#if (G81PL != 0)
interrupt void I2CINT1A_ISR(void)    // I2C-A
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
	IER |= M_INT8;
	IER	&= MINT8;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG81;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER8.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER8_2 (use MINT8 and MG82 masks):
#if (G82PL != 0)
interrupt void I2CINT2A_ISR(void)     // I2C-A
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
	IER |= M_INT8;
	IER	&= MINT8;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG82;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER8.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// -----------------------------------------------------------
// PIE Group 9 - MUXed into CPU INT9
// -----------------------------------------------------------

// Connected to PIEIER9_1 (use MINT9 and MG91 masks):
#if (G91PL != 0)
interrupt void SCIRXINTA_ISR(void)     // SCI-A
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG91;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER9_2 (use MINT9 and MG92 masks):
#if (G92PL != 0)
interrupt void SCITXINTA_ISR(void)     // SCI-A
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG92;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif


// Connected to PIEIER9_3 (use MINT9 and MG93 masks):
#if (G93PL != 0)
interrupt void SCIRXINTB_ISR(void)     // SCI-B
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG93;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER9_4 (use MINT9 and MG94 masks):
#if (G94PL != 0)
interrupt void SCITXINTB_ISR(void)     // SCI-B
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG94;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
 
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER9_5 (use MINT9 and MG95 masks):
#if (G95PL != 0)
interrupt void ECAN0INTA_ISR(void)    // eCAN-A
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG95;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER9_6 (use MINT9 and MG96 masks):
#if (G96PL != 0)
interrupt void ECAN1INTA_ISR(void)     // eCAN-A
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG96;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER9_7 (use MINT9 and MG97 masks):
#if (G97PL != 0)
interrupt void ECAN0INTB_ISR(void)    // eCAN-B
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG97;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......

	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// Connected to PIEIER9_8 (use MINT9 and MG98 masks):
#if (G98PL != 0)
interrupt void ECAN1INTB_ISR(void)     // eCAN-B
{
	// Set interrupt priority:
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG98;   // Set "group"  priority	
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts	
	EINT;

  	// Insert ISR Code here.......
  
	// Restore registers saved:
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}     
#endif

// -----------------------------------------------------------
// PIE Group 10 - MUXed into CPU INT10
// -----------------------------------------------------------
// -----------------------------------------------------------
// PIE Group 11 - MUXed into CPU INT11
// -----------------------------------------------------------
// -----------------------------------------------------------
// PIE Group 12 - MUXed into CPU INT12
// -----------------------------------------------------------

//---------------------------------------------------------------------------
// Catch All Default ISRs: 
//

interrupt void EMPTY_ISR(void)  // Empty ISR - only does a return.
{

}

interrupt void PIE_RESERVED(void)  // Reserved space.  For test.
{
  asm ("      ESTOP0");
  for(;;);
}

interrupt void INT_NOTUSED_ISR(void)  // Reserved space.  For test.
{
  asm ("      ESTOP0");
  for(;;);
}

interrupt void rsvd_ISR(void)      // For test
{
  asm ("      ESTOP0");
  for(;;);
}

//===========================================================================
// No more.
//===========================================================================
