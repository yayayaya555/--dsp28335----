// TI File $Revision: /main/8 $
// Checkin $Date: August 10, 2007   09:06:32 $
//###########################################################################
//
// FILE:   Example_2833xSpi_FFDLB.c
//
// TITLE:  DSP2833x Device Spi Digital Loop Back program. 
//
// ASSUMPTIONS:
//
//    This program requires the DSP2833x header files. 
// 
//    This program uses the internal loop back test mode of the peripheral. 
//    Other then boot mode pin configuration, no other hardware configuration
//    is required. 
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
//    This program is a SPI example that uses the internal loopback of
//    the peripheral.  Interrupts are not used.
//
//    A stream of data is sent and then compared to the recieved stream.
//  
//    The sent data looks like this:
//    0000 0001 0002 0003 0004 0005 0006 0007 .... FFFE FFFF
//
//    This pattern is repeated forever.  
//
//          Watch Variables:         
//                sdata - sent data
//                rdata - received data
//		
////###########################################################################		
// Original Author: S.S.
//
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################


#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


#define	  SetData	GpioDataRegs.GPADAT.bit.GPIO20 = 1
#define	  ClrData   GpioDataRegs.GPADAT.bit.GPIO20 = 0
#define	  SetClk	GpioDataRegs.GPADAT.bit.GPIO22 = 1
#define	  ClrClk	GpioDataRegs.GPADAT.bit.GPIO22 = 0

#define	  LedReg	(*((volatile  Uint16 *)0x41FF))
#define   SysReg    (*((volatile  Uint16 *)0x42FF))    
Uint16    *ExRamStart = (Uint16 *)0x100000;

void	SendData(Uint16 data);

// Prototype statements for functions found within this file.
// interrupt void ISRTimer2(void);
void delay_loop(void);
void spi_xmit(Uint16 a);
void spi_fifo_init(void);
void spi_init(void);
void error(void);

void main(void)
{
   Uint16 sdata;  // send data
   Uint16 rdata;  // received data
   
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO: 
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example  
// Setup only the GP I/O only for SPI-A functionality
// This function is found in DSP2833x_Spi.c

   InitXintf16Gpio();	//zq

   InitSpiaGpio();

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
// InitPeripherals(); // Not required for this example
   spi_fifo_init();	  // Initialize the Spi FIFO
   spi_init();		  // init SPI

// Step 5. User specific code:
// Interrupts are not used in this example. 
	SendData(0xFF);
	LedReg = 0xFF;
   sdata = 0x0000;							
   for(;;)
   {    
     // Transmit data
     spi_xmit(sdata);
     // Wait until data is received
     while(SpiaRegs.SPIFFRX.bit.RXFFST !=1) { } 			
     // Check against sent data
     rdata = SpiaRegs.SPIRXBUF;				
     if(rdata != sdata) error();
     sdata++;
   }
} 	


// Step 7. Insert all local Interrupt Service Routines (ISRs) and functions here:	

void delay_loop()
{
    long      i;
    for (i = 0; i < 1000000; i++) {}
}


void error(void)
{
    asm("     ESTOP0");						// Test failed!! Stop!
    for (;;);
}

void spi_init()
{    
	SpiaRegs.SPICCR.all =0x000F;	             // Reset on, rising edge, 16-bit char bits  
	SpiaRegs.SPICTL.all =0x0006;    		     // Enable master mode, normal phase,
                                                 // enable talk, and SPI int disabled.
	SpiaRegs.SPIBRR =0x007F;									
    SpiaRegs.SPICCR.all =0x009F;		         // Relinquish SPI from Reset   
    SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
}

void spi_xmit(Uint16 a)
{
    SpiaRegs.SPITXBUF=a;
}    

void spi_fifo_init()										
{
// Initialize SPI FIFO registers
    SpiaRegs.SPIFFTX.all=0xE040;
    SpiaRegs.SPIFFRX.all=0x204f;
    SpiaRegs.SPIFFCT.all=0x0;
}  

void	SendData(Uint16 data)
{
	Uint16	i,Temp;
	Temp = 0x80;
	for	(i=0;i<8;i++)
		{
			if ((data & Temp)==0)	ClrData;
			else	SetData;
			Temp >>= 1;
			DELAY_US(100);
			ClrClk;
			DELAY_US(200);
			SetClk;
		}
	SysReg = 0xEF;
	DELAY_US(200);	
	SysReg = 0xFF ;
	SetData;		
}		

//===========================================================================
// No more.
//===========================================================================

