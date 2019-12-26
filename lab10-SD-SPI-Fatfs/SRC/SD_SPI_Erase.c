//############################################################################
//
// FILE:   SD_SPI_Erase.c
//
// TITLE:  SD/MMC Erase Function
//

#include "SD.h"						//SD Include File		

//############################# SD_ERASE_BLOCK ###############################
void sd_erase_block(Uint16 starting_sector, Uint16 total_sectors)
{
	CS_LOW;							//Pull CS low
	data_manipulation = TRUE;		//Data manipulation function 

	//Transmit Erase Start Block Command 
	spi_xmit_command(ERASE_WR_BLK_START_ADDR, starting_sector, DUMMY_CRC);
	
	RESET_RESPONSE;					//Reset response 
	while(response != SUCCESS)		//Wait until card responds with SUCCESS response
		sd_command_response();

	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;					

	//Add starting sector to total number of sectors to find ending address 
	total_sectors += starting_sector;

	//Transmit Erase End Block command 		
	spi_xmit_command(ERASE_WR_BLK_END_ADDR, total_sectors, DUMMY_CRC);
	
	RESET_RESPONSE;					//Reset response
	while(response != SUCCESS)		//Wait until card responds with SUCCESS response
		sd_command_response();

	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;

	//Transmit ERASE command
	spi_xmit_command(ERASE, STUFF_BITS, DUMMY_CRC);
	
	RESET_RESPONSE;					//Reset response	
	while(response != SUCCESS)		//Wait until card responds with SUCCESS response
		sd_command_response();

	//Card will respond with the DATA OUT line pulled low if the card is still busy
	//erasing. Continue checking DATA OUT line until line is released high.
	while(response != DUMMY_DATA)			 
		response = spi_xmit_byte(DUMMY_DATA);
	
	CS_HIGH;						//Pull CS high			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;
}
//############################# SD_ERASE_BLOCK ###############################
