//############################################################################
//
// FILE:   SD_SPI_Write.c
//
// TITLE:  SD/MMC Write Data Functions
//
//############################################################################
#include "SD.h"						//SD Include File		

//############################# SD_WRITE_BLOCK ###############################
void sd_write_block(Uint16 sector, Uint8 *pBuffer)
{
	CS_LOW;							//Pull CS low
    data_manipulation = TRUE;		//Data manipulation function

	//Transmit WRITE BLOCK command
	spi_xmit_command(WRITE_BLOCK, sector, DUMMY_CRC);

	RESET_RESPONSE;					//Reset response
	while(response != SUCCESS)		//Wait until card responds with SUCCESS response
		sd_command_response();

	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
	
	//Call sd_write_data to write to specified sector
	sd_write_data(pBuffer, SINGLE_SECTOR, 0);	
			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;

	//Check card status to see if data was written properly
	sd_send_status();				

	CS_HIGH;						//Pull CS high			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
}
//############################# SD_WRITE_BLOCK ###############################


//######################## SD_WRITE_MULTIPLE_BLOCK ###########################
void sd_write_multiple_block(Uint16 sector, Uint8 *pBuffer, Uint16 total_sectors)
{
	CS_LOW;							//Pull CS low
	data_manipulation = TRUE;		//Data manipulation function
    	
	//Transmit WRITE MULTIPLE BLOCK command
	spi_xmit_command(WRITE_MULTIPLE_BLOCK, sector, DUMMY_CRC);

	RESET_RESPONSE;					//Reset response
	while(response != SUCCESS)		//Wait until card responds with SUCCESS response
		sd_command_response();

	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
	
	//Call sd_write_data to write to specified sectors
	sd_write_data(pBuffer, total_sectors, MULTIPLE_WRITE);
	
	//Set response to zero to check if card is still busy
	response = BUSY;

	//Card will respond with the DATA OUT line pulled low if the card is still busy
	//erasing. Continue checking DATA OUT line until line is released high.
	while(response != DUMMY_DATA)			 
		response = spi_xmit_byte(DUMMY_DATA);
			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;

	//Check card status to see if data was written properly
	sd_send_status();

	CS_HIGH;						//Pull CS high			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
}
//######################## SD_WRITE_MULTIPLE_BLOCK ###########################


//############################# SD_WRITE_DATA ################################
void sd_write_data(Uint8 *pBuffer, Uint16 total_sectors, Uint16 multiple_write)
{
	Uint16 i, j;
    Uint16 d=0;
	RESET_RESPONSE;					//Reset response

	//Continue this write loop for the total number of sectors required
	for(i=0;i<total_sectors;i++)
	{
		//If multiple sector write is required, send data token for multiple write
		if(multiple_write == MULTIPLE_WRITE)
			spi_xmit_byte(MULTIPLE_START_BLOCK);
		//If multiple sector write is not required, send data token for write
		else
			spi_xmit_byte(START_BLOCK);	

		//Write block of data 
		for(j=0;j<512;j++)
		 {
			d=*pBuffer;
			d<<=8;
			spi_xmit_byte(d);
			pBuffer++;
		 }

		//Transmit 0xFF 2 more times to send CRC. In SPI Mode CRC is disable by default
		//so application does not need to store it. 
		spi_xmit_byte(DUMMY_DATA);					
		spi_xmit_byte(DUMMY_DATA);

		//After data write, card with send a response stating if the card was accepted or
		//if an error occured
		while(response != DATA_ACCEPTED)
		{
			response = spi_xmit_byte(DUMMY_DATA);	
			response &= 0x0F00;		//Mask response to test for errors

			//If there where errors writing data, branch to error function
			if((response == CRC_ERROR) || (response == WRITE_ERROR))
				sd_error();	 
		}

		//Card will respond with the DATA OUT line pulled low if the card is still busy
		//erasing. Continue checking DATA OUT line until line is released high.
		while(response != DUMMY_DATA)			 
			response = spi_xmit_byte(DUMMY_DATA);
	}

	//If multiple sector write is required, send data token to end transmission
	if(multiple_write == MULTIPLE_WRITE)
		spi_xmit_byte(MULTIPLE_STOP_TRANSMISSION);
}
//############################# SD_WRITE_DATA ################################

