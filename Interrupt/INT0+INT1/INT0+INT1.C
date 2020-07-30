/*******************************************************************************
*  ����:                  �������������ʾ�ⲿ�жϼ���                         *
*																			   *
*  ���ӷ��������ս���ͼ				                                     	   *
********************************************************************************
*                         	       										       *
* ��ѧԱ�������������̣��õ�Ƭ����ֱ�ӿ�������ܺ��ⲿ�ж�ʹ��                 *
********************************************************************************/


#include < reg51.h >
#include <intrins.h>

sbit LS138A=P2^2;  
sbit LS138B=P2^3;
sbit LS138C=P2^4; 

unsigned int LedNumVal_1,LedNumVal_2,LedOut[8];

//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
unsigned char code Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40}; 


void delay(unsigned int i)
{
    char j;
    for(i; i > 0; i--)
        for(j = 200; j > 0; j--);
}


void main(void)
{  unsigned char i;

   P0=0xff;
   P1=0xff;
   P2=0xff;


// IT0=0;       //�͵�ƽ����
   IT0=1;       //�½��ش���
   EX0=1;


   
// IT1=0;       //�͵�ƽ����
   IT1=1;       //�½��ش���
   EX1=1;
   EA=1;


   while(1)
   {    
     LedOut[0]=Disp_Tab[LedNumVal_1%10000/1000];
     LedOut[1]=Disp_Tab[LedNumVal_1%1000/100]|0x80;	  //0x7fС����
     LedOut[2]=Disp_Tab[LedNumVal_1%100/10];
     LedOut[3]=Disp_Tab[LedNumVal_1%10];

	 LedOut[4]=Disp_Tab[LedNumVal_2%10000/1000];
     LedOut[5]=Disp_Tab[LedNumVal_2%1000/100];
     LedOut[6]=Disp_Tab[LedNumVal_2%100/10];
     LedOut[7]=Disp_Tab[LedNumVal_2%10];


	 for( i=0; i<8; i++) 
	 {	 P0 = LedOut[i];
			
	  switch(i)					  
	     {	    
			case 0:LS138A=0; LS138B=0; LS138C=0; break;         
	        case 1:LS138A=1; LS138B=0; LS138C=0; break;             	
	        case 2:LS138A=0; LS138B=1; LS138C=0; break; 
	        case 3:LS138A=1; LS138B=1; LS138C=0; break; 
			case 4:LS138A=0; LS138B=0; LS138C=1; break;
			case 5:LS138A=1; LS138B=0; LS138C=1; break;
			case 6:LS138A=0; LS138B=1; LS138C=1; break;
			case 7:LS138A=1; LS138B=1; LS138C=1; break;
			
	     }

		delay(150);
	 }
 

   }

}



/********************************************************
* INT0�жϺ���                                          *
********************************************************/
void  counter0(void) interrupt 0  using 1
{
  
   EX0=0;  
   LedNumVal_1++;
   EX0=1;
}
/********************************************************
* INT1�жϺ���                                          *
********************************************************/
void  counter1(void) interrupt 2 using 2
{
   
   EX1=0;
   LedNumVal_2++;
   EX1=1;
}
/********************************************************/

