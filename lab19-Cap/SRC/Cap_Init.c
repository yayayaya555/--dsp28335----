// TI File $Revision: /main/7 $
// Checkin $Date: September 20, 2007   13:30:31 $
//###########################################################################
//
// FILE:   DSP2833x_Cap_Init.c
//
// TITLE:  DSP2833x Device System Control Initialization & Support Functions.
//
// DESCRIPTION:
//
//         Example initialization of system resources.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################


#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File

// Functions that will be run from RAM need to be assigned to
// a different section.  This section will then be mapped to a load and
// run address using the linker cmd file.

#pragma CODE_SECTION(InitFlash, "ramfuncs");

//---------------------------------------------------------------------------
// InitSysCtrl:
//---------------------------------------------------------------------------
// This function initializes the System Control registers to a known state.
// - Disables the watchdog
// - Set the PLLCR for proper SYSCLKOUT frequency
// - Set the pre-scaler for the high and low frequency peripheral clocks
// - Enable the clocks to the peripherals

void InitCapl(void)
{
 ChoseCap();
 InitECap1Gpio();
 InitECap2Gpio();
 SetCap1Mode();
 SetCap2Mode(); 
}
void ChoseCap(void)
{ SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK=1;//enable clock to Cap1
  SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK=1;
  //SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK=1;
  //SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK=1;
  //SysCtrlRegs.PCLKCR1.bit.ECAP5ENCLK=1;
  //SysCtrlRegs.PCLKCR1.bit.ECAP6ENCLK=1;
  }
void InitECapGpio()
{

   InitECap1Gpio();
#if (DSP28_ECAP2)
   InitECap2Gpio();
#endif // endif DSP28_ECAP2
#if (DSP28_ECAP3)
   InitECap3Gpio();
#endif // endif DSP28_ECAP3
#if (DSP28_ECAP4)
   InitECap4Gpio();
#endif // endif DSP28_ECAP4
#if (DSP28_ECAP5)
   InitECap5Gpio();
#endif // endif DSP28_ECAP5
#if (DSP28_ECAP6)
   InitECap6Gpio();
#endif // endif DSP28_ECAP6
}

void InitECap1Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

 //  GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;      // Enable pull-up on GPIO5 (CAP1)
  GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;     // Enable pull-up on GPIO24 (CAP1)
// GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;     // Enable pull-up on GPIO34 (CAP1)


// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

 //  GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 0;    // Synch to SYSCLKOUT GPIO5 (CAP1)
  GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;   // Synch to SYSCLKOUT GPIO24 (CAP1)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 0;   // Synch to SYSCLKOUT GPIO34 (CAP1)

