#include "led.h"   
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);	 	//使能PA与PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 				//LED0-->PA8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 		//推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 					//根据设定参数初始化GPIOA8
 GPIO_SetBits(GPIOA,GPIO_Pin_8);						 							//PB1 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 				//LED1-->PD2 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 		//推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					 					//根据设定参数初始化GPIOD2
 GPIO_SetBits(GPIOD,GPIO_Pin_2);						 							//PB1 输出高
}
 
