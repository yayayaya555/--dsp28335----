/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               sdio_sd.h
** Descriptions:            sdio sd卡操作头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-10-30
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SDIO_SD_H
#define __SDIO_SD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File


typedef enum
{
/** 
  * @brief  SDIO specific error defines  
  */   
  SD_CMD_CRC_FAIL                    = (1), /*!< Command response received (but CRC check failed) */
  SD_DATA_CRC_FAIL                   = (2), /*!< Data bock sent/received (CRC check Failed) */
  SD_CMD_RSP_TIMEOUT                 = (3), /*!< Command response timeout */
  SD_DATA_TIMEOUT                    = (4), /*!< Data time out */
  SD_TX_UNDERRUN                     = (5), /*!< Transmit FIFO under-run */
  SD_RX_OVERRUN                      = (6), /*!< Receive FIFO over-run */
  SD_START_BIT_ERR                   = (7), /*!< Start bit not detected on all data signals in widE bus mode */
  SD_CMD_OUT_OF_RANGE                = (8), /*!< CMD's argument was out of range.*/
  SD_ADDR_MISALIGNED                 = (9), /*!< Misaligned address */
  SD_BLOCK_LEN_ERR                   = (10), /*!< Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
  SD_ERASE_SEQ_ERR                   = (11), /*!< An error in the sequence of erase command occurs.*/
  SD_BAD_ERASE_PARAM                 = (12), /*!< An Invalid selection for erase groups */
  SD_WRITE_PROT_VIOLATION            = (13), /*!< Attempt to program a write protect block */
  SD_LOCK_UNLOCK_FAILED              = (14), /*!< Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
  SD_COM_CRC_FAILED                  = (15), /*!< CRC check of the previous command failed */
  SD_ILLEGAL_CMD                     = (16), /*!< Command is not legal for the card state */
  SD_CARD_ECC_FAILED                 = (17), /*!< Card internal ECC was applied but failed to correct the data */
  SD_CC_ERROR                        = (18), /*!< Internal card controller error */
  SD_GENERAL_UNKNOWN_ERROR           = (19), /*!< General or Unknown error */
  SD_STREAM_READ_UNDERRUN            = (20), /*!< The card could not sustain data transfer in stream read operation. */
  SD_STREAM_WRITE_OVERRUN            = (21), /*!< The card could not sustain data programming in stream mode */
  SD_CID_CSD_OVERWRITE               = (22), /*!< CID/CSD overwrite error */
  SD_WP_ERASE_SKIP                   = (23), /*!< only partial address space was erased */
  SD_CARD_ECC_DISABLED               = (24), /*!< Command has been executed without using internal ECC */
  SD_ERASE_RESET                     = (25), /*!< Erase sequence was cleared before executing because an out of erase sequence command was received */
  SD_AKE_SEQ_ERROR                   = (26), /*!< Error in sequence of authentication. */
  SD_INVALID_VOLTRANGE               = (27),
  SD_ADDR_OUT_OF_RANGE               = (28),
  SD_SWITCH_ERROR                    = (29),
  SD_SDIO_DISABLED                   = (30),
  SD_SDIO_FUNCTION_BUSY              = (31),
  SD_SDIO_FUNCTION_FAILED            = (32),
  SD_SDIO_UNKNOWN_FUNCTION           = (33),

/** 
  * @brief  Standard error defines   
  */ 
  SD_INTERNAL_ERROR, 
  SD_NOT_CONFIGURED,
  SD_REQUEST_PENDING, 
  SD_REQUEST_NOT_APPLICABLE, 
  SD_INVALID_PARAMETER,  
  SD_UNSUPPORTED_FEATURE,  
  SD_UNSUPPORTED_HW,  
  SD_ERROR,  
  SD_OK  
} SD_Error;



/** 
  * @brief  SDIO Transfer state  
  */   
typedef enum
{
  SD_TRANSFER_OK  = 0,
  SD_TRANSFER_BUSY = 1,
  SD_TRANSFER_ERROR
} SDTransferState;

/** 
  * @brief  SD Card States 
  */   
typedef enum
{
  SD_CARD_READY                  = ((Uint32)0x00000001),
  SD_CARD_IDENTIFICATION         = ((Uint32)0x00000002),
  SD_CARD_STANDBY                = ((Uint32)0x00000003),
  SD_CARD_TRANSFER               = ((Uint32)0x00000004),
  SD_CARD_SENDING                = ((Uint32)0x00000005),
  SD_CARD_RECEIVING              = ((Uint32)0x00000006),
  SD_CARD_PROGRAMMING            = ((Uint32)0x00000007),
  SD_CARD_DISCONNECTED           = ((Uint32)0x00000008),
  SD_CARD_ERROR                  = ((Uint32)0x000000FF)
}SDCardState;


