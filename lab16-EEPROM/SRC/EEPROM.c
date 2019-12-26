#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


#define	  SetData	GpioDataRegs.GPADAT.bit.GPIO20 = 1
#define	  ClrData   GpioDataRegs.GPADAT.bit.GPIO20 = 0
#define	  SetClk	GpioDataRegs.GPADAT.bit.GPIO22 = 1
#define	  ClrClk	GpioDataRegs.GPADAT.bit.GPIO22 = 0

#define	  LedReg	(*((volatile  Uint16 *)0x41FF))
Uint16    *ExRamStart = (Uint16 *)0x100000;

void InitI2C(void);
Uint16 	ReadData(Uint16  *RamAddr, Uint16	RomAddress, Uint16 number);
Uint16 	WriteData(Uint16	*Wdata, Uint16	RomAddress, Uint16	number);

Uint16	I2C_xrdy();
Uint16	I2C_rrdy();

Uint16  i;


void main(void)
{
	Uint16   dat1[8]={0,0,0,0,0,0,0,0};
	Uint16   dat[]={ 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   	InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example
   	InitXintf16Gpio();	//zq

   	InitI2CGpio();

	InitI2C();
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

	LedReg = 0xFF;

	WriteData(dat,0x60,8);
	DELAY_US(10000);
	ReadData(dat1,0x60,8);

    for(; ;)
    {

    }

}




Uint16 WriteData(Uint16	*Wdata, Uint16	RomAddress, Uint16	number)
{
   Uint16 i;
   if (I2caRegs.I2CSTR.bit.BB == 1)
   {
      return I2C_BUS_BUSY_ERROR;
   }
   while(!I2C_xrdy());
   I2caRegs.I2CSAR = 0x50;
   I2caRegs.I2CCNT = number + 1;
   I2caRegs.I2CDXR = RomAddress;
   I2caRegs.I2CMDR.all = 0x6E20;
   for (i=0; i<number; i++)
   {
      while(!I2C_xrdy());
      I2caRegs.I2CDXR = *Wdata;
      Wdata++;
	  if (I2caRegs.I2CSTR.bit.NACK == 1)
   		  return	I2C_BUS_BUSY_ERROR;
   }   	
   return I2C_SUCCESS;   
}

Uint16 ReadData(Uint16  *RamAddr, Uint16	RomAddress, Uint16 number)
{
   Uint16  i,Temp;

   if (I2caRegs.I2CSTR.bit.BB == 1)
   {
       return I2C_BUS_BUSY_ERROR;
   }
   while(!I2C_xrdy());
   I2caRegs.I2CSAR = 0x50;
   I2caRegs.I2CCNT = 1;
   I2caRegs.I2CDXR = RomAddress;
   I2caRegs.I2CMDR.all = 0x6620; 
   if (I2caRegs.I2CSTR.bit.NACK == 1)
   		return	I2C_BUS_BUSY_ERROR;
   DELAY_US(50);		
   while(!I2C_xrdy());
   I2caRegs.I2CSAR = 0x50;
   I2caRegs.I2CCNT = number;	 
   I2caRegs.I2CMDR.all = 0x6C20; 
   if (I2caRegs.I2CSTR.bit.NACK == 1)
   		return	I2C_BUS_BUSY_ERROR;
   for(i=0;i<number;i++)
   {
      while(!I2C_rrdy());
   	  Temp = I2caRegs.I2CDRR;
	  if (I2caRegs.I2CSTR.bit.NACK == 1)
   		  return	I2C_BUS_BUSY_ERROR;
   	  *RamAddr = Temp;
   	  RamAddr++;
   }
   return I2C_SUCCESS;
}


Uint16	I2C_xrdy()
{
	Uint16	t;
	t = I2caRegs.I2CSTR.bit.XRDY;
	return t;
}

Uint16	I2C_rrdy()
{
	Uint16	t;
	t = I2caRegs.I2CSTR.bit.RRDY;
	return t;
}


//===========================================================================
// No more.
//===========================================================================
