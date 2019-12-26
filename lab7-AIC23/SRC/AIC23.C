#include	"DSP2833X_Device.h"
#include 	"DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ClrAICCS       GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;DELAY_US(1);
#define SetAICCS       GpioDataRegs.GPASET.bit.GPIO13 = 1;DELAY_US(1); 
#define  SetSIDIN	   GpioDataRegs.GPASET.bit.GPIO12 = 1;DELAY_US(1);  
#define	 ClrSIDIN	   GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;DELAY_US(1);
#define  SetSCLK	   GpioDataRegs.GPBSET.bit.GPIO61 = 1;DELAY_US(1); 
#define  ClrSCLK	   GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;DELAY_US(1);  

extern	Uint16	  volume;
extern	Uint16	  tAicRegs;


void 	WriteAic23(Uint16  addr,Uint16  dat)
		{
    		Uint16	i,Temp;
			Temp = addr<<9;
			dat = dat | Temp;
    		//CS=0;
    		ClrAICCS;   		
			DELAY_US(200);
    		for(i=0;i<16;i++)
    			{
      				//SCLK=0;      				
		    		ClrSCLK;
					DELAY_US(200);
     				Temp = dat<<i;
      				Temp = Temp & 0x8000;	
					if (Temp){
						  SetSIDIN;
						}else{
      					  ClrSIDIN; 	
      					}          					     
      				DELAY_US(100);
      				SetSCLK;   //SCLK=1;
      				DELAY_US(100);
      			}
    		//SCLK=0;
    		//ClrSCLK;
			DELAY_US(200);
    		//CS=1;
    		SetAICCS;
			DELAY_US(1000);
}

void 	InitAic23()
		{ 
   			WriteAic23(RESET,0);
   			WriteAic23(D_INTERFACE_ACT,0x001);
   			WriteAic23(POWER_CON,0);
   			WriteAic23(SAMPLE_RATE,0x023);  //44.1k
//	   		WriteAic23(SAMPLE_RATE,0x062);  //22.05k
//   		write_AIC23(SAMPLE_RATE,0x02e);    //8.021k
    
   			WriteAic23(L_LINE_VOLUME,0x0117);
   			WriteAic23(R_LINE_VOLUME,0x0117);
   
   			volume=108;
   			WriteAic23(L_HEADPHONE_VOLUME,0x0180+volume);   
   			WriteAic23(R_HEADPHONE_VOLUME,0x0180+volume);   
   
//   		write_AIC23(A_AUDIO_PATH,0x009);  //bypass DAC OFF
//   		write_AIC23(A_AUDIO_PATH,0x014);   //MIC ADC DAC ON  0DB
//     		write_AIC23(A_AUDIO_PATH,0x1fc);   //bypass MIC ADC DAC ON 0DB sidetone 
     		WriteAic23(A_AUDIO_PATH,0x07d);   //bypass MIC ADC DAC ON 20DB sidetone(-6db)
//   		write_AIC23(A_AUDIO_PATH,0x011);   //LINE ADC DAC ON
   
   			WriteAic23(D_AUDIO_PATH,0x04);
   
   			WriteAic23(D_AUDIO_INTERFACE,0x043);   //master  dsp mode  16BIT
		}
		

void delay(Uint32 k)
{
   while(k--);
}
