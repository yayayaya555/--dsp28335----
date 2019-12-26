#include "SD.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "sdio_sd.h"
#include "ff.h"
#include <stdio.h>

FATFS fs;         /* Work area (file system object) for logical drive */
FIL fsrc;         /* file objects */   
FRESULT res=FR_OK;
UINT br;

char path[512]="0:";
Uint8 textFileBuffer[] = "感谢您使用研旭28335开发版 ！^_^ \r\n";   

void main(void)
{

//	Uint16 i, testdata = 0x0000;
   FRESULT h;
   char m[]="0:/fatfs.txt";
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example
// Setup only the GP I/O only for SPI-A functionality

   InitXintf16Gpio();	//zq

   InitSpiaGpio();

// Step 3. Initialize PIE vector table:
// Disable and clear all CPU interrupts
   DINT;
   IER = 0x0000;
   IFR = 0x0000;
  /*  while(*i!=0) 
	 {
        *i=0;
		i++;
	 }*/
// 	Initialize the PIE vector table with pointers to the shell Interrupt 
// 	Service Routines (ISR).  
// 	This will populate the entire table, even if the interrupt
// 	is not used in this example.  This is useful for debug purposes.
// 	The shell ISR routines are found in DSP280x_DefaultIsr.c.
// 	This function is found in DSP280x_PieVect.c.
   	InitPieVectTable();

// 	Step 4. Initialize all the Device Peripherals:
   	spi_initialization();					//Initialize SPI	

// 	Step 5. User specific code:	

	//Initialize test data for known data to transmit to card
/*	for(i=0;i<1024;i++)						 
	{										
		write_buffer[i] = testdata;
		testdata += 0x0100;			//Card accepts 8 bit data so upper 8 bits are used
	}

   	sd_card_insertion();			//Check for card insertion
	sd_initialization();			//Initialize card

	sd_read_register(SEND_CSD);		//Read CSD register
	sd_read_register(READ_OCR);		//Read OCR register
	sd_read_register(SEND_CID);		//Read CID register
*/
//	disk_initialize(0);
    res = f_unlink(m);//删除SD卡内同名文件
	h=f_mount(0,&fs);  
	if(h!=FR_OK)  asm(" ESTOP0"); //文件注册失败，程序暂停

	res = f_open( &fsrc , m , FA_CREATE_ALWAYS | FA_WRITE);//FA_CREATE_NEW | FA_WRITE);		

    if ( res == FR_OK )
    { 
      /* Write buffer to file */
      res = f_write(&fsrc, textFileBuffer, sizeof(textFileBuffer), &br);     
 
    
      /*close file */
      f_close(&fsrc); //如果此句屏蔽则文件内容不会被写入SD卡     
    }
//	res = f_unlink(m);
//	res=f_read(&fsrc,read,sizeof(textFileBuffer), &br);
	
    asm(" ESTOP0");				//Emulation stop
   	for(;;){};					//Loop forever
} 	





//===========================================================================
// No more.
//===========================================================================

