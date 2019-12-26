// TI File $Revision: /main/1 $
// Checkin $Date: August 29, 2007   14:07:22 $
//###########################################################################
//
// FILE:    Example_2833xFPU.c
//
// TITLE:   DSP2833x Device Getting Started Program.
//
// ASSUMPTIONS:
//
//    This program requires the DSP2833x header files.
//
//    Other then boot mode configuration, no other hardware configuration
//    is required.
//
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
// The code calculates two y=mx+b equations.  The variables are all
// 32-bit floating-point. 
//
// Two projects are supplied:
//
// Example_fpu_hardware.pjt (floating-point):
//
//    If the Example_2833xFPU_hardware.pjt file is used then the compiler 
//    will generate floating point instructions to do these calculations.
//    To compile the project for floating point, the following Build Options were used:
//    1. Project->Build Options-> Compiler Tab-> Advanced category: 
//           a. in textbox: compiler options -v28 --float_support=fpu32 are set
//           b. OR the following is equivalent to "a.": pull-down menu next to 
//              "Floating Point Support"-> "fpu32" selected.
//    2. Project->Build Options-> Linker Tab-> Libraries category: 
//           a. runtime support library used is rts2800_fpu32.lib.
//    3. Not included in this example: If the project includes any other libraries,
//       they must also be compiled with floating point instructions.
//
// Example_fpu_software.pjt (fixed-point emulates floating-point with software):
//
//    If the Example_2833xFPU_software.pjt file is used, then the compiler
//    will only used fixed point instructions.  This means the runtime 
//    support library will be used to emulate floating point. 
//    This will also run on C28x devices without the floating point unit. 
//    To compile the project for fixed point, the following Build Options were used:
//    1. Project->Build Options-> Compiler Tab-> Advanced category: 
//           a. in textbox: compiler option  --float_support=fpu32 is REMOVED
//                                            -v28 should not be removed
//           b. OR the following is equivalent to "a.": pull-down menu next to 
//              "Floating Point Support"-> "None" selected.
//    2. Project->Build Options-> Linker Tab-> Libraries category: 
//           a. runtime support library used is rts2800.lib or rts2800_ml.lib.
//    3. Not included in this example: If the project includes any other libraries,
//       they must also be compiled with fixed point instructions.
//
// Watch Variables:
//           y1
//           y2
//           FPU registers (optional)
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################


#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

float y1, y2;
float m1, m2;
float x1, x2;
float b1, b2;


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


// Step 5. User specific code, enable interrupts:

//
// Calculate two y=mx+b equations.  
   
   y1 = 0;
   y2 = 0;
   m1 = .5;
   m2 = .6;
   x1 = 3.4;
   x2 = 7.3;
   b1 = 4.2;
   b2 = 8.9;
   
   y1 = m1*x1 + b1;
   y2 = m2*x2 + b2;


   ESTOP0;  // This is a software breakpoint
}


//===========================================================================
// No more.
//===========================================================================
