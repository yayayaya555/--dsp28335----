//############################################################################
//
// FILE:   SD_SPI_Registers.c
//
// TITLE:  SD/MMC Register Manipulation Functions
//
//############################################################################
#include "SD.h"						//SD Include File		

//############################ SD_READ_REGISTER ##############################
void sd_read_register(Uint16 command)
{
	CS_LOW;							//Pull CS low
	data_manipulation = FALSE;		//Register manipulation function

	//Transmit register command requested
	spi_xmit_command(command, STUFF_BITS, DUMMY_CRC);				
	
	RESET_RESPONSE;					//Reset response
	while(response != SUCCESS)		//Wait until card responds with SUCCESS response
		sd_command_response();
	
	if(command == READ_OCR)			//Test if OCR register is requested					
		sd_ocr_response();			//Call sd_ocr_response to read OCR register
	else
		//Call sd_cid_csd_response to read CID or CSD registers
		sd_cid_csd_response(command);

	CS_HIGH;						//Pull CS high			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
}
//############################ SD_READ_REGISTER ##############################


//############################ SD_OCR_RESPONSE ###############################
void sd_ocr_response()
{
	Uint16 i;
	
	//OCR register is five bytes. Transmit 0xFF 5 times to receive the contents
	//of OCR register and store them.
	for(i=0;i<4;i++)						 
		ocr_contents[i] = spi_xmit_byte(DUMMY_DATA);

	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
}
//############################ SD_OCR_RESPONSE ###############################


//########################## SD_CID_CSD_RESPONSE #############################
void sd_cid_csd_response(Uint16 command)
{
	Uint16 i;

	RESET_RESPONSE;					//Reset Response
	while(response != START_BLOCK)	//Wait until START BLOCK is received
		response = spi_xmit_byte(DUMMY_DATA);

	//CID and CSD Registers are 16 bytes. Transmit 0xFF 16 times to receive the contents
	//of CID or CSD Register and store them.
	for(i=0;i<16;i++)
	{
		if(command == SEND_CSD)
			csd_contents[i] = spi_xmit_byte(DUMMY_DATA);
		else
			cid_contents[i] = spi_xmit_byte(DUMMY_DATA);			
	}

	//Transmit 0xFF 2 more times to receive CRC. In SPI Mode CRC is disable by default
	//so application does not need to store it. 
	spi_xmit_byte(DUMMY_DATA);					
	spi_xmit_byte(DUMMY_DATA);
	
	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;				
}
//########################## SD_CID_CSD_RESPONSE #############################


//############################# SD_SEND_STATUS ###############################
void sd_send_status()
{
	data_manipulation = FALSE;		//Register manipulation function

	//Transmit SEND STATUS command
	spi_xmit_command(SEND_STATUS, STUFF_BITS, DUMMY_CRC);

	RESET_RESPONSE;					//Reset response
	while(response == DUMMY_DATA)	//Wait until response is not 0xFF
		response = spi_xmit_byte(DUMMY_DATA);
	
	card_status[0] = response;					//Store first byte of Status register
	card_status[1] = spi_xmit_byte(DUMMY_DATA);	//Store second byte of status register

	//If either byte of CARD STATUS is not SUCCESS, error was generated.
	if((card_status[0] != SUCCESS) || (card_status[1] != SUCCESS))
		sd_error();								//Branch to error function

	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
}
//############################# SD_SEND_STATUS ###############################

