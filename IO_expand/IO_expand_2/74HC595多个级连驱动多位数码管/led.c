#include <reg51.h> 
#include <intrins.h>
#define  NOP() _nop_()  /* �����ָ�� */

/*
//������  (�����Ǳ�׼��)
unsigned char code LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};

*/

//������������д�ģ�����׼��
unsigned char code LED_0F[] = 
{
/*0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F,-,*/
    0x82,0xFA,0x46,0x52,0x3A,0x13,0x03,0xDA,0x02,0x12,0x0A,0x23,0x87,0x62,0x07,0x0F,0x7F,
};

// ����ԭ�ζ���
#define uchar unsigned char
	

void OUT_595(void);
void WR_595(unsigned char SendVal);
void display_num(void);
void disp_init();
uchar out_calc(uchar xian);


unsigned char code LED_0F[];		// LED��ģ��
uchar second,dp_num=0;

sbit MOSIO = P1^2;				//������������
sbit R_CLK  = P1^0;				//ʱ�������źš�����������Ч
sbit S_CLK = P1^1;				//�����źš���������������Ч

//-----------------------------------------------------------------------------
// ȫ�ֱ���
uchar LED[8];	//����LED��8λ��ʾ����

uchar temp; 

//*****************************************************************************
// ������
//
void main (void) 
{
	TMOD=0X01; //T0������ʽ1
	TH0=(65536-10000)/256;
	TL0=(65536-10000)%256;	 //10�����ж�һ��
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
	

	WR_595(out_calc(0));			 //����8λ
	WR_595(out_calc(1));			 //����8λ
	WR_595(out_calc(2));			 //����8λ
	WR_595(out_calc(3));			 //����8λ
	WR_595(out_calc(4));			 //����8λ
	WR_595(out_calc(5));			 //����8λ
	WR_595(out_calc(6));			 //����8λ
	WR_595(out_calc(7));			 //����8λ
	
	OUT_595();			 //���沢���

}

uchar out_calc(uchar xian)
{
	unsigned char code *led_table;          // ���ָ��
	led_table = LED_0F + LED[xian];
	temp = *led_table;
	return temp;
}


void WR_595(unsigned char SendVal)
{  
  unsigned char i;
		
  for(i=0;i<8;i++) 
   {
	if((SendVal<<i)&0x80) MOSIO=1; //set dataline high  0X80  ���λ��SendVal���Ƶ����λ �����߼�����
	else MOSIO=0;				   // ���Ϊ�� MOSIO = 1  
 
	S_CLK=1;  //�����ط�����λ
	NOP();	 //������ʱ����һ����ȵ������ź�
	NOP();	 //������ʱ
	S_CLK=0;
		
   }

}



/********************************************************/
/*                                                      */
/*����λ�Ĵ����ڵ��������浽����Ĵ�������ʾ            */
/*                                                      */
/********************************************************/
 void OUT_595(void)
{
	R_CLK=0; //set dataline low
	NOP();  //������ʱ
	NOP();  //������ʱ
	R_CLK=1; 	 //�����ؽ������͵����������
	NOP();  //������ʱ
	NOP();  //������ʱ
	R_CLK=0;
}


