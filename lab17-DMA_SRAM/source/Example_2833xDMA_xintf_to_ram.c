// TI File $Revision: /main/1 $
// Checkin $Date: August 29, 2007   14:07:44 $
//###########################################################################
//
// FILE:   Example_2833xDMA_XINTF_to_Ram.c
//
// TITLE:  DSP2833x DMA Ram to Ram
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
//
// DESCRIPTION:
//
// Code will perform a block copy of 1024 words from Zone 6 XINTF (DMABuf2) 
// to L4 SARAM (DMABuf1) .  
// Transfer will be started by Timer0.  
// We will use 32-bit DMA datasize.  Note this is independent from the XINTF
// data width which is x16. Code will end in local_DINTCH1_ISR once the transfer is 
// complete
//
// Watch Variables:
//      DMABuf1
//      DMABuf2
//
//###########################################################################
//
// Original source by: M.P.
//
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


#define BUF_SIZE   1024  // Sample buffer size


#pragma DATA_SECTION(DMABuf1,"DMARAML4");
#pragma DATA_SECTION(DMABuf2,"ZONE6DATA");

volatile Uint16 DMABuf1[BUF_SIZE];
volatile Uint16 DMABuf2[BUF_SIZE];

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

interrupt void local_DINTCH1_ISR(void);
void init_zone6(void);


void main(void)
{
   Uint16 i;
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();


// Step 2. Initialize GPIO:
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
   EALLOW;	// Allow access to EALLOW protected registers
   PieVectTable.DINTCH1= &local_DINTCH1_ISR;
   EDIS;   // Disable access to EALLOW protected registers
   IER = M_INT7 ;	                             //Enable INT7 (7.1 DMA Ch1)
   EnableInterrupts();
   CpuTimer0Regs.TCR.bit.TSS  = 1;               //Stop Timer0 for now


//Step 5. User specific code, enable interrupts:
  // Initialize DMA 
	DMAInitialize();
    init_zone6();

	// Initialize Tables
   for (i=0; i<BUF_SIZE; i++)
   {
     DMABuf1[i] = 0;
	 DMABuf2[i] = i;
   }

	
// Configure DMA Channel
    DMADest   = &DMABuf1[0];
	DMASource = &DMABuf2[0];
   	DMACH1AddrConfig(DMADest,DMASource);
	DMACH1BurstConfig(31,2,2);         //Will set up to use 32-bit datasize, pointers are based on 16-bit words
	DMACH1TransferConfig(31,2,2);      //so need to increment by 2 to grab the correct location
	DMACH1WrapConfig(0xFFFF,0,0xFFFF,0);
	//Use timer0 to start the x-fer.  
	//Since this is a static copy use one shot mode, so only one trigger is needed
	//Also using 32-bit mode to decrease x-fer time
    DMACH1ModeConfig(DMA_TINT0,PERINT_ENABLE,ONESHOT_ENABLE,CONT_DISABLE,SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,THIRTYTWO_BIT,CHINT_END,CHINT_ENABLE); 

 

												 

	StartDMACH1();

    
   //Init the timer 0

   CpuTimer0Regs.TIM.half.LSW = 512;    //load low value so we can start the DMA quickly
   CpuTimer0Regs.TCR.bit.SOFT = 1;      //Allow to free run even if halted
   CpuTimer0Regs.TCR.bit.FREE = 1; 
   CpuTimer0Regs.TCR.bit.TIE  = 1;      //Enable the timer0 interrupt signal
   CpuTimer0Regs.TCR.bit.TSS  = 0;      //restart the timer 0
   for(;;);
   
}

// INT7.1
interrupt void local_DINTCH1_ISR(void)     // DMA Channel 1
{
   Uint16 i;  
  // To receive more interrupts from this PIE group, acknowledge this interrupt 
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   for (i=0; i<BUF_SIZE; i++)
   {
     if(DMABuf1[i] != i)
	 {
		asm ("      ESTOP0");//error
		break;
	 }
   }
   asm ("      ESTOP0");//ok
   for(;;);
}


// Configure the timing paramaters for Zone 6.
// Notes: 
//    This function should not be executed from XINTF
//    Adjust the timing based on the data manual and
//    external device requirements.     
void init_zone6(void)
{
	EALLOW;
    // Make sure the XINTF clock is enabled
	SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;
	EDIS; 
	// Configure the GPIO for XINTF with a 16-bit data bus
	// This function is in DSP2833x_Xintf.c
	InitXintf16Gpio();

    // All Zones---------------------------------
    // Timing for all zones based on XTIMCLK = SYSCLKOUT 
	EALLOW;
    XintfRegs.XINTCNF2.bit.XTIMCLK = 0;
    // Buffer up to 3 writes
    XintfRegs.XINTCNF2.bit.WRBUFF = 3;
    // XCLKOUT is enabled
    XintfRegs.XINTCNF2.bit.CLKOFF = 0;
    // XCLKOUT = XTIMCLK 
    XintfRegs.XINTCNF2.bit.CLKMODE = 0;   

    // Zone 6------------------------------------
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    XintfRegs.XTIMING6.bit.XWRLEAD = 1;
    XintfRegs.XTIMING6.bit.XWRACTIVE = 2;
    XintfRegs.XTIMING6.bit.XWRTRAIL = 1;
    // Zone read timing
    XintfRegs.XTIMING6.bit.XRDLEAD = 1;
    XintfRegs.XTIMING6.bit.XRDACTIVE = 3;
    XintfRegs.XTIMING6.bit.XRDTRAIL = 0;
    
    // don't double all Zone read/write lead/active/trail timing 
    XintfRegs.XTIMING6.bit.X2TIMING = 0;
 
    // Zone will not sample XREADY signal  
    XintfRegs.XTIMING6.bit.USEREADY = 0;
    XintfRegs.XTIMING6.bit.READYMODE = 0;
 
    // 1,1 = x16 data bus
    // 0,1 = x32 data bus
    // other values are reserved
    XintfRegs.XTIMING6.bit.XSIZE = 3;
    EDIS; 
   //Force a pipeline flush to ensure that the write to 
   //the last register configured occurs before returning.  
   asm(" RPT #7 || NOP"); 
}



