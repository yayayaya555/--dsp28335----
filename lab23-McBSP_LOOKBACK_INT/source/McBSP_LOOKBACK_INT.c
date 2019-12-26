//###########################################################################
//
// FILE:   Example_2833xMCBSP_FFDLB_int.c
//
// TITLE:  DSP2833x Device McBSP Digital Loop Back porgram
//
// ASSUMPTIONS:
//
//    This program requires the DSP2833x header files.
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
// This program is a McBSP example that uses the internal loopback of
// the peripheral.  Both Rx and Tx interrupts are enabled.
//
// Incrementing values from 0x0000 to 0x00FF are being sent and received.
//
// This pattern is repeated forever.
//
// By default for the McBSP examples, the McBSP sample rate generator (SRG) input
// clock frequency is LSPCLK (150E6/4 or 100E6/4) assuming SYSCLKOUT = 150 MHz or
// 100 MHz respectively.  If while testing, the SRG input frequency
// is changed, the #define MCBSP_SRG_FREQ  (150E6/4 or 100E6/4) in the Mcbsp.c file must
// also be updated accordingly.  This define is used to determine the Mcbsp initialization
// delay after the SRG is enabled, which must be at least 2 SRG clock cycles.
//
//   Watch Variables:
//                sdata
//                rdata
//                rdata_point
//
//###########################################################################
//
// Original Source by S.D.
//
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################



#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

// Prototype statements for functions found within this file.

interrupt void Mcbsp_TxINTA_ISR(void);
interrupt void Mcbsp_RxINTA_ISR(void);
void mcbsp_init_dlb(void);
void error(void);

// Global data variables used for this example
Uint16 sdata;    // Sent Data
Uint16 rdata;    // Recieved Data
Uint16 rdata_point; // Keep track of where we
                    // are in the data stream


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
// Setup only the GP I/O only for McBSP-A functionality
   InitMcbspaGpio();

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
   EALLOW;	// Allow access to EALLOW protected registers
   PieVectTable.MRINTA= &Mcbsp_RxINTA_ISR;
   PieVectTable.MXINTA= &Mcbsp_TxINTA_ISR;
   EDIS;   // Disable access to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   mcbsp_init_dlb();      // For this example, only initialize the Mcbsp


// Step 5. User specific code, enable interrupts:

   sdata = 0;
   rdata_point = sdata;

// Enable interrupts required for this example
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER6.bit.INTx5=1;     // Enable PIE Group 6, INT 5
   PieCtrlRegs.PIEIER6.bit.INTx6=1;     // Enable PIE Group 6, INT 6
   IER=0x20;                            // Enable CPU INT6
   EINT;                                // Enable Global Interrupts

// Step 6. IDLE loop. Just sit and loop forever (optional):
   for(;;);

}


// Step 7. Insert all local Interrupt Service Routines (ISRs) and functions here:


void error(void)
{
    asm("     ESTOP0"); // Test failed!! Stop!
    for (;;);
}

void mcbsp_init_dlb()
{

//*************** RESET MCBSP
   McbspaRegs.SPCR2.bit.FRST=0; // Frame Sync generator reset
   McbspaRegs.SPCR2.bit.GRST=0; // Sample Rate generator Reset
   McbspaRegs.SPCR2.bit.XRST=0; // Transmitter reset
   McbspaRegs.SPCR1.bit.RRST=0; // Receiver reset

//*************** Initialize McBSP Registers
// McBSP register settings for Digital loop back
   McbspaRegs.SPCR2.all=0x0000; // XRST =0
   McbspaRegs.SPCR1.all=0x8000; // RRST =0, DLB enabled
   McbspaRegs.RCR2.all=0x0001;  // RDATDLY = 1
   McbspaRegs.RCR1.all=0x0;
   McbspaRegs.XCR2.all=0x0001;  // XDATDLY = 1
   McbspaRegs.XCR1.all=0x0;

   McbspaRegs.SRGR2.all=0x3140;
   McbspaRegs.SRGR1.all=0x010f;
   McbspaRegs.MCR2.all=0x0;
   McbspaRegs.MCR1.all=0x0;
   McbspaRegs.PCR.all=0x0A00;

   McbspaRegs.MFFINT.bit.XINT = 1; // Enable Transmit Interrupts
   McbspaRegs.MFFINT.bit.RINT = 1; // Enable Receive Interrupts

//************* Enable Sample rate generator
   McbspaRegs.SPCR2.bit.GRST=1;
//   delay_loop();                   // Wait at least 2 SRG clock cycles

//************ Enable TX/RX unit
   McbspaRegs.SPCR2.bit.XRST=1;
   McbspaRegs.SPCR1.bit.RRST=1;

//************ Frame Sync generator reset
   McbspaRegs.SPCR2.bit.FRST=1;
}

interrupt void Mcbsp_TxINTA_ISR(void)
{
    McbspaRegs.DXR1.all= sdata;
    sdata = (sdata+1)& 0x00FF ;
    // To receive more interrupts from this PIE group, acknowledge this interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
}

interrupt void Mcbsp_RxINTA_ISR(void)
{
    rdata=McbspaRegs.DRR1.all;
    if (rdata != ( (rdata_point) & 0x00FF) ) error();
    rdata_point = (rdata_point+1) & 0x00FF;
    // To receive more interrupts from this PIE group, acknowledge this interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
}

//===========================================================================
// No more.
//===========================================================================

