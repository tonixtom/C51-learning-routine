#include"reg51.h"
#include"XPT2046.h"
#include"lcd.h"


//--����ȫ�ֱ���--//
void Delay10ms(unsigned int c);   //��� 0us
unsigned char DisplayData[8];		//�������Ҫ��ʾ��8λ����ֵ
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
			temp = Read_AD_Data(0x94);		//   AIN0 ��λ��		  ͨ����ַ	001
	//	temp = Read_AD_Data(0xD4);		//   AIN1 ��������		ͨ����ַ	101
	//	temp = Read_AD_Data(0xA4);		//   AIN2 ��������		ͨ����ַ	010
	//	temp = Read_AD_Data(0xE4);		//   AIN3 �ⲿ����		ͨ����ַ	110
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
* ������         : LcdDisplay()
* ��������		   : ��ʾ����
* ����           : ��
* ���         	 : ��
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
* �� �� ��         : Delay10ms
* ��������		   : ��ʱ��������ʱ10ms
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Delay10ms(unsigned int c)   //��� 0us
{
    unsigned char a, b;

	//--c�Ѿ��ڴ��ݹ�����ʱ���Ѿ���ֵ�ˣ�������for����һ��Ͳ��ø�ֵ��--//
    for (;c>0;c--)
	{
		for (b=38;b>0;b--)
		{
			for (a=130;a>0;a--);
		}          
	}       
}