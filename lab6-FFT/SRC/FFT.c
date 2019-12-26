#include "FFT.h"

 
//#define NL 256  // NL为合成信号点数，与N的值必须是一致的，即NL=N
 //   int N=NL;   //FFT点数
//float Input[NL];//输入的信号序列

//Uint16  SampleTable[NL];

static struct Complex Wn;//定义旋转因子
static struct Complex Vn;//每一级第一个旋转因子虚部为0，实部为1
//static struct Complex T;//存放旋转因子与X(k+B)的乘积

//float Realin[NL]={0};// 采样输入的实数
//float output[NL]={0};// 输出的FFT幅值（复数的模）

static struct Complex MUL(struct Complex a,struct Complex b)//定义复乘
{
   struct Complex c;
   c.real=a.real*b.real-a.imag*b.imag;
   c.imag=a.real*b.imag+a.imag*b.real;
   return(c);
}

static void FFT(struct Complex *xin,int N)//输入为复数指针*xin，做N点FFT
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
static void ModelComplex(struct Complex *Sample,int N,float *output)
{
   int i;
   for(i=0;i<N;i++)
    {
     output[i]=(int)sqrt(Sample[i].real*Sample[i].real+Sample[i].imag*Sample[i].imag)*2/N;
	}
}
 
void fft_IO(float *IO_IN, int IN_N, float *IO_OUT)
{
   int i;
   int n;
   struct Complex in[Buff_Length];// 采样输入的实数转化为复数
   n=IN_N;
     for(i=0;i<n;i++)   //输入实数信号转换为复数
	  {
         in[i].real=IO_IN[i];
		 in[i].imag=0;
	  }
   FFT(in,n);
   ModelComplex(in,n,IO_OUT);  //求模 
}


//===========================================================================
// No more.
//===========================================================================
