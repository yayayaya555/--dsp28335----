#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h" 

#define a  3 //x(n)的序列长度
#define b  4 //h(n)的序列长度
#define c  a+b-1  //y(n)的序列长度 =a+b-1

//Uint16 Input[256];   
Uint16 x1[a]={3,2,1};   //卷积序列1
Uint16 h1[b]={4,3,2,1}; //卷积序列2
Uint16 y1[c];           //卷积输出序列
/*=============================================================
    功能：实现离散线性卷积
算法原理：对位相乘求和法实现卷积
形参：xn（*x所指向的数组长度）、hn（*h所指向的数组长度）为参与
     运算的两个卷积序列数组长度
     *x、*h为指向两个数组的指针
	 *y指向输出序列的数组
注意：输出序列长度为xn+hn-1；存放内容为输出数组的 0~(xn+hn-2)。
另外，该函数实现的无符号整型的卷积运算，如果要实现浮点型，需要
将形参的Uint16 hn,Uint16 *x,Uint16 *h,Uint16 *y的Uint16数据格式
改为float或者double型
==============================================================*/
void LinearConvolution(Uint16 xn,Uint16 hn,Uint16 *x,Uint16 *h,Uint16 *y)  
{
   Uint16 i,j,k,l;
   Uint16 yn;   //输出序列y的长度
   yn=xn+hn-1;
   for(i=0;i<yn;i++) y[i]=0;  //输出数组初始化
   k=yn-1;
   for(i=hn-1;i>0;i--)      //将*h作为被乘数
    {
       l=k;
       for(j=xn-1;j>0;j--)  //数组x[n]的1~(xn-1)与h[i]逐一相乘
	    {
           y[l]+=h[i]*x[j];
		   l--;
		}
	   y[l]+=x[0]*h[i];     
	   k--;
	}
	l=k;
   for(j=xn-1;j>0;j--)
	{
       y[l]+=h[0]*x[j];
	   l--;
    }
	y[l]+=x[0]*h[0];
}


void main(void)
{
  // Uint16 i;

   InitSysCtrl();

   InitXintf16Gpio();	//zq

   DINT;

   InitPieCtrl();


   IER = 0x0000;
   IFR = 0x0000;
   InitPieVectTable();
   LinearConvolution(a,b,x1,h1,y1);
   
 /*  for(i=0;i<256;i++) 
     { 
      Input[i]=200 * sin(2 * 3.14 * i / 255)+300+100 * cos(2 * 3.14 * 100* i / 255);
	   DELAY_US(10);
	 }*/

   

 while(1)
 {
     
 }

}


//===========================================================================
// No more.
//===========================================================================
