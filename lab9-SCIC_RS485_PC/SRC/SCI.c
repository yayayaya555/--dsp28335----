#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

// Prototype statements for functions found within this file.
void scib_echoback_init(void);
void scib_xmit(int a);
void scib_msg(char *msg);

#define InitDIR()                                          \
                     EALLOW;                               \
                     GpioCtrlRegs.GPBPUD.bit.GPIO61 = 0;   \
                     GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;   \
                     GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1; \
                     EDIS;                                 					 
#define RX_EN       GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
#define TX_EN       GpioDataRegs.GPBSET.bit.GPIO61 = 1;


void main(void)
{

    Uint16 ReceivedChar;
    char *msg;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   // InitGpio(); Skipped for this example

// For this example, only init the pins for the SCI-A port.
// This function is found in the DSP2833x_Sci.c file.
   InitScicGpio();
   InitDIR();
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

// Step 5. User specific code:


   // scic_fifo_init();	   // Initialize the SCI FIFO
    scib_echoback_init();  // Initalize SCI for echoback

    msg = "\r\n\n\nHello Yan Xu!\0";
    scib_msg(msg);

    msg = "\r\nYou will enter a character, and the DSP will echo it back! \n\0";
    scib_msg(msg);

	for(;;)
    {
       msg = "\r\nEnter a character: \0";
       scib_msg(msg);

       // Wait for inc character
       while(ScicRegs.SCIRXST.bit.RXRDY !=1) { } // wait for XRDY =1 for empty state

       // Get character
       ReceivedChar = ScicRegs.SCIRXBUF.all;

       // Echo character back
       msg = "  You sent: \0";
       scib_msg(msg);
	  
       scib_xmit(ReceivedChar);

    
    }

}


// Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void scib_echoback_init()
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    ScicRegs.SCICTL1.bit.SWRESET =0;
 	ScicRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	ScicRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE

	#if (CPU_FRQ_150MHZ)
	      ScicRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 37.5MHz.
	      ScicRegs.SCILBAUD    =0x00E7;
	#endif
	#if (CPU_FRQ_100MHZ)
      ScicRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.
      ScicRegs.SCILBAUD    =0x0044;
	#endif
	ScicRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
}


// Transmit a character from the SCI
void scib_xmit(int a)
{
    while (ScicRegs.SCICTL2.bit.TXRDY == 0) {}
    ScicRegs.SCITXBUF=a;

}

void scib_msg(char * msg)
{
    int i;
    i = 0;
	TX_EN;
    while(msg[i] != '\0')
    {
        scib_xmit(msg[i]);
        i++;
    }
	RX_EN;
}


//===========================================================================
// No more.
//===========================================================================