/** 
  * @brief  Card Specific Data: CSD Register   
  */ 
typedef struct
{
  __IO Uint8  CSDStruct;            /*!< CSD structure */
  __IO Uint8  SysSpecVersion;       /*!< System specification version */
  __IO Uint8  Reserved1;            /*!< Reserved */
  __IO Uint8  TAAC;                 /*!< Data read access-time 1 */
  __IO Uint8  NSAC;                 /*!< Data read access-time 2 in CLK cycles */
  __IO Uint8  MaxBusClkFrec;        /*!< Max. bus clock frequency */
  __IO Uint16 CardComdClasses;      /*!< Card command classes */
  __IO Uint8  RdBlockLen;           /*!< Max. read data block length */
  __IO Uint8  PartBlockRead;        /*!< Partial blocks for read allowed */
  __IO Uint8  WrBlockMisalign;      /*!< Write block misalignment */
  __IO Uint8  RdBlockMisalign;      /*!< Read block misalignment */
  __IO Uint8  DSRImpl;              /*!< DSR implemented */
  __IO Uint8  Reserved2;            /*!< Reserved */
  __IO Uint32 DeviceSize;           /*!< Device Size */
  __IO Uint8  MaxRdCurrentVDDMin;   /*!< Max. read current @ VDD min */
  __IO Uint8  MaxRdCurrentVDDMax;   /*!< Max. read current @ VDD max */
  __IO Uint8  MaxWrCurrentVDDMin;   /*!< Max. write current @ VDD min */
  __IO Uint8  MaxWrCurrentVDDMax;   /*!< Max. write current @ VDD max */
  __IO Uint8  DeviceSizeMul;        /*!< Device size multiplier */
  __IO Uint8  EraseGrSize;          /*!< Erase group size */
  __IO Uint8  EraseGrMul;           /*!< Erase group size multiplier */
  __IO Uint8  WrProtectGrSize;      /*!< Write protect group size */
  __IO Uint8  WrProtectGrEnable;    /*!< Write protect group enable */
  __IO Uint8  ManDeflECC;           /*!< Manufacturer default ECC */
  __IO Uint8  WrSpeedFact;          /*!< Write speed factor */
  __IO Uint8  MaxWrBlockLen;        /*!< Max. write data block length */
  __IO Uint8  WriteBlockPaPartial;  /*!< Partial blocks for write allowed */
  __IO Uint8  Reserved3;            /*!< Reserded */
  __IO Uint8  ContentProtectAppli;  /*!< Content protection application */
  __IO Uint8  FileFormatGrouop;     /*!< File format group */
  __IO Uint8  CopyFlag;             /*!< Copy flag (OTP) */
  __IO Uint8  PermWrProtect;        /*!< Permanent write protection */
  __IO Uint8  TempWrProtect;        /*!< Temporary write protection */
  __IO Uint8  FileFormat;           /*!< File Format */
  __IO Uint8  ECC;                  /*!< ECC code */
  __IO Uint8  CSD_CRC;              /*!< CSD CRC */
  __IO Uint8  Reserved4;            /*!< always 1*/
} SD_CSD;

/** 
  * @brief  Card Identification Data: CID Register   
  */
typedef struct
{
  __IO Uint8  ManufacturerID;       /*!< ManufacturerID */
  __IO Uint16 OEM_AppliID;          /*!< OEM/Application ID */
  __IO Uint32 ProdName1;            /*!< Product Name part1 */
  __IO Uint8  ProdName2;            /*!< Product Name part2*/
  __IO Uint8  ProdRev;              /*!< Product Revision */
  __IO Uint32 ProdSN;               /*!< Product Serial Number */
  __IO Uint8  Reserved1;            /*!< Reserved1 */
  __IO Uint16 ManufactDate;         /*!< Manufacturing Date */
  __IO Uint8  CID_CRC;              /*!< CID CRC */
  __IO Uint8  Reserved2;            /*!< always 1 */
} SD_CID;

/** 
  * @brief SD Card information 
  */
typedef struct
{
  SD_CSD SD_csd;
  SD_CID SD_cid;
  Uint32 CardCapacity;  /*!< Card Capacity */
  Uint32 CardBlockSize; /*!< Card Block Size */
  Uint16 RCA;
  Uint8 CardType;
} SD_CardInfo;


/** 
  * @brief  SDIO Data Transfer Frequency (25MHz max) 
  */
//#define SDIO_TRANSFER_CLK_DIV            ((Uint8)0x1) 

//#define SD_DETECT_PIN                    GPIO_Pin_10                 /* PF.10 */
//#define SD_DETECT_GPIO_PORT              GPIOF                       /* GPIOF */
//#define SD_DETECT_GPIO_CLK               RCC_APB2Periph_GPIOF

