#include<reg51.h>
#include"st7565.h"

//---声明一个全局变量---//
void Delay10ms(unsigned int c);

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void main()
{

	Lcd12864_Init();
	Lcd12864_ClearScreen();
/*		
	while (1)
	{
		Lcd12864_Write16CnCHAR(0, 0, "司公限有技科中普");
		Delay10ms(100);
		Lcd12864_Write16CnCHAR(0, 2, "司公限有技科中普");
		Delay10ms(100);
		Lcd12864_Write16CnCHAR(0, 4, "司公限有技科中普");
		Delay10ms(100);
		Lcd12864_Write16CnCHAR(0, 6, "司公限有技科中普");
		Delay10ms(100);
	}
	*/

}

/*******************************************************************************
* 函 数 名         : Delay10ms
* 函数功能		   : 延时函数，延时10ms
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Delay10ms(unsigned int c)   //误差 0us
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}
