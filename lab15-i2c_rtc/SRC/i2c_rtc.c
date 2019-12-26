// TI File $Revision: /main/9 $
// Checkin $Date: August 10, 2007   09:05:58 $
//###########################################################################
//
// FILE:    Example_2833xI2c_rtc.c
//
// TITLE:   DSP2833x I2C RTC Example
//
// ASSUMPTIONS:
//
//    This program requires the DSP2833x header files.
//
//    This program requires an external I2C RTC connected to
//    the I2C bus at address 0x6f.
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
//    This program will write 1-14 words to RTC and read them back.
//    The data written and the RTC address written to are contained
//    in the message structure, I2cMsgOut1. The data read back will be
//    contained in the message structure I2cMsgIn1.
//
//    This program will work with the on-board I2C RTC supplied on
//    the F2833x eZdsp.
//
//
//###########################################################################
// Original Author: D.F.
//
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################


#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
//#define uchar unsigned char

// Note: I2C Macros used in this example can be found in the
// DSP2833x_I2C_defines.h file

// Prototype statements for functions found within this file.
void   I2CA_Init(void);
Uint16 I2CA_WriteData(struct I2CMSG *msg);
Uint16 I2CA_ReadData(struct I2CMSG *msg);
void   WriteData(struct I2CMSG *msg,Uint16 *MsgBuffer,Uint16 MemoryAdd,Uint16 NumOfBytes);
interrupt void i2c_int1a_isr(void);
void pass(void);
void fail(void);

#define I2C_SLAVE_ADDR       0x6f
#define I2C_NUMBYTES          1
#define I2C_RNUMBYTES         8
#define I2C_RTC_HIGH_ADDR  0x00
#define I2C_RTC_LOW_ADDR   0x30

Uint16	YEAR = 2011;
Uint16	MONTH = 12;
Uint16	DAY = 31;
Uint16	WEEK = 6;
Uint16	HOUR = 23;
Uint16	MINUTE = 59;
Uint16	SECOND = 49;

#define	Y2K		0x0037
#define	DW		0x0036
#define	YR		0x0035
#define	MO		0x0034
#define	DT		0x0033
#define	HR		0x0032
#define	MN		0x0031
#define	SC		0x0030

// Global variables
// Two bytes will be used for the outgoing address,
struct I2CMSG I2cMsgOut1={I2C_MSGSTAT_SEND_WITHSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          I2C_RTC_HIGH_ADDR,
                          I2C_RTC_LOW_ADDR};


struct I2CMSG I2cMsgIn1={ I2C_MSGSTAT_SEND_NOSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_RNUMBYTES,
                          I2C_RTC_HIGH_ADDR,
                          I2C_RTC_LOW_ADDR};

struct I2CMSG *CurrentMsgPtr;				// Used in interrupts
Uint16 PassCount;
Uint16 FailCount;

unsigned char Decimal_to_BCD(unsigned char temp)//十进制转换成BCD码 
{
	unsigned char a,b,c;
	a=temp;
	b=0;
	if(a>=10) 
	{
		while(a>=10) 
		{
			a=a-10;
			b=b+16;
			c=a+b;
			temp=c;
		}
	}
	return temp;
} 

unsigned char BCD_to_Decimal(unsigned char temp)//BCD码转换成十进制 
{
	unsigned char a,b,c;
	a=temp;
	b=0;
	if(a>=16) 
	{
		while(a>=16) 
		{
			a=a-16;
			b=b+10;
			c=a+b;
			temp=c;
		}
	}
	return temp;
}