/** 
  * @brief  SDIO Intialization Frequency (400KHz max)
  */
//#define SDIO_INIT_CLK_DIV                ((Uint8)0xB2)
//#define SDIO_FIFO_ADDRESS                ((Uint32)0x40018080)


/** 
  * @brief SDIO Commands  Index 
  */
#define SD_CMD_GO_IDLE_STATE                       ((Uint8)0)
#define SD_CMD_SEND_OP_COND                        ((Uint8)1)
#define SD_CMD_ALL_SEND_CID                        ((Uint8)2)
#define SD_CMD_SET_REL_ADDR                        ((Uint8)3) /*!< SDIO_SEND_REL_ADDR for SD Card */
#define SD_CMD_SET_DSR                             ((Uint8)4)
#define SD_CMD_SDIO_SEN_OP_COND                    ((Uint8)5)
#define SD_CMD_HS_SWITCH                           ((Uint8)6)
#define SD_CMD_SEL_DESEL_CARD                      ((Uint8)7)
#define SD_CMD_HS_SEND_EXT_CSD                     ((Uint8)8)
#define SD_CMD_SEND_CSD                            ((Uint8)9)
#define SD_CMD_SEND_CID                            ((Uint8)10)
#define SD_CMD_READ_DAT_UNTIL_STOP                 ((Uint8)11) /*!< SD Card doesn't support it */
#define SD_CMD_STOP_TRANSMISSION                   ((Uint8)12)
#define SD_CMD_SEND_STATUS                         ((Uint8)13)
#define SD_CMD_HS_BUSTEST_READ                     ((Uint8)14)
#define SD_CMD_GO_INACTIVE_STATE                   ((Uint8)15)
#define SD_CMD_SET_BLOCKLEN                        ((Uint8)16)
#define SD_CMD_READ_SINGLE_BLOCK                   ((Uint8)17)
#define SD_CMD_READ_MULT_BLOCK                     ((Uint8)18)
#define SD_CMD_HS_BUSTEST_WRITE                    ((Uint8)19)
#define SD_CMD_WRITE_DAT_UNTIL_STOP                ((Uint8)20) /*!< SD Card doesn't support it */
#define SD_CMD_SET_BLOCK_COUNT                     ((Uint8)23) /*!< SD Card doesn't support it */
#define SD_CMD_WRITE_SINGLE_BLOCK                  ((Uint8)24)
#define SD_CMD_WRITE_MULT_BLOCK                    ((Uint8)25)
#define SD_CMD_PROG_CID                            ((Uint8)26) /*!< reserved for manufacturers */
#define SD_CMD_PROG_CSD                            ((Uint8)27)
#define SD_CMD_SET_WRITE_PROT                      ((Uint8)28)
#define SD_CMD_CLR_WRITE_PROT                      ((Uint8)29)
#define SD_CMD_SEND_WRITE_PROT                     ((Uint8)30)
#define SD_CMD_SD_ERASE_GRP_START                  ((Uint8)32) /*!< To set the address of the first write
                                                                  block to be erased. (For SD card only) */
#define SD_CMD_SD_ERASE_GRP_END                    ((Uint8)33) /*!< To set the address of the last write block of the
                                                                  continuous range to be erased. (For SD card only) */
#define SD_CMD_ERASE_GRP_START                     ((Uint8)35) /*!< To set the address of the first write block to be erased.
                                                                  (For MMC card only spec 3.31) */

#define SD_CMD_ERASE_GRP_END                       ((Uint8)36) /*!< To set the address of the last write block of the
                                                                  continuous range to be erased. (For MMC card only spec 3.31) */

#define SD_CMD_ERASE                               ((Uint8)38)
#define SD_CMD_FAST_IO                             ((Uint8)39) /*!< SD Card doesn't support it */
#define SD_CMD_GO_IRQ_STATE                        ((Uint8)40) /*!< SD Card doesn't support it */
#define SD_CMD_LOCK_UNLOCK                         ((Uint8)42)
#define SD_CMD_APP_CMD                             ((Uint8)55)
#define SD_CMD_GEN_CMD                             ((Uint8)56)
#define SD_CMD_NO_CMD                              ((Uint8)64)

/** 
  * @brief Following commands are SD Card Specific commands.
  *        SDIO_APP_CMD should be sent before sending these commands. 
  */
