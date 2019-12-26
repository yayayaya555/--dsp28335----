
//###########################################################################
// Original Author H.J.
//
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

// Prototype statements for functions found within this file.
void mailbox_check(int32 T1, int32 T2, int32 T3);
void mailbox_read(int16 i); 

// Global variable for this example
Uint32  ErrorCount;
Uint32  PassCount;
Uint32  MessageReceivedCount;

Uint32  TestMbox1 = 0;
Uint32  TestMbox2 = 0;
Uint32  TestMbox3 = 0;

void main(void)
{

    Uint16  j;

// eCAN control registers require read/write access using 32-bits.  Thus we
// will create a set of shadow registers for this example.  These shadow
// registers will be used to make sure the access is 32-bits and not 16.
   struct ECAN_REGS ECanbShadow; 

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO: 
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example  

// For this example, configure CAN pins using GPIO regs here
// This function is found in DSP2833x_ECan.c
   InitECanGpio();

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
 
// Step 5. User specific code, enable interrupts:

    MessageReceivedCount = 0;
    ErrorCount = 0;
    PassCount = 0;
    
    // eCAN control registers require 32-bit access. 
    // If you want to write to a single bit, the compiler may break this
    // access into a 16-bit access.  One solution, that is presented here,
    // is to use a shadow register to force the 32-bit access. 
     
    // Read the entire register into a shadow register.  This access
    // will be 32-bits.  Change the desired bit and copy the value back
    // to the eCAN register with a 32-bit write. 
   
    // Configure the eCAN RX and TX pins for eCAN transmissions
    EALLOW;
    ECanbShadow.CANTIOC.all = ECanbRegs.CANTIOC.all;
    ECanbShadow.CANTIOC.bit.TXFUNC = 1;
    ECanbRegs.CANTIOC.all = ECanbShadow.CANTIOC.all;

    ECanbShadow.CANRIOC.all = ECanbRegs.CANRIOC.all;
    ECanbShadow.CANRIOC.bit.RXFUNC = 1;
    ECanbRegs.CANRIOC.all = ECanbShadow.CANRIOC.all;
    EDIS;
     
    // Disable all Mailboxes
    // Since this write is to the entire register (instead of a bit
    // field) a shadow register is not required.
    ECanbRegs.CANME.all = 0;

    // Mailboxs can be written to 16-bits or 32-bits at a time
    // Write to the MSGID field of TRANSMIT mailboxes MBOX0 - 15 
    ECanbMboxes.MBOX0.MSGID.all = 0x9555AAA0; 
    ECanbMboxes.MBOX1.MSGID.all = 0x9555AAA1; 
    ECanbMboxes.MBOX2.MSGID.all = 0x9555AAA2; 
    ECanbMboxes.MBOX3.MSGID.all = 0x9555AAA3; 
    ECanbMboxes.MBOX4.MSGID.all = 0x9555AAA4; 
    ECanbMboxes.MBOX5.MSGID.all = 0x9555AAA5; 
    ECanbMboxes.MBOX6.MSGID.all = 0x9555AAA6; 
    ECanbMboxes.MBOX7.MSGID.all = 0x9555AAA7; 
    ECanbMboxes.MBOX8.MSGID.all = 0x9555AAA8; 
    ECanbMboxes.MBOX9.MSGID.all = 0x9555AAA9; 
    ECanbMboxes.MBOX10.MSGID.all = 0x9555AAAA; 
    ECanbMboxes.MBOX11.MSGID.all = 0x9555AAAB; 
    ECanbMboxes.MBOX12.MSGID.all = 0x9555AAAC; 
    ECanbMboxes.MBOX13.MSGID.all = 0x9555AAAD; 
    ECanbMboxes.MBOX14.MSGID.all = 0x9555AAAE; 
    ECanbMboxes.MBOX15.MSGID.all = 0x9555AAAF; 
    
    // Write to the MSGID field of RECEIVE mailboxes MBOX16 - 31
    ECanbMboxes.MBOX16.MSGID.all = 0x9555AAA0; 
    ECanbMboxes.MBOX17.MSGID.all = 0x9555AAA1; 
    ECanbMboxes.MBOX18.MSGID.all = 0x9555AAA2; 
    ECanbMboxes.MBOX19.MSGID.all = 0x9555AAA3; 
    ECanbMboxes.MBOX20.MSGID.all = 0x9555AAA4; 
    ECanbMboxes.MBOX21.MSGID.all = 0x9555AAA5; 
    ECanbMboxes.MBOX22.MSGID.all = 0x9555AAA6; 
    ECanbMboxes.MBOX23.MSGID.all = 0x9555AAA7; 
    ECanbMboxes.MBOX24.MSGID.all = 0x9555AAA8; 
    ECanbMboxes.MBOX25.MSGID.all = 0x9555AAA9; 
    ECanbMboxes.MBOX26.MSGID.all = 0x9555AAAA; 
    ECanbMboxes.MBOX27.MSGID.all = 0x9555AAAB; 
    ECanbMboxes.MBOX28.MSGID.all = 0x9555AAAC; 
    ECanbMboxes.MBOX29.MSGID.all = 0x9555AAAD; 
    ECanbMboxes.MBOX30.MSGID.all = 0x9555AAAE; 
    ECanbMboxes.MBOX31.MSGID.all = 0x9555AAAF; 

    // Configure Mailboxes 0-15 as Tx, 16-31 as Rx 
    // Since this write is to the entire register (instead of a bit
    // field) a shadow register is not required.
    ECanbRegs.CANMD.all = 0xFFFF0000; 
    
    // Enable all Mailboxes */
    // Since this write is to the entire register (instead of a bit
    // field) a shadow register is not required.
    ECanbRegs.CANME.all = 0xFFFFFFFF;

    // Specify that 8 bits will be sent/received
    ECanbMboxes.MBOX0.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX1.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX2.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX3.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX4.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX5.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX6.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX7.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX8.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX9.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX10.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX11.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX12.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX13.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX14.MSGCTRL.bit.DLC = 8;
    ECanbMboxes.MBOX15.MSGCTRL.bit.DLC = 8;
    
    // No remote frame is requested
    // Since RTR bit is undefined upon reset,
    // it must be initialized to the proper value 
    ECanbMboxes.MBOX0.MSGCTRL.bit.RTR = 0;      
    ECanbMboxes.MBOX1.MSGCTRL.bit.RTR = 0;  
    ECanbMboxes.MBOX2.MSGCTRL.bit.RTR = 0;  
    ECanbMboxes.MBOX3.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX4.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX5.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX6.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX7.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX8.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX9.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX10.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX11.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX12.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX13.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX14.MSGCTRL.bit.RTR = 0;
    ECanbMboxes.MBOX15.MSGCTRL.bit.RTR = 0;
    
    // Write to the mailbox RAM field of MBOX0 - 15
    ECanbMboxes.MBOX0.MDL.all = 0x9555AAA0;
    ECanbMboxes.MBOX0.MDH.all = 0x89ABCDEF;

    ECanbMboxes.MBOX1.MDL.all = 0x9555AAA1;
    ECanbMboxes.MBOX1.MDH.all = 0x89ABCDEF;
   
    ECanbMboxes.MBOX2.MDL.all = 0x9555AAA2;
    ECanbMboxes.MBOX2.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX3.MDL.all = 0x9555AAA3;
    ECanbMboxes.MBOX3.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX4.MDL.all = 0x9555AAA4;
    ECanbMboxes.MBOX4.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX5.MDL.all = 0x9555AAA5;
    ECanbMboxes.MBOX5.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX6.MDL.all = 0x9555AAA6;
    ECanbMboxes.MBOX6.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX7.MDL.all = 0x9555AAA7;
    ECanbMboxes.MBOX7.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX8.MDL.all = 0x9555AAA8;
    ECanbMboxes.MBOX8.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX9.MDL.all = 0x9555AAA9;
    ECanbMboxes.MBOX9.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX10.MDL.all = 0x9555AAAA;
    ECanbMboxes.MBOX10.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX11.MDL.all = 0x9555AAAB;
    ECanbMboxes.MBOX11.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX12.MDL.all = 0x9555AAAC;
    ECanbMboxes.MBOX12.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX13.MDL.all = 0x9555AAAD;
    ECanbMboxes.MBOX13.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX14.MDL.all = 0x9555AAAE;
    ECanbMboxes.MBOX14.MDH.all = 0x89ABCDEF;
 
    ECanbMboxes.MBOX15.MDL.all = 0x9555AAAF;
    ECanbMboxes.MBOX15.MDH.all = 0x89ABCDEF;

    // Since this write is to the entire register (instead of a bit
    // field) a shadow register is not required. 
    EALLOW;
    ECanbRegs.CANMIM.all = 0xFFFFFFFF;

    // Request permission to change the configuration registers
    ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
    ECanbShadow.CANMC.bit.CCR = 1;            
    ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;
    EDIS;
    
    // Wait until the CPU has been granted permission to change the
    // configuration registers
    // Wait for CCE bit to be set..
    do 
    {
      ECanbShadow.CANES.all = ECanbRegs.CANES.all;
    } while(ECanbShadow.CANES.bit.CCE != 1 );  
    
    // Configure the eCAN timing
    EALLOW;
    ECanbShadow.CANBTC.all = ECanbRegs.CANBTC.all;

    ECanbShadow.CANBTC.bit.BRPREG = 9;    // (BRPREG + 1) = 10 feeds a 15 MHz CAN clock
    ECanbShadow.CANBTC.bit.TSEG2REG = 5 ; // to the CAN module. (150 / 10 = 15)
    ECanbShadow.CANBTC.bit.TSEG1REG = 7;  // Bit time = 15
    ECanbRegs.CANBTC.all = ECanbShadow.CANBTC.all;
    
    ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
    ECanbShadow.CANMC.bit.CCR = 0;            
    ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;
    EDIS;

    // Wait until the CPU no longer has permission to change the
    // configuration registers
    do
    {
      ECanbShadow.CANES.all = ECanbRegs.CANES.all;
    } while(ECanbShadow.CANES.bit.CCE != 0 ); 

    // Configure the eCAN for self test mode 
    // Enable the enhanced features of the eCAN.
    EALLOW;
    ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
    ECanbShadow.CANMC.bit.STM = 1;    // Configure CAN for self-test mode  
    ECanbShadow.CANMC.bit.SCB = 1;    // eCAN mode (reqd to access 32 mailboxes)
    ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;
    EDIS;
    
    // Begin transmitting 
    for(;;)                                
    {
     
       ECanbRegs.CANTRS.all = 0x0000FFFF;  // Set TRS for all transmit mailboxes
       while(ECanbRegs.CANTA.all != 0x0000FFFF ) {}  // Wait for all TAn bits to be set..
       ECanbRegs.CANTA.all = 0x0000FFFF;   // Clear all TAn    
       MessageReceivedCount++;

       //Read from Receive mailboxes and begin checking for data */
       for(j=0; j<16; j++)         // Read & check 16 mailboxes
       {
          mailbox_read(j);         // This func reads the indicated mailbox data
          mailbox_check(TestMbox1,TestMbox2,TestMbox3); // Checks the received data
       }

       if(MessageReceivedCount > 100)
       {
	      if(ErrorCount == 0)
		  {
			asm("      ESTOP0"); // OK
		  }
		  else
		  {
			asm("      ESTOP0"); // ERROR
		  }
       } 
    }
}

// This function reads out the contents of the indicated 
// by the Mailbox number (MBXnbr).
void mailbox_read(int16 MBXnbr)
{
   volatile struct MBOX *Mailbox;
   Mailbox = &ECanbMboxes.MBOX0 + MBXnbr;
   TestMbox1 = Mailbox->MDL.all; // = 0x9555AAAn (n is the MBX number)
   TestMbox2 = Mailbox->MDH.all; // = 0x89ABCDEF (a constant)
   TestMbox3 = Mailbox->MSGID.all;// = 0x9555AAAn (n is the MBX number)

} // MSGID of a rcv MBX is transmitted as the MDL data.


void mailbox_check(int32 T1, int32 T2, int32 T3)
{
    if((T1 != T3) || ( T2 != 0x89ABCDEF))
    {
       ErrorCount++;
    }
    else
    {
       PassCount++;
    }
}


//===========================================================================
// No more.
//===========================================================================
