#include <reg51.h> 
#include <intrins.h>
#define  NOP() _nop_()  /* 定义空指令 */

/*
//共阳极  (这里是标准的)
unsigned char code LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};

*/

//共阳极（单独写的，不标准）
unsigned char code LED_0F[] = 
{
/*0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F,-,*/
    0x82,0xFA,0x46,0x52,0x3A,0x13,0x03,0xDA,0x02,0x12,0x0A,0x23,0x87,0x62,0x07,0x0F,0x7F,
};

// 函数原形定义
#define uchar unsigned char
	

void OUT_595(void);
void WR_595(unsigned char SendVal);
void display_num(void);
void disp_init();
uchar out_calc(uchar xian);


unsigned char code LED_0F[];		// LED字模表
uchar second,dp_num=0;

sbit MOSIO = P1^2;				//串行数据输入
sbit R_CLK  = P1^0;				//时钟脉冲信号——上升沿有效
sbit S_CLK = P1^1;				//打入信号————上升沿有效

//-----------------------------------------------------------------------------
// 全局变量
uchar LED[8];	//用于LED的8位显示缓存

uchar temp; 

//*****************************************************************************
// 主程序
//
void main (void) 
{
	TMOD=0X01; //T0工作方式1
	TH0=(65536-10000)/256;
	TL0=(65536-10000)%256;	 //10毫秒中断一次
	EA=1;
	ET0=1;
	TR0=1;
	
	disp_init();

	
	while(1)
	{
		;
	}
	

}


void T0_SEVR() interrupt 1
{
	int i;
	TH0=(65536-40000)/256;
	TL0=(65536-40000)%256;
	second++;
	if(second==20)
	{
		second=0;
		for(i=0;i<8;i++)
			LED[i]=dp_num%17;
		dp_num++;
		if(dp_num>100)
			dp_num=0;
	}

	display_num();

}

void disp_init()
{
	LED[0]=1;
	LED[1]=2;
	LED[2]=3;
	LED[3]=4;
	LED[4]=13;
	LED[5]=12;
	LED[6]=14;
	LED[7]=15;

	S_CLK = 0;
	R_CLK = 1; 
}
void display_num(void)
{	
	

	WR_595(out_calc(0));			 //输入8位
	WR_595(out_calc(1));			 //输入8位
	WR_595(out_calc(2));			 //输入8位
	WR_595(out_calc(3));			 //输入8位
	WR_595(out_calc(4));			 //输入8位
	WR_595(out_calc(5));			 //输入8位
	WR_595(out_calc(6));			 //输入8位
	WR_595(out_calc(7));			 //输入8位
	
	OUT_595();			 //锁存并输出

}

uchar out_calc(uchar xian)
{
	unsigned char code *led_table;          // 查表指针
	led_table = LED_0F + LED[xian];
	temp = *led_table;
	return temp;
}


void WR_595(unsigned char SendVal)
{  
  unsigned char i;
		
  for(i=0;i<8;i++) 
   {
	if((SendVal<<i)&0x80) MOSIO=1; //set dataline high  0X80  最高位与SendVal左移的最高位 进行逻辑运算
	else MOSIO=0;				   // 如果为真 MOSIO = 1  
 
	S_CLK=1;  //上升沿发生移位
	NOP();	 //短暂延时产生一定宽度的脉冲信号
	NOP();	 //短暂延时
	S_CLK=0;
		
   }

}



/********************************************************/
/*                                                      */
/*将移位寄存器内的数据锁存到输出寄存器并显示            */
/*                                                      */
/********************************************************/
 void OUT_595(void)
{
	R_CLK=0; //set dataline low
	NOP();  //短暂延时
	NOP();  //短暂延时
	R_CLK=1; 	 //上升沿将数据送到输出锁存器
	NOP();  //短暂延时
	NOP();  //短暂延时
	R_CLK=0;
}