#define SD_CMD_APP_SD_SET_BUSWIDTH                 ((Uint8)6)  /*!< For SD Card only */
#define SD_CMD_SD_APP_STAUS                        ((Uint8)13) /*!< For SD Card only */
#define SD_CMD_SD_APP_SEND_NUM_WRITE_BLOCKS        ((Uint8)22) /*!< For SD Card only */
#define SD_CMD_SD_APP_OP_COND                      ((Uint8)41) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CLR_CARD_DETECT          ((Uint8)42) /*!< For SD Card only */
#define SD_CMD_SD_APP_SEND_SCR                     ((Uint8)51) /*!< For SD Card only */
#define SD_CMD_SDIO_RW_DIRECT                      ((Uint8)52) /*!< For SD I/O Card only */
#define SD_CMD_SDIO_RW_EXTENDED                    ((Uint8)53) /*!< For SD I/O Card only */

/** 
  * @brief Following commands are SD Card Specific security commands.
  *        SDIO_APP_CMD should be sent before sending these commands. 
  */
#define SD_CMD_SD_APP_GET_MKB                      ((Uint8)43) /*!< For SD Card only */
#define SD_CMD_SD_APP_GET_MID                      ((Uint8)44) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CER_RN1                  ((Uint8)45) /*!< For SD Card only */
#define SD_CMD_SD_APP_GET_CER_RN2                  ((Uint8)46) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CER_RES2                 ((Uint8)47) /*!< For SD Card only */
#define SD_CMD_SD_APP_GET_CER_RES1                 ((Uint8)48) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_READ_MULTIPLE_BLOCK   ((Uint8)18) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK  ((Uint8)25) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_ERASE                 ((Uint8)38) /*!< For SD Card only */
#define SD_CMD_SD_APP_CHANGE_SECURE_AREA           ((Uint8)49) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_WRITE_MKB             ((Uint8)48) /*!< For SD Card only */
  
#define SD_DMA_MODE                                ((Uint32)0x00000000)
#define SD_INTERRUPT_MODE                          ((Uint32)0x00000001)
#define SD_POLLING_MODE                            ((Uint32)0x00000002)

/**
  * @brief  SD detection on its memory slot
  */
#define SD_PRESENT                                 ((Uint8)0x01)
#define SD_NOT_PRESENT                             ((Uint8)0x00)

/** 
  * @brief Supported SD Memory Cards 
  */
  /*
#define SDIO_STD_CAPACITY_SD_CARD_V1_1             ((Uint32)0x00000000)
#define SDIO_STD_CAPACITY_SD_CARD_V2_0             ((Uint32)0x00000001)
#define SDIO_HIGH_CAPACITY_SD_CARD                 ((Uint32)0x00000002)
#define SDIO_MULTIMEDIA_CARD                       ((Uint32)0x00000003)
#define SDIO_SECURE_DIGITAL_IO_CARD                ((Uint32)0x00000004)
#define SDIO_HIGH_SPEED_MULTIMEDIA_CARD            ((Uint32)0x00000005)
#define SDIO_SECURE_DIGITAL_IO_COMBO_CARD          ((Uint32)0x00000006)
#define SDIO_HIGH_CAPACITY_MMC_CARD                ((Uint32)0x00000007)
*/

//void SD_DeInit(void);
SD_Error SD_Init(void);
//SDTransferState SD_GetStatus(void);
//SDCardState SD_GetState(void);
//Uint8 SD_Detect(void);
//SD_Error SD_PowerON(void);
//SD_Error SD_PowerOFF(void);
//SD_Error SD_InitializeCards(void);
//SD_Error SD_GetCardInfo(SD_CardInfo *cardinfo);
//SD_Error SD_EnableWideBusOperation(Uint32 WideMode);
//SD_Error SD_SetDeviceMode(Uint32 Mode);
//SD_Error SD_SelectDeselect(Uint32 addr);
SD_Error SD_ReadBlock(Uint8 *readbuff, Uint32 ReadAddr, Uint16 BlockSize);
SD_Error SD_ReadMultiBlocks(Uint8 *readbuff, Uint32 ReadAddr, Uint16 BlockSize, Uint32 NumberOfBlocks);
SD_Error SD_WriteBlock(Uint8 *writebuff, Uint32 WriteAddr, Uint16 BlockSize);
SD_Error SD_WriteMultiBlocks(Uint8 *writebuff, Uint32 WriteAddr, Uint16 BlockSize, Uint32 NumberOfBlocks);
//SDTransferState SD_GetTransferState(void);
//SD_Error SD_StopTransfer(void);
//SD_Error SD_Erase(Uint32 startaddr, Uint32 endaddr);
//SD_Error SD_SendStatus(Uint32 *pcardstatus);
//SD_Error SD_SendSDStatus(Uint32 *psdstatus);
//SD_Error SD_ProcessIRQSrc(void);

#ifdef __cplusplus
}
#endif

#endif /* __SDIO_SD_H */


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

