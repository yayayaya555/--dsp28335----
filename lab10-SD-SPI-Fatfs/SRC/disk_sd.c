//############################################################################
//
// FILE:   SD_SPI_Read.c
//
// TITLE:  SD/MMC Read Data Functions
//
#include "sdio_sd.h"
#include "SD.h"		

SD_CardInfo SDCardInfo;

SD_Error SD_Init(void)
{
  SD_Error errorstatus = SD_OK;
  	sd_card_insertion();			//Check for card insertion
	sd_initialization();			//Initialize card

	sd_read_register(SEND_CSD);		//Read CSD register
	sd_read_register(READ_OCR);		//Read OCR register
	sd_read_register(SEND_CID);		//Read CID register
  return(errorstatus);
}
/*
SD_Error SD_Erase(Uint32 startaddr, Uint32 endaddr)
{
  SD_Error errorstatus = SD_OK;
  sd_erase_block(startaddr,endaddr);
  return(errorstatus);
}*/

SD_Error SD_ReadBlock(Uint8 *readbuff, Uint32 ReadAddr, Uint16 BlockSize)
{
  SD_Error errorstatus = SD_OK;
  if (0 == readbuff)
  {
    errorstatus = SD_INVALID_PARAMETER;
    return(errorstatus);
  }
  sd_read_block(ReadAddr,readbuff);

  errorstatus = SD_OK;
  return(errorstatus);
}

SD_Error SD_ReadMultiBlocks(Uint8 *readbuff, Uint32 ReadAddr, 
                            Uint16 BlockSize, Uint32 NumberOfBlocks)
{
   SD_Error errorstatus = SD_OK;
  if (0 == readbuff)
  {
    errorstatus = SD_INVALID_PARAMETER;
    return(errorstatus);
  }
  sd_read_multiple_block(ReadAddr,readbuff,NumberOfBlocks);

  errorstatus = SD_OK;
  return(errorstatus);
}

SD_Error SD_WriteBlock(Uint8 *writebuff, Uint32 WriteAddr, Uint16 BlockSize)
{
  SD_Error errorstatus = SD_OK;
  if (0 == writebuff)
  {
    errorstatus = SD_INVALID_PARAMETER;
    return(errorstatus);
  }
  sd_write_block(WriteAddr,writebuff);

  errorstatus = SD_OK;
  return(errorstatus);
}

SD_Error SD_WriteMultiBlocks(Uint8 *writebuff, Uint32 WriteAddr, 
                             Uint16 BlockSize, Uint32 NumberOfBlocks)
{
   SD_Error errorstatus = SD_OK;
  if (0 == writebuff)
  {
    errorstatus = SD_INVALID_PARAMETER;
    return(errorstatus);
  }
  sd_write_multiple_block(WriteAddr,writebuff,NumberOfBlocks);

  errorstatus = SD_OK;
  return(errorstatus);
}


//########################### SD_DATA_RESPONSE ###############################

