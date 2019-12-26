#include	"DSP2833X_Device.h"

// Definitions for the SST 39VF400A part
//#define 	SST_ID                   0x00BF         /* SST Manufacturer's ID code   */
//#define 	SST_39VF800A             0x2780         /* SST39VF800/SST39VF800A device code */
#define		TimeOutErr				 1
#define		VerifyErr				 2
#define		WriteOK					 0
#define		EraseErr				 3
#define		EraseOK					 0			
#define		SectorSize				 0x800
#define		BlockSize				 0x8000
unsigned  	int  *FlashStart = (unsigned  int *)0x100000;//flash的首地址
unsigned  	int  *ExRamStart = (unsigned  int *)0x180000;//sram的首地址

Uint16	SectorErase(Uint16	SectorNum)
		{
			Uint16	i,Data;
			Uint32	TimeOut;
			*(FlashStart + 0x5555) = 0xAAAA;
			*(FlashStart + 0x2AAA) = 0x5555;
			*(FlashStart + 0x5555) = 0x8080;
			*(FlashStart + 0x5555) = 0xAAAA;
			*(FlashStart + 0x2AAA) = 0x5555;
			*(FlashStart + SectorSize * SectorNum) = 0x3030;
			i = 0;
			TimeOut = 0;
			while(i<5)
				{
					Data = *(FlashStart +  SectorSize * (SectorNum + 1) -1);
					if	(Data == 0xFFFF)	i++;
					else	i=0;
					if ( ++TimeOut>0x1000000)	return (TimeOutErr);
				}
			for	(i=0;i<SectorSize;i++)	
				{
					Data = *(FlashStart + SectorSize * SectorNum +i);
					if (Data !=0xFFFF)	return (EraseErr);
				}
			return  (EraseOK);											
		}
		
Uint16	BlockErase(Uint16	BlockNum)
		{
			Uint16	i,Data;
			Uint32	TimeOut;		
			*(FlashStart + 0x5555) = 0xAAAA;
			*(FlashStart + 0x2AAA) = 0x5555;
			*(FlashStart + 0x5555) = 0x8080;
			*(FlashStart + 0x5555) = 0xAAAA;
			*(FlashStart + 0x2AAA) = 0x5555;
			*(FlashStart + BlockSize * BlockNum + 1) = 0x5050;
			i = 0;
			TimeOut = 0;
			while(i<5)
				{
					Data = *(FlashStart +  BlockSize * (BlockNum +1));
					if	(Data == 0xFFFF)	i++;
					else	i=0;
					if ( ++TimeOut>0x1000000)	return (TimeOutErr);
				}
			for	(i=0;i<SectorSize;i++)	
				{
					Data = *(FlashStart + BlockSize * BlockNum +i);
					if (Data !=0xFFFF)	return (EraseErr);
				}
			return  (EraseOK);											
					
		}
				
Uint16	ChipErase(void)
		{
			Uint16	Data;
			Uint32	TimeOut,i;				
			*(FlashStart + 0x5555) = 0xAAAA;
			*(FlashStart + 0x2AAA) = 0x5555;
			*(FlashStart + 0x5555) = 0x8080;
			*(FlashStart + 0x5555) = 0xAAAA;
			*(FlashStart + 0x2AAA) = 0x5555;
			*(FlashStart + 0x5555) = 0x1010;	
			i = 0;
			TimeOut = 0;
			while(i<5)
				{
					Data = *(FlashStart +  0x3FFFF);
					if	(Data == 0xFFFF)	i++;
					else	i=0;
					if ( ++TimeOut>0x1000000)	return (TimeOutErr);
				}
			for	(i=0;i<0x40000;i++)	
				{
					Data = *(FlashStart + i);
					if (Data !=0xFFFF)	return (EraseErr);
				}
			return  (EraseOK);											
											
		}
		

Uint16	FlashWrite(Uint32	RamStart, Uint32   RomStart,  Uint16	Length)
		{
			Uint32	i,TimeOut;
			Uint16	Data1,Data2,j;
			for	(i=0;i<Length;i++)
				{
					*(FlashStart + 0x5555) = 0x00AA;
					*(FlashStart + 0x2AAA) = 0x0055;
					*(FlashStart + 0x5555) = 0x00A0;
					*(FlashStart + RomStart + i) = *(ExRamStart + RamStart + i);
					TimeOut = 0;
					j=0;
					while(j<5)
						{
							Data1 = *(FlashStart + RomStart + i);


































































































































































































































































































































































































































































































































							Data2 = *(FlashStart + RomStart + i);							
							if	(Data1 == Data2)	j++;
							else	j=0;
							if ( ++TimeOut>0x1000000)	return (TimeOutErr);
								
						}						

				}
			for (i=0;i<Length;i++)
				{
					Data1 = *(FlashStart + RomStart +i);
					Data2 = *(ExRamStart + RamStart +i);
					if  (Data1 != Data2)	return (VerifyErr);
				}
			return  (WriteOK);				
		}

void	FlashRead(Uint32	RamStart, Uint32  RomStart,	Uint16	Length)
		{
			Uint32	i;
			Uint16	Temp;
			for	(i=0;i<Length;i++)
				{
					Temp =  *(FlashStart + RomStart +i);
					*(ExRamStart + RamStart +i) = Temp;
				}	
		}

void	InitExRam(Uint16	Start)
		{
			Uint16	i;
			for	(i=0;i<0xFFFF;i++)		*(ExRamStart + Start + i) = i;
		}
void	ClearExRam(Uint16	Start)
		{
			Uint16	i;
			for	(i=0;i<0xFFFF;i++)		*(ExRamStart + Start + i) = 0;
		}
void	RamRead(Uint16	Start)
		{
			Uint16	i;
			for	(i=0;i<0xFFFF;i++)		*(ExRamStart + Start + i) = *(ExRamStart +i);
		}							
//=========================================NO MORE==============================

