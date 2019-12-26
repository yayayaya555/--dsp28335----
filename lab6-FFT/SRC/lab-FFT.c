#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include  <math.h>

 
#define pi 3.141593 // float小数点后6位
#define NL 256  // NL为合成信号点数，与N的值必须是一致的，即NL=N
    int N=NL;   //FFT点数
float Input[NL];//输入的信号序列
/*
float h[33] = {
   0.000744808099883,0.0008898861356028,-0.002727390076489, 0.002920995444386,
  0.0009645511494193,-0.008002287495031,  0.01133584612049,-0.002751488761016,
   -0.01688113961025,   0.0316509088309, -0.01948352023097, -0.02634617068536,
    0.07974565309008, -0.08470853564896, -0.03245044438095,   0.5650983280183,
     0.5650983280183, -0.03245044438095, -0.08470853564896,  0.07974565309008,
   -0.02634617068536, -0.01948352023097,   0.0316509088309, -0.01688113961025,
  -0.002751488761016,  0.01133584612049,-0.008002287495031,0.0009645511494193,
   0.002920995444386,-0.002727390076489,0.0008898861356028, 0.000744808099883
}; 

float h[32]=
{
  
         0  , -0.00009  ,  0.00042  ,  0.00108  , -0.00224  , -0.00413  ,  0.00704  ,  0.01135,



   -0.01756  , -0.02634  ,  0.03871  ,  0.05650  , -0.08349  , -0.12957  ,  0.23113  ,  0.71720,


    0.71720   , 0.23113  , -0.12957  , -0.08349  ,  0.05650   , 0.03871  , -0.02634  , -0.01756,

  

    0.01135   , 0.00704  , -0.00413  , -0.00224  ,  0.00108   , 0.00042  , -0.00009    ,     0

};  */

//Uint16  SampleTable[NL];
struct Complex		// 定义复数结构体
{
   float real,imag;
};
struct Complex Wn;//定义旋转因子
struct Complex Vn;//每一级第一个旋转因子虚部为0，实部为1
struct Complex T;//存放旋转因子与X(k+B)的乘积

//float Realin[NL]={0};// 采样输入的实数
float output[NL]={0};// 输出的FFT幅值（复数的模）
struct Complex Sample[NL];// 采样输入的实数转化为复数

struct Complex MUL(struct Complex a,struct Complex b)//定义复乘
{
   struct Complex c;
   c.real=a.real*b.real-a.imag*b.imag;
   c.imag=a.real*b.imag+a.imag*b.real;
   return(c);
}

void MYFFT(struct Complex *xin,int N)//输入为复数指针*xin，做N点FFT
{
   int L=0; // 级间运算层
   int J=0; // 级内运算层
   int K=0,KB=0; // 蝶形运算层
   int M=1,Nn=0;// N=2^M
   float B=0; // 蝶形运算两输入数据间隔
   /* 以下是为倒序新建的局部变量*/
   int LH=0,J2=0,N1=0,I,K2=0;
   struct Complex T;
   /*以下是倒序*/
   LH=N/2; // LH=N/2
   J2=LH;
   N1=N-2;
   for(I=1;I<=N1;I++)
    {
     if(I<J2)
	 {
       T=xin[I];
       xin[I]=xin[J2];
       xin[J2]=T;
	 }
	 K2=LH;
	 while(J2>=K2)
	  {
        J2-=K2;
        K2=K2/2;// K2=K2/2
	  }
	  J2+=K2;
    }	    
   /* 以下为计算出M */
   Nn=N;
   while(Nn!=2)// 计算出N的以2为底数的幂M
   {
     M++;
	 Nn=Nn/2;
   }

   /* 蝶形运算 */
   for(L=1;L<=M;L++)  // 级间
	{
	  B=pow(2,(L-1));
      Vn.real=1;
	  Vn.imag=0;
      Wn.real=cos(pi/B);
      Wn.imag=-sin(pi/B);
	  for(J=0;J<B;J++)   // 级内
	   {        
		 for(K=J;K<N;K+=2*B)  // 蝶形因子运算
		  {
            KB=K+B;
            T=MUL(xin[KB],Vn);
            xin[KB].real=xin[K].real-T.real;//原址运算，计算结果存放在原来的数组中
            xin[KB].imag=xin[K].imag-T.imag;
             xin[K].real=xin[K].real+T.real;
             xin[K].imag=xin[K].imag+T.imag;      
		  }
		  Vn=MUL(Wn,Vn);// 旋转因子做复乘相当于指数相加，得到的结果
		  // 和J*2^（M-L）是一样的，因为在蝶形因子运算
		 // 层中M与L都是不变的，唯一变x化的是级内的J
		 // 而且J是以1为步长的，如J*W等效于W+W+W...J个W相加
		}
	 }
}


/*
void FilterDC(struct Complex *ADC,int N)//去除数据中的直流成分，否则直流分量将很大
{
   int i;
   float sum=0;
   for(i=0;i<N;i++)
    { sum+=ADC[i].real;}
   sum=sum/N;
   for(i=0;i<N;i++)
    { ADC[i].real-=sum;}
}*/

/********************************
功能：计算复数的模
形参：*Sample指向需要取模的复数结构体
      N为取模点数
	  *output存放取模后数值的数组
*********************************/
void ModelComplex(struct Complex *Sample,int N,float *output)
{
   int i;
   for(i=0;i<N;i++)
    {
     output[i]=sqrt(Sample[i].real*Sample[i].real+Sample[i].imag*Sample[i].imag)*2/N;
	}
}

void main(void)
{
   Uint16 i=0;
   InitSysCtrl();
 //  InitXintf16Gpio();
 // InitAdc();
   
   DINT;
   InitPieCtrl();
   IER = 0x0000;
   IFR = 0x0000;
    for(i=0;i<NL;i++) //产生一个三次谐波叠加而成的方波
     { 
      Input[i]=sin(2*pi*5*i/(NL-1))+sin(2*pi*i*5*3/(NL-1))/3+sin(2*pi*i*5*5/(NL-1))/5;
	 }
	 for(i=0;i<NL;i++)   //输入实数信号转换为复数
	  {
         Sample[i].real=Input[i];
		//  Sample[i].real=h[i];
		 Sample[i].imag=0;
	  }
	 MYFFT(Sample,NL);                //FFT
     ModelComplex(Sample,NL,output);  //求模
	while(1)
   {       
   //  FilterDC(Sample,NL);
   }
}


//===========================================================================
// No more.
//===========================================================================
