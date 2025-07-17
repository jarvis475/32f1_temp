#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
}

//按键处理函数
u8 KEY1_Scan(void)
{	 
	if(K1==0)
	{
		delay_ms(20);
		if(K1==0)
		{
			return 1;
		}
	}
 	return 0;// 无按键按下
}

u8 KEY2_Scan(void)
{	 
	if(K2==0)
	{
		delay_ms(20);
		if(K2==0)
		{
			return 1;
		}
	}
 	return 0;// 无按键按下
}
u8 KEY3_Scan(void)
{	 
	if(K3==0)
	{
		delay_ms(20);
		if(K3==0)
		{
			return 1;
		}
	}
 	return 0;// 无按键按下
}

u8 KEY4_Scan(void)
{	 
	if(K4==0)
	{
		delay_ms(20);
		if(K4==0)
		{
			return 1;
		}
	}
 	return 0;// 无按键按下
}