/* Configure eCAP-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP1 functional pins.
// Comment out other unwanted lines.

  //  GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;     // Configure GPIO5 as CAP1
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;    // Configure GPIO24 as CAP1
// GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 1;    // Configure GPIO24 as CAP1

    EDIS;
}

#if DSP28_ECAP2
void InitECap2Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

 //  GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;     // Enable pull-up on GPIO7 (CAP2)
 GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;    // Enable pull-up on GPIO25 (CAP2)
// GpioCtrlRegs.GPBPUD.bit.GPIO37 = 0;    // Enable pull-up on GPIO37 (CAP2)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

  // GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;    // Synch to SYSCLKOUT GPIO7 (CAP2)
GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;   // Synch to SYSCLKOUT GPIO25 (CAP2)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO37 = 0;   // Synch to SYSCLKOUT GPIO37 (CAP2)

/* Configure eCAP-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP2 functional pins.
// Comment out other unwanted lines.

 //  GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 3;    // Configure GPIO7 as CAP2
  GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;   // Configure GPIO25 as CAP2
// GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 3;   // Configure GPIO37 as CAP2

    EDIS;
}
#endif // endif DSP28_ECAP2

#if DSP28_ECAP3
void InitECap3Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;      // Enable pull-up on GPIO9 (CAP3)
// GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;     // Enable pull-up on GPIO26 (CAP3)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 0;    // Synch to SYSCLKOUT GPIO9 (CAP3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;   // Synch to SYSCLKOUT GPIO26 (CAP3)

/* Configure eCAP-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP3 functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 3;     // Configure GPIO9 as CAP3
// GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    // Configure GPIO26 as CAP3

    EDIS;
}
#endif // endif DSP28_ECAP3


#if DSP28_ECAP4
void InitECap4Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;   // Enable pull-up on GPIO11 (CAP4)
// GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   // Enable pull-up on GPIO27 (CAP4)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 0; // Synch to SYSCLKOUT GPIO11 (CAP4)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0; // Synch to SYSCLKOUT GPIO27 (CAP4)

/* Configure eCAP-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP4 functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;  // Configure GPIO11 as CAP4
// GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;  // Configure GPIO27 as CAP4

    EDIS;
}
#endif // endif DSP28_ECAP4


#if DSP28_ECAP5
void InitECap5Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;     // Enable pull-up on GPIO3 (CAP5)
// GpioCtrlRegs.GPBPUD.bit.GPIO48 = 0;    // Enable pull-up on GPIO48 (CAP5)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 0;  // Synch to SYSCLKOUT GPIO3 (CAP5)
// GpioCtrlRegs.GPBQSEL2.bit.GPIO48 = 0; // Synch to SYSCLKOUT GPIO48 (CAP5)

/* Configure eCAP-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP5 functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 2;   // Configure GPIO3 as CAP5
// GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 1;  // Configure GPIO48 as CAP5

    EDIS;
}
#endif // endif DSP28_ECAP5


#if DSP28_ECAP6
void InitECap6Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;     // Enable pull-up on GPIO1 (CAP6)
// GpioCtrlRegs.GPBPUD.bit.GPIO49 = 0;    // Enable pull-up on GPIO49 (CAP6)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 0;  // Synch to SYSCLKOUT GPIO1 (CAP6)
// GpioCtrlRegs.GPBQSEL2.bit.GPIO49 = 0; // Synch to SYSCLKOUT GPIO49 (CAP6)

/* Configure eCAP-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP6 functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 2;   // Configure GPIO1 as CAP6
// GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 1;  // Configure GPIO49 as CAP6

    EDIS;
}  
#endif // endif DSP28_ECAP6 
void SetCap1Mode(void)
{
  ECap1Regs.ECCTL1.bit.CAP1POL = EC_RISING;
  ECap1Regs.ECCTL1.bit.CAP2POL = EC_RISING;
  ECap1Regs.ECCTL1.bit.CAP3POL = EC_RISING;
  ECap1Regs.ECCTL1.bit.CAP4POL = EC_RISING;
  ECap1Regs.ECCTL1.bit.CTRRST1 = EC_ABS_MODE;
  ECap1Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;
  ECap1Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;
  ECap1Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;
  ECap1Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;
  ECap1Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
  ECap1Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;
  ECap1Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;
  ECap1Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
  ECap1Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;
  ECap1Regs.ECEINT.all=0x0000;//stop all interrupt
  ECap1Regs.ECCLR.all=0xFFFF;//clare all flag
  ECap1Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;// Æô¶¯
  ECap1Regs.ECEINT.bit.CEVT4=1;// Enable cevt4 interrupt
}


void SetCap2Mode(void)
{
  ECap2Regs.ECCTL1.bit.CAP1POL = EC_FALLING;
  ECap2Regs.ECCTL1.bit.CAP2POL = EC_FALLING;
  ECap2Regs.ECCTL1.bit.CAP3POL = EC_FALLING;
  ECap2Regs.ECCTL1.bit.CAP4POL = EC_FALLING;
  ECap2Regs.ECCTL1.bit.CTRRST1 = EC_ABS_MODE;
  ECap2Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;
  ECap2Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;
  ECap2Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;
  ECap2Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;
  ECap2Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
  ECap2Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;
  ECap2Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;
  ECap2Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
  ECap2Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;
  ECap2Regs.ECEINT.all=0x0000;//stop all interrupt
  ECap2Regs.ECCLR.all=0xFFFF;//clare all flag
  ECap2Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;// Æô¶¯
  ECap2Regs.ECEINT.bit.CEVT4=1;// Enable cevt4 interrupt
}
//===========================================================================
// End of file.
//===========================================================================
