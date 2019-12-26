#include"DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

typedef enum {
       ERR = 0,
	   OK
}RESULT;

typedef struct {   
   Uint16 HumiH:8;
   Uint16 HumiL:8;
   Uint16 TempH:8;
   Uint16 TempL:8;
   RESULT flag;
}Obj_Sensor;
#define   UNDEF   0xFF
#define	  DATA 	  GpioDataRegs.GPBDAT.bit.GPIO50 
#define   Data_O  EALLOW;                             \
                  GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1; \
				  EDIS;
#define   Data_I  EALLOW;                             \
                  GpioCtrlRegs.GPBDIR.bit.GPIO50 = 0; \
				  EDIS; 
#define	  EN 	GpioDataRegs.GPBDAT.bit.GPIO33
#define	  RW 	GpioDataRegs.GPBDAT.bit.GPIO32
#define	  RS 	GpioDataRegs.GPADAT.bit.GPIO20 
Uint16 Temp[]={0,0,0,0,0};

void delay(Uint16 t)
{
   Uint16 i;
   while(t--)
    {
      for(i=0;i<125;i++);
    }
}

void LCD_DATA(uchar d){
   Uint32 i=0;
   i = GpioDataRegs.GPADAT.all;
   i |= (d<<6)&0x3FC0; 
   i = (~((d<<6)&0x3FC0))|(~i);
   GpioDataRegs.GPADAT.all = ~i;
} 


void Write_order(Uint16 order)
{
   RS=0;delay(1);
   RW=0;delay(1);
   EN=1;delay(1);
   LCD_DATA(order);
   delay(10);
   EN=0;delay(1);
}

void Write_data(Uint16 data)
{
   RS=1;delay(1);
   RW=0;delay(1);
   EN=1;delay(1);
   LCD_DATA(data);
   delay(10);
   EN=0;delay(1);
}
void LCDInit(void)
{
  delay(500);
  Write_order(0x30);// 功能设定：基本指令动作
  delay(5);
  Write_order(0x0c);//显示状态：开
  delay(5);
  Write_order(0x01);//清屏
  delay(6);
  Write_order(0x02);//地址归位：AC=0x00
  delay(4);
} 
void ConfigLCD(void)
{
    EALLOW;
	GpioCtrlRegs.GPAMUX1.all &= 0xc03f; 
	GpioCtrlRegs.GPADIR.all |= 0x00003FC0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1; 
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1; 
    GpioCtrlRegs.GPAMUX2.bit.GPIO20= 0;
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 1; 
    EDIS;
}

void display(char *hz)
{
   while(*hz!='\0')
    {
       Write_data(*hz);
       hz++;
       delay(2);
    }
} 

//函数功能：显示十进制数据（最大9999 9999 9）
//输入参数：   v：要显示的十进制数据
//           add: 显示起始地址
//           Len：十进制数据长度（最长9位）
//输出参数：无
void DisDec(Uint32 v, Uint16 add, unsigned char Len){
  Uint32 GUI_Pow10[] = {
  1 , 10, 100, 1000, 10000,
  100000, 1000000, 10000000, 100000000, 1000000000 
  }; 
  char c[10], g;
  unsigned char s=0;
  if (Len > 9) {
    Len = 9;
  }
  if(v == 0) Len = 1;
  while(Len--){
    //d = GUI_Pow10[Len];
    g = (char) (v / GUI_Pow10[Len]);
    v -= g * GUI_Pow10[Len];
    c[s++] = g + '0';     
  }
  c[s] = '\0';
  g=0;
  while(g < s-1){
    if(c[g] == '0') c[g]=' ';
	else break;
	g++;
  }
    if(add != UNDEF) Write_order(add);
    delay(5);
    display(c);
}    

void ConfigIO(void)
{
   EALLOW;
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;
   // GpioCtrlRegs.GPBDIR.bit.GPIO50 = 0; 
    EDIS;
}

void Read_Temp(Uint16 * pot){   
   Uint16 a=0,b,x;
   Uint16 Time_out=0;
   for(;a<5;a++){   //0
     for(b=0;b<8;b++){  //1
       while(!DATA);  //等待拉高
	   DELAY_US(30);  //waiting 30us
	   x = 0;
	   if(DATA) x = 1;
	   Time_out = 2;
	   while(DATA && Time_out++); //数据变为0或者超时可以结束该while
	   if(Time_out == 1) break;  //已经超时 跳出循环
	   (* pot) <<= 1;
	   if(x) (* pot)++;
	 }  //1
	 pot++;
   }  //0
}

Obj_Sensor GET_Dev(void){
   Obj_Sensor Obj_x;
   Uint16 u=0, sum=0;
   Data_O;      //配置为输出
   DATA = 0;
   DELAY_US(20000);  //拉低延时18ms
   DATA = 1;       
   DELAY_US(40);     //拉高延时20-40us
   Data_I;      //配置为输入
   Obj_x.flag = ERR;
   if(DATA == 0){  //DHT11发送响应拉低80us
      while(!DATA);  //等待拉高
	  while(DATA);   //等待拉低
	  Read_Temp(Temp);
	  for(;u<4;u++)
        sum += Temp[u];
	  Obj_x.HumiH = Temp[0];
	  Obj_x.HumiL = Temp[1];
	  Obj_x.TempH = Temp[2];
	  Obj_x.TempL = Temp[3];
	  if(sum != Temp[4]) //校验和
	     Obj_x.flag = ERR;
	  else
	     Obj_x.flag = OK;
   }
   return Obj_x;
}

void main(void)
{    
    Obj_Sensor o;
    InitSysCtrl();
  //  InitXintf();
  //  InitXintf16Gpio();
    DINT;
    InitPieCtrl();
    IER=0x0000;
    IFR=0x0000;
	ConfigLCD();
	RS=0;
    delay(5);
    RW=0;
    delay(5);
    EN=0;
    LCDInit();
    delay(5);
    Write_order(0x01);
    delay(50);
    Write_order(0x80);
    delay(5);
    display("湿度      %RH");
    Write_order(0x90);
    delay(5);
    display("温度      ℃");  
    ConfigIO();    
    while(1){
      do{
         o = GET_Dev();
         DELAY_US(1000000);
	  }while( o.flag != OK);
	  Write_order(0x82);
      delay(5);
      display(":");
      DisDec(o.HumiH, UNDEF, 2);
	  display(".");
	  DisDec(o.HumiL, UNDEF, 1);
	  Write_order(0x92);
      delay(5);
      display(":");
      DisDec(o.TempH, UNDEF, 2);
	  display(".");
	  DisDec(o.TempL, UNDEF, 1); 
	}
}

//
//===========================================================================
// No more.
//===========================================================================
