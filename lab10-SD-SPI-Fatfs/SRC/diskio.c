/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "sdio_sd.h"
#include "DSP2833x_Device.h" 
#include "SD.h"

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */

#define ATA		0
#define MMC		1
#define USB		2
BYTE  SD_Stat=0;

extern SD_CardInfo SDCardInfo;

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	switch (drv) {
	case ATA :
	
		// translate the reslut code here

		if(SD_Init()==SD_OK) {SD_Stat=1; return RES_OK;}
		                else return RES_ERROR;

	case MMC :
	//	result = MMC_disk_initialize();
		// translate the reslut code here

		return 1;

	case USB :
	//	result = USB_disk_initialize();
		// translate the reslut code here

		return 1;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
//	DSTATUS stat;
//	int result;

/*	switch (drv) {
	case ATA :
		result = ATA_disk_status();
		// translate the reslut code here

		return stat;

	case MMC :
		result = MMC_disk_status();
		// translate the reslut code here

		return stat;

	case USB :
		result = USB_disk_status();
		// translate the reslut code here

		return stat;
	}*/
	if(SD_Stat==0) return  disk_initialize(drv);
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
//	DRESULT res;
//	int result;
     if( !count )
     {    
        return RES_PARERR;  /* count不能等于0，否则返回参数错误 */
     } 

	switch (drv) {
	case ATA :
	//	result = ATA_disk_read(buff, sector, count);
		// translate the reslut code here
         sd_read_multiple_block(sector,buff,count);
		return RES_OK;

	case MMC :
	//	result = MMC_disk_read(buff, sector, count);
		// translate the reslut code here

		return RES_NOTRDY;

	case USB :
	//	result = USB_disk_read(buff, sector, count);
		// translate the reslut code here

		return RES_NOTRDY;
	}
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
//	DRESULT res;
//	int result;

	switch (drv) {
	case ATA :
	//	result = ATA_disk_write(buff, sector, count);
		// translate the reslut code here
        sd_write_multiple_block(sector,(Uint8 *)buff,count);
 	    return RES_OK;

	case MMC :
	//	result = MMC_disk_write(buff, sector, count);
		// translate the reslut code here

		return RES_NOTRDY;

	case USB :
	//	result = USB_disk_write(buff, sector, count);
		// translate the reslut code here

		return RES_NOTRDY;
	}
	return RES_PARERR;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
//	int result;
    if(drv)  return RES_PARERR; //仅支持单磁盘操作，否则返回参数错误 

switch(ctrl)  
    {  
    case CTRL_SYNC:  
      
            res = RES_OK;  
      
        break;  
  
    case GET_BLOCK_SIZE:  
        *(WORD*)buff = SDCardInfo.CardCapacity/SDCardInfo.CardBlockSize;  
        res = RES_OK;  
        break;  
  
    case GET_SECTOR_COUNT: //读卡容量  
        *(WORD*)buff = SDCardInfo.CardBlockSize; 
        break;  
  
    default:  
        res = RES_PARERR;  
        break;  
    }  
    return res;  
}

DWORD get_fattime (void)
{
   
   // return 0;
   return	  ((DWORD)(2000 - 1980) << 25)
			| ((DWORD)1 << 21)
			| ((DWORD)1 << 16)
			| ((DWORD)0 << 11)
			| ((DWORD)0 << 5)
			| ((DWORD)0 >> 1);
} 
