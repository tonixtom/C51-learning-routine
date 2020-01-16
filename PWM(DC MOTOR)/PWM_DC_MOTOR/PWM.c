#include <reg52.h>


sbit PWM=P1^0;

unsigned char timer1; 

void Time1Config();

void main(void)
{
	Time1Config();
	while(1)
	{ 
		if(timer1>100)  //PWM周期为100*0.5ms
		{
			timer1=0;
		}
		if(timer1 < 50)	//改变30这个值可以改变直流电机的速度
		{
			PWM=1;
		}
		else
		{
			PWM=1;
		}
	}
	

 }

/*******************************************************************************
* 函 数 名       : Time1Config
* 函数功能		 : 设置定时器
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/

void Time1Config()
{
	TMOD|= 0x10;   //设置定时计数器工作方式1为定时器

	//--定时器赋初始值，12MHZ下定时0.5ms--//  
	TH1 = 0xFE; 
	TL1 = 0x0C;

	
	ET1 = 1; 	 //开启定时器1中断
	EA = 1;
	TR1 = 1;	 //开启定时器	
}

/*******************************************************************************
* 函 数 名       : Time1
* 函数功能		 : 定时器1的中断函数
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/

void Time1(void) interrupt 3    //3 为定时器1的中断号  1 定时器0的中断号 0 外部中断1 2 外部中断2  4 串口中断
{
	TH1 = 0xFE;  //重新赋初值
	TL1 = 0x0C;
	timer1++;    
}