void rtc(void)
{
  Uint16 i;
  Uint16 flag=1;
  while(flag)
   {
      if(I2cMsgOut1.MsgStatus == I2C_MSGSTAT_SEND_WITHSTOP)
      {
		 i = 0x02;
		 WriteData(&I2cMsgOut1,&i,0x003f,1);
		 i = 0x06;
		 WriteData(&I2cMsgOut1,&i,0x003f,1);

		// i = YEAR >> 8;
	/*	 i=Decimal_to_BCD(YEAR/100);
		 WriteData(&I2cMsgOut1,&i,Y2K,1);
		 i=(YEAR<2000)?1900:2000;
		 i = Decimal_to_BCD(YEAR-i);
		 WriteData(&I2cMsgOut1,&i,YR,1);
		 i = Decimal_to_BCD(MONTH);
		 WriteData(&I2cMsgOut1,&i,MO,1);
		 i = Decimal_to_BCD(DAY);
		 WriteData(&I2cMsgOut1,&i,DT,1);
		 i = WEEK;
		 WriteData(&I2cMsgOut1,&i,DW,1);
		 i = Decimal_to_BCD(HOUR)|0x80;
		 WriteData(&I2cMsgOut1,&i,HR,1);
		 i = Decimal_to_BCD(MINUTE);
		 WriteData(&I2cMsgOut1,&i,MN,1);
		 i = Decimal_to_BCD(SECOND);
		 WriteData(&I2cMsgOut1,&i,SC,1);*/

      }  // end of write section

      ///////////////////////////////////
      // Read data from RTC section //
      ///////////////////////////////////

      // Check outgoing message status. Bypass read section if status is
      // not inactive.
      if (I2cMsgOut1.MsgStatus == I2C_MSGSTAT_INACTIVE)
      {
         // Check incoming message status.
         if(I2cMsgIn1.MsgStatus == I2C_MSGSTAT_SEND_NOSTOP)
         {
            // RTC address setup portion
            while(I2CA_ReadData(&I2cMsgIn1) != I2C_SUCCESS)
            {
               // Maybe setup an attempt counter to break an infinite while
               // loop. The RTC will send back a NACK while it is performing
               // a write operation. Even though the write communique is
               // complete at this point, the RTC could still be busy
               // programming the data. Therefore, multiple attempts are
               // necessary.
            }
            // Update current message pointer and message status
            CurrentMsgPtr = &I2cMsgIn1;
            I2cMsgIn1.MsgStatus = I2C_MSGSTAT_SEND_NOSTOP_BUSY;
         }

         // Once message has progressed past setting up the internal address
         // of the RTC, send a restart to read the data bytes from the
         // RTC. Complete the communique with a stop bit. MsgStatus is
         // updated in the interrupt service routine.
         else if(I2cMsgIn1.MsgStatus == I2C_MSGSTAT_RESTART)
         {
            DELAY_US(1000000);
			YEAR= BCD_to_Decimal(I2cMsgIn1.MsgBuffer[7])*100
			     +BCD_to_Decimal(I2cMsgIn1.MsgBuffer[5]);
			MONTH = BCD_to_Decimal(I2cMsgIn1.MsgBuffer[4]);
			DAY = BCD_to_Decimal(I2cMsgIn1.MsgBuffer[3]);
			WEEK = I2cMsgIn1.MsgBuffer[6];
			HOUR = BCD_to_Decimal(I2cMsgIn1.MsgBuffer[2]&0x7F);
			MINUTE = BCD_to_Decimal(I2cMsgIn1.MsgBuffer[1]);
			SECOND = BCD_to_Decimal(I2cMsgIn1.MsgBuffer[0]);


            // Read data portion
            while(I2CA_ReadData(&I2cMsgIn1) != I2C_SUCCESS)
            {
               // Maybe setup an attempt counter to break an infinite while
               // loop.
            }
            // Update current message pointer and message status
            CurrentMsgPtr = &I2cMsgIn1;
            I2cMsgIn1.MsgStatus = I2C_MSGSTAT_READ_BUSY;
			flag=0;
         }
      }  // end of read section
   }
}

