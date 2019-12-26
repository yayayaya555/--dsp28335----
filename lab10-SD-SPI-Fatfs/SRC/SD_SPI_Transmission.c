//############################################################################
//
// FILE:   SD_SPI_Transmission.c
//
// TITLE:  SD/MMC SPI Transmission and Error Functions
//
//############################################################################
#include "SD.h"						//SD Include File		

//############################# SPI_XMIT_BYTE ################################
Uint16 spi_xmit_byte(Uint16 byte)
{
  	SpiaRegs.SPITXBUF = byte;         			//Transmit Byte
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1); 	//Wait until the RXBUF has received last bit
  	return (SpiaRegs.SPIRXBUF<<8);			//Read Byte from RXBUF and return
}
//############################# SPI_XMIT_BYTE ################################


//############################ SPI_XMIT_COMMAND ##############################
void spi_xmit_command(Uint16 command, Uint32 data, Uint16 crc)
{
	Uint16 i, full_command[6];			
	
	//If data manipulation is requested from standard capacity card,
	//multiply data by 512 to receive full address to transmit
	if((data_manipulation == TRUE) && (high_capacity == FALSE))
		data *= BLOCK_LENGTH;					 
	
	//Set first element of full_command to the command to be transmitted
	full_command[0] = command;		

	//This loop breaks the data/address into 4 bytes to be transmitted. Since 
	//the data is brought into function as a long, it must be typecast to an unsigned
	//integer to transmit properly. The data is anded with 0xFF to get what data is located
	//in the last two bytes of data. Data is then right shifted by eight to test the next 
	//byte.  
	for(i=4;i>0;i--)
	{
		full_command[i] = ((Uint16)(Uint32)(data & 0x000000FF) << 8);
		data = data >> 8;
	}
    
	//Set last element of full_command to the crc value to be transmitted
	if(crc_enabled == TRUE)
    	full_command[5] = sd_crc7(full_command);
	else
		full_command[5] = crc;
    
    for(i=0;i<6;i++)						//Transmit full command 
    	spi_xmit_byte(full_command[i]);			
} 
//############################ SPI_XMIT_COMMAND ##############################


//################################ SD_CRC7 ###################################
Uint16 sd_crc7(Uint16 full_command[6])
{
	Uint16 i,j,command,crc = 0x0000;
   	                                           
    for (i=0;i<5;i++)
    {
		command = full_command[i];		
       	for (j=0;j<8;j++)
      	{
         	crc = crc << 1;					//Shift crc left by 1			
         	if ((command ^ crc) & 0x8000)	//Test command XOR with crc and masked with 0x8000
         		crc = crc ^ 0x0900;  		//XOR crc with 0x0900           
         	command = command << 1;			//Shift command left by 1
      	}

       	crc = crc & 0x7F00;					//Mask CRC with 0x7F00	
   	}
   
   	crc = crc << 1;							//Shift crc left by 1
   	crc |= 0x0100;							//CRC ORed with 0x0100
   
  	return(crc);							//Return CRC
}
//################################ SD_CRC7 ###################################


//########################## SD_COMMAND_RESPONSE #############################
void sd_command_response()
{
	Uint16 i;

	RESET_RESPONSE;							//Reset Response
		
	//This loop continously transmits 0xFF in order to receive response from card. 
	//The card is expected to return 00 or 01 stating that it is in idle state or 
	//it has finished it's initialization(SUCCESS). If anything is received besides
	//0x00, 0x01, or 0xFF then an error has occured. 
	for(i=0;i<8;i++)
	{
		response = spi_xmit_byte(DUMMY_DATA);
		//If response is 0x00 or 0x01 break from loop		
		if ((response == IN_IDLE_STATE) || (response == SUCCESS))
			break;
		//If response is not 0x00, 0x01, or 0xFF branch to sd_error
		else if (response != DUMMY_DATA)
			sd_error();
	}
}
//########################## SD_COMMAND_RESPONSE #############################


//############################### SD_ERROR ###################################
void sd_error()
{	
	//For this example all errors are sent to this trap function. Specific application 
	//will have to be written to handle errors.
	 
	CS_HIGH;								//Pull CS high			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;

	asm(" ESTOP0");							//Emulation stop
   	for(;;){};								//Loop forever
}
//############################### SD_ERROR ###################################
