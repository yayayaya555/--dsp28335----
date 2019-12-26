
#define SPCR10_VAL     0x0000
#define SPCR20_VAL     0x0220
//2 words per frame
#define RCR10_VAL      0x0140
#define RCR20_VAL      0x04
//2 words per frame
#define XCR10_VAL      0x0140
#define XCR20_VAL      0x04
#define PCR0_VAL       0x01

#define   VOL1     0x81
#define   VOL2     0x82

#define   L_LINE_VOLUME        0x00
#define   R_LINE_VOLUME        0x01
#define   L_HEADPHONE_VOLUME   0x02
#define   R_HEADPHONE_VOLUME   0x03
#define   A_AUDIO_PATH         0x04
#define   D_AUDIO_PATH         0x05
#define   POWER_CON            0x06
#define   D_AUDIO_INTERFACE    0x07
#define   SAMPLE_RATE          0x08
#define   D_INTERFACE_ACT      0x09
#define   RESET                0x0f



#define	  LedReg	(*((volatile  Uint16 *)0x41FF))
//#define   SysReg    (*((volatile  Uint16 *)0x42FF))  
#define   KeyReg    (*((volatile  Uint16 *)0x44FF))

/*#define	 SetAICCS		 0x40  
#define  ClrAICCS		 0xBF 	
#define  SetSIDIN		 0x20  
#define	 ClrSIDIN		 0xDF  
#define  SetSCLK		 0x10  
#define  ClrSCLK		 0xEF  
*/

extern	void	delay(Uint32	k);
extern	void	InitAic23(void);
extern	void	WriteAic23(Uint16	addr,	Uint16	dat);
interrupt	void	ISRMcbspSend(void);

//==============================END ===============================

