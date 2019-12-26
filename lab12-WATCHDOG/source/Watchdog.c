// TI File $Revision: /main/8 $
// Checkin $Date: August 10, 2007   09:07:57 $
//###########################################################################
//
// FILE:   Example_2833xWatchdog.c
//
// TITLE:  DSP2833x Watchdog interrupt test program.
//
// ASSUMPTIONS:
//
//    This program requires the DSP2833x header files.  
//
//    As supplied, this project is configured for "boot to SARAM" 
//    operation.  The 2833x Boot Mode table is shown below.  
//    For information on configuring the boot mode of an eZdsp, 
//    please refer to the documentation included with the eZdsp,  
//
//       $Boot_Table:
//
//         GPIO87   GPIO86     GPIO85   GPIO84
//          XA15     XA14       XA13     XA12
//           PU       PU         PU       PU
//        ==========================================
//            1        1          1        1    Jump to Flash
//            1        1          1        0    SCI-A boot
//            1        1          0        1    SPI-A boot
//            1        1          0        0    I2C-A boot
//            1        0          1        1    eCAN-A boot
//            1        0          1        0    McBSP-A boot
//            1        0          0        1    Jump to XINTF x16
//            1        0          0        0    Jump to XINTF x32
//            0        1          1        1    Jump to OTP
//            0        1          1        0    Parallel GPIO I/O boot
//            0        1          0        1    Parallel XINTF boot
//            0        1          0        0    Jump to SARAM	    <- "boot to SARAM"
//            0        0          1        1    Branch to check boot mode
//            0        0          1        0    Boot to flash, bypass ADC cal
//            0        0          0        1    Boot to SARAM, bypass ADC cal
//            0        0          0        0    Boot to SCI-A, bypass ADC cal
//                                              Boot_Table_End$
//
// DESCRIPTION:
//
//   This program exercises the watchdog.  
//
//   First the watchdog is connected to the WAKEINT interrupt of the
//   PIE block.  The code is then put into an infinite loop.
// 
//   The user can select to feed the watchdog key register or not
//   by commenting one line of code in the infinite loop.
//
//   If the watchdog key register is fed by the ServiceDog function 
//   then the WAKEINT interrupt is not taken.  If the key register 
//   is not fed by the ServiceDog function then WAKEINT will be taken.  
//
//      Watch Variables:
//         LoopCount for the number of times through the infinite loop
//         WakeCount for the number of times through WAKEINT
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################


#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File

// Prototype statements for functions found within this file.
interrupt void wakeint_isr(void);

// Global variables for this example
Uint32 WakeCount;
Uint32 LoopCount;

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

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.  
   EALLOW;	// This is needed to write to EALLOW protected registers
   PieVectTable.WAKEINT = &wakeint_isr;
   EDIS;   // This is needed to disable write to EALLOW protected registers
	
// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
 
// Step 5. User specific code, enable interrupts:

// Clear the counters
   WakeCount = 0; // Count interrupts
   LoopCount = 0; // Count times through idle loop

// Connect the watchdog to the WAKEINT interrupt of the PIE
// Write to the whole SCSR register to avoid clearing WDOVERRIDE bit
   EALLOW;
   SysCtrlRegs.SCSR = BIT1;
   EDIS;

// Enable WAKEINT in the PIE: Group 1 interrupt 8
// Enable INT1 which is connected to WAKEINT:
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER1.bit.INTx8 = 1;   // Enable PIE Gropu 1 INT8
   IER |= M_INT1;                       // Enable CPU int1
   EINT;                                // Enable Global Interrupts

// Reset the watchdog counter
   ServiceDog();
      
// Enable the watchdog
   EALLOW;
   SysCtrlRegs.WDCR = 0x0028;   
   EDIS;
   
// Step 6. IDLE loop. Just sit and loop forever (optional):	
   for(;;)
   {
      LoopCount++;
	    
      // Uncomment ServiceDog to just loop here
      // Comment ServiceDog to take the WAKEINT instead
    // ServiceDog();
   }
	

} 	


// Step 7. Insert all local Interrupt Service Routines (ISRs) and functions here:	
// If local ISRs are used, reassign vector addresses in vector table as
// shown in Step 5

interrupt void wakeint_isr(void)
{
	WakeCount++;
	
	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//===========================================================================
// No more.
//===========================================================================
