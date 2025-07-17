#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTB时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;//K3,K4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB10,11

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}
//按键处理函数
u8 KEY2_Scan(void)
{	 
	if(WK_UP==1)
	{
		return 1;
	}
 	return 0;// 无按键按下
}

//按键处理函数
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

//按键处理函数
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
