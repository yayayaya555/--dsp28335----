
void	SendData(Uint16 data);
Uint16	BlockErase(Uint16	BlockNum);
Uint16	SectorErase(Uint16	SectorNum);
Uint16	BlockErase(Uint16	BlockNum);
Uint16	ChipErase(void);
Uint16	FlashWrite(Uint32	RamStart, Uint32   RomStart,  Uint16	Length);
void	FlashRead(Uint32	RamStart, Uint32  RomStart,	Uint16	Length);
void	InitExRam(Uint16	Start);
void	ClearExRam(Uint16	Start);
void	RamRead(Uint16	Start);