void main(void)
{
//   Uint16 i;

   CurrentMsgPtr = &I2cMsgOut1;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
/*   InitSysCtrl();


// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();
// Setup only the GP I/O only for I2C functionality
   InitI2CGpio();

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
   PieVectTable.I2CINT1A = &i2c_int1a_isr;
   EDIS;   // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   I2CA_Init();

// Step 5. User specific code

// Enable interrupts required for this example

// Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
   PieCtrlRegs.PIEIER8.bit.INTx1 = 1;

// Enable CPU INT8 which is connected to PIE group 8
   IER |= M_INT8;
   EINT;
*/


   InitSysCtrl();

    DINT;

 //  InitXintf16Gpio();	//zq
   
 //  InitSpiaGpio();
   
   InitI2CGpio();
   
   InitPieCtrl();
   IER = 0x0000;
   IFR = 0x0000;
  
   InitPieVectTable();  
   EALLOW;	// This is needed to write to EALLOW protected registers
   PieVectTable.I2CINT1A = &i2c_int1a_isr;
   EDIS;   
// Step 3. Initialize PIE vector table:
// Disable and clear all CPU interrupts
    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;
   I2CA_Init();
// Enable CPU INT8 which is connected to PIE group 8
   IER |= M_INT8;
   EINT;

   // Application loop
   for(;;)
   {
      //////////////////////////////////
      // Write data to RTC CTRL section //
      //////////////////////////////////

      // Check the outgoing message to see if it should be sent.
      // In this example it is initialized to send with a stop bit.
     rtc();

   }   // end of for(;;)
}   // end of main


void I2CA_Init(void)
{
   // Initialize I2C
   I2caRegs.I2CMDR.all = 0x0000;	// Take I2C reset
   									// Stop I2C when suspended

   I2caRegs.I2CFFTX.all = 0x0000;	// Disable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x0040;	// Disable RXFIFO, clear RXFFINT,

   #if (CPU_FRQ_150MHZ)             // Default - For 150MHz SYSCLKOUT
        I2caRegs.I2CPSC.all = 14;   // Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz)
   #endif
   #if (CPU_FRQ_100MHZ)             // For 100 MHz SYSCLKOUT
     I2caRegs.I2CPSC.all = 9;	    // Prescaler - need 7-12 Mhz on module clk (100/10 = 10MHz)
   #endif

   I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
   I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero
   I2caRegs.I2CIER.all = 0x24;		// Enable SCD & ARDY interrupts

   I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset
   									// Stop I2C when suspended

   I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,

   return;
}


Uint16 I2CA_WriteData(struct I2CMSG *msg)
{
   Uint16 i;

   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.
   if (I2caRegs.I2CMDR.bit.STP == 1)
   {
      return I2C_STP_NOT_READY_ERROR;
   }

   // Setup slave address
   I2caRegs.I2CSAR = msg->SlaveAddress;

   // Check if bus busy
   if (I2caRegs.I2CSTR.bit.BB == 1)
   {
      return I2C_BUS_BUSY_ERROR;
   }

   // Setup number of bytes to send
   // MsgBuffer + Address
   I2caRegs.I2CCNT = msg->NumOfBytes+2;

   // Setup data to send
   I2caRegs.I2CDXR = msg->MemoryHighAddr;
   I2caRegs.I2CDXR = msg->MemoryLowAddr;
// for (i=0; i<msg->NumOfBytes-2; i++)
   for (i=0; i<msg->NumOfBytes; i++)

   {
      I2caRegs.I2CDXR = *(msg->MsgBuffer+i);
   }

   // Send start as master transmitter
   I2caRegs.I2CMDR.all = 0x6E20;

   return I2C_SUCCESS;
}


