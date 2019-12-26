//############################################################################
//
// FILE:   SD_SPI_Read.c
//
// TITLE:  SD/MMC Read Data Functions
//
#include "SD.h"						//SD Include File		

//############################# SD_READ_BLOCK ################################
void sd_read_block(Uint16 sector, Uint8 *pBuffer)
{
	CS_LOW;							//Pull CS low
	data_manipulation = TRUE;		//Data manipulation function

	//Transmit READ SINGLE BLOCK command
	spi_xmit_command(READ_SINGLE_BLOCK, sector, DUMMY_CRC);	
	
	RESET_RESPONSE;					//Reset Response
	while(response != SUCCESS)		//Wait until card responds with SUCCESS response
		sd_command_response();

	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;

	//Call sd_data_response to read specified sector
	sd_data_response(pBuffer, SINGLE_SECTOR);	

	CS_HIGH;						//Pull CS high			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
}
//############################# SD_READ_BLOCK ################################


//######################## SD_READ_MULTIPLE_BLOCK ############################
void sd_read_multiple_block(Uint16 sector, Uint8 *pBuffer, Uint16 total_sectors)
{
	Uint16 i;

	CS_LOW;							//Pull CS low
	data_manipulation = TRUE;		//Data manipulation function

	//Transmit READ MULTIPLE BLOCK command
	spi_xmit_command(READ_MULTIPLE_BLOCK, sector, DUMMY_CRC);	
	
	RESET_RESPONSE;					//Reset response
	while(response != SUCCESS)		//Wait until card responds with SUCCESS response
		sd_command_response();

	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
	
	//Call sd_data_response to read specified sectors
	sd_data_response(pBuffer, total_sectors);
	
	//Transmit STOP TRANSMISSION command			
	spi_xmit_command(STOP_TRANSMISSION, STUFF_BITS, DUMMY_CRC);
	
	RESET_RESPONSE;					//Reset response

	//Wait 64 clock cycles or until card responds with SUCCESS response to move on
	for(i=0;i<8;i++)
	{
		response = spi_xmit_byte(DUMMY_DATA);
		if (response == SUCCESS)
		 	break;
	}
	
	CS_HIGH;						//Pull CS high			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
}
//######################## SD_READ_MULTIPLE_BLOCK ############################


//########################### SD_DATA_RESPONSE ###############################
void sd_data_response(Uint8 *pBuffer, Uint16 total_sectors)
{
	Uint16 i, j;

	data_manipulation = TRUE;		//Data manipulation function

	//Continue until all total sectors requested are transmitted
	for(i=0;i<total_sectors;i++)	
	{
		RESET_RESPONSE;				//Reset response
		//This loop continues receiving a response from the card until a START_BLOCK
		//or and error response is transmitted. If response is START_BLOCK then 
		//data will be transmitted. If response is an error the data will not be
		//transmitted.
		while(response != START_BLOCK)
		{
			response = spi_xmit_byte(DUMMY_DATA);
				
			if((response == ERROR) || (response == CC_ERROR) || \
			(response == CARD_ECC_FAILED) || (response == OUT_OF_RANGE))
				sd_error();
		}
			
		for(j=0;j<512;j++)			//Read block of data
			//Store data to address referred to by pBuffer
			*pBuffer++ = (spi_xmit_byte(DUMMY_DATA)>>8);	

		//Transmit 0xFF 2 more times to receive CRC. In SPI Mode CRC is disabled by default
		//so application does not need to store it. 
		spi_xmit_byte(DUMMY_DATA);					
		spi_xmit_byte(DUMMY_DATA);
	}
	
	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;			
}
//########################### SD_DATA_RESPONSE ###############################

