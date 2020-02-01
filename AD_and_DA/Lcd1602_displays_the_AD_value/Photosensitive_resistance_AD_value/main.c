#include"reg51.h"
#include"XPT2046.h"
#include"lcd.h"


//--声明全局变量--//
void Delay10ms(unsigned int c);   //误差 0us
unsigned char DisplayData[8];		//用来存放要显示的8位数的值
void LcdDisplay();


void main(void)
{
	uint temp,count;
	LcdInit();
  while(1)
	{
	   if(count==10)
	  {
	  	count=0; 
			temp = Read_AD_Data(0x94);		//   AIN0 电位器		  通道地址	001
	//	temp = Read_AD_Data(0xD4);		//   AIN1 热敏电阻		通道地址	101
	//	temp = Read_AD_Data(0xA4);		//   AIN2 光敏电阻		通道地址	010
	//	temp = Read_AD_Data(0xE4);		//   AIN3 外部输入		通道地址	110
			}
	  count++;
	  DisplayData[0]=0;
	  DisplayData[1]=0;
	  DisplayData[2]=0;
	  DisplayData[3]=0;

	  DisplayData[4]=temp%10000/1000;
	  DisplayData[5]=temp%1000/100;
	  DisplayData[6]=temp%100/10;
	  DisplayData[7]=temp%10/1;
		LcdDisplay();	
		//Delay10ms(50);
	}
}


/*******************************************************************************
* 函数名         : LcdDisplay()
* 函数功能		   : 显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void LcdDisplay()
{
	uchar i;
	LcdWriteCom(0x80);
	for(i=0; i<8; i++)
		{		
			//LcdWriteData(PuZh[i]);	
			LcdWriteData('0'+DisplayData[i]);				
		}		 
}

/*******************************************************************************
* 函 数 名         : Delay10ms
* 函数功能		   : 延时函数，延时10ms
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Delay10ms(unsigned int c)   //误差 0us
{
    unsigned char a, b;

	//--c已经在传递过来的时候已经赋值了，所以在for语句第一句就不用赋值了--//
    for (;c>0;c--)
	{
		for (b=38;b>0;b--)
		{
			for (a=130;a>0;a--);
		}          
	}       
}