Uint16 I2CA_ReadData(struct I2CMSG *msg)
{
   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.
   if (I2caRegs.I2CMDR.bit.STP == 1)
   {
      return I2C_STP_NOT_READY_ERROR;
   }

   I2caRegs.I2CSAR = msg->SlaveAddress;

   if(msg->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP)
   {
      // Check if bus busy
      if (I2caRegs.I2CSTR.bit.BB == 1)
      {
         return I2C_BUS_BUSY_ERROR;
      }
      I2caRegs.I2CCNT = 2;
      I2caRegs.I2CDXR = msg->MemoryHighAddr;
      I2caRegs.I2CDXR = msg->MemoryLowAddr;
      I2caRegs.I2CMDR.all = 0x2620;			// Send data to setup RTC address
   }
   else if(msg->MsgStatus == I2C_MSGSTAT_RESTART)
   {
      I2caRegs.I2CCNT = msg->NumOfBytes;	// Setup how many bytes to expect
      I2caRegs.I2CMDR.all = 0x2C20;			// Send restart as master receiver
   }

   return I2C_SUCCESS;
}

interrupt void i2c_int1a_isr(void)     // I2C-A
{
   Uint16 IntSource, i;

   // Read interrupt source
   IntSource = I2caRegs.I2CISRC.all;

   // Interrupt source = stop condition detected
   if(IntSource == I2C_SCD_ISRC)
   {
      // If completed message was writing data, reset msg to inactive state
      if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_WRITE_BUSY)
      {
         CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
      }
      else
      {
         // If a message receives a NACK during the address setup portion of the
         // RTC read, the code further below included in the register access ready
         // interrupt source code will generate a stop condition. After the stop
         // condition is received (here), set the message status to try again.
         // User may want to limit the number of retries before generating an error.
         if(CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY)
         {
            CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_SEND_NOSTOP;
         }
         // If completed message was reading RTC data, reset msg to inactive state
         // and read data from FIFO.
         else if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_READ_BUSY)
         {
            CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_SEND_NOSTOP;//I2C_MSGSTAT_INACTIVE;
            for(i=0; i < CurrentMsgPtr->NumOfBytes; i++)
            {
              CurrentMsgPtr->MsgBuffer[i] = I2caRegs.I2CDRR;
            }
		 }
      }
   }  // end of stop condition detected

   // Interrupt source = Register Access Ready
   // This interrupt is used to determine when the RTC address setup portion of the
   // read data communication is complete. Since no stop bit is commanded, this flag
   // tells us when the message has been sent instead of the SCD flag. If a NACK is
   // received, clear the NACK bit and command a stop. Otherwise, move on to the read
   // data portion of the communication.
   else if(IntSource == I2C_ARDY_ISRC)
   {
      if(I2caRegs.I2CSTR.bit.NACK == 1)
      {
         I2caRegs.I2CMDR.bit.STP = 1;
         I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
      }
      else if(CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY)
      {
         CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_RESTART;
      }
   }  // end of register access ready

   else
   {
      // Generate some error due to invalid interrupt source
      asm("   ESTOP0");
   }

   // Enable future I2C (PIE Group 8) interrupts
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}

void pass()
{
    asm("   ESTOP0");
    for(;;);
}

void fail()
{
    asm("   ESTOP0");
    for(;;);
}

void WriteData(struct I2CMSG *msg,Uint16 *MsgBuffer,Uint16 MemoryAdd,Uint16 NumOfBytes)
{
	Uint16 i,Error;
	for(i = 0; i < NumOfBytes; i++)
	{
		msg->MsgBuffer[i] = MsgBuffer[i];		
	}
	msg->MemoryHighAddr = MemoryAdd >> 8;
	msg->MemoryLowAddr = MemoryAdd & 0xff;
	msg->NumOfBytes = NumOfBytes;
	Error = I2CA_WriteData(&I2cMsgOut1);

	if (Error == I2C_SUCCESS)
	{
		CurrentMsgPtr = &I2cMsgOut1;
		I2cMsgOut1.MsgStatus = I2C_MSGSTAT_WRITE_BUSY;
	}
	while(I2cMsgOut1.MsgStatus != I2C_MSGSTAT_INACTIVE);
	DELAY_US(1000);
}

//===========================================================================
// No more.
//===========================================================================
