/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    20-September-2021
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2011 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "delay.h"
#include "led.h"
#include "oled.h"
#include "ds18b20.h"
#include "usart.h"
#include "key.h"
#include "timer.h"
#include "PidContoller.h"

u16 PWM_Duty;
short nowtem;
float tem2=25.0;
u8 t=0;					//PID标志符
/* Private functions ---------------------------------------------------------*/
void delay(u32 n)
{
	while(n--)
	{
		u32 i=10000;
		while(i--);
	}
}

void PIDPWM(void)
{
	nowtem=DS18B20_Get_Temp();
	User_PidPWMControl(tem2);     //PID
	TIM_SetCompare3(TIM4, PWM_Duty);		//PWM
	t=0;
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

int main(void)
{
	delay_init();
	OLED_Init();
	LED_Init();
	DS18B20_Init();
	KEY_Init();
	TIM3_Int_Init(9990,2600);
	TIM4_PWM_Init(999,17);
	uart1_init(115200);
	
  while (1)
  {
		LED0=0;				//验证代码是否运行
		if(t)
		{
			PIDPWM();
		}
		float tem0=DS18B20_Get_Temp() /10.0f;
		char tem1[10];
		sprintf(tem1, "%.1f", tem0);
		uart1_sent_tem(tem0,tem2);             	//发送到J.COM
		u8 a=0;       //OLED状态标志位
		if(KEY2_Scan())
		{
			a=1;
			delay_ms(200);
		}
		if(a==0)
		{
			OLED_ShowCHinese(20,0,0);
			OLED_ShowCHinese(35,0,1);
			OLED_ShowCHinese(50,0,2);
			OLED_ShowCHinese(65,0,3);
			OLED_ShowCHinese(80,0,4);
			OLED_ShowCHinese(95,0,5);						//显示标题
			
			OLED_ShowCHinese(0,2,6);
			OLED_ShowCHinese(15,2,7);
			OLED_ShowCHinese(30,2,0);
			OLED_ShowCHinese(45,2,1);
			OLED_ShowString(65,2,"=");
			OLED_ShowString(75,2,tem1);					//OLED显示实时温度
			
			char tem3[10];
			sprintf(tem3, "%.1f", tem2);
			OLED_ShowCHinese(0,4,8);
			OLED_ShowCHinese(15,4,9);
			OLED_ShowCHinese(30,4,0);
			OLED_ShowCHinese(45,4,1);
			OLED_ShowString(65,4,"=");
			OLED_ShowString(75,4,tem3);					//OLED显示设定温度
			
			char temp_str[10];
			OLED_ShowString(0,6,"PWM:");
      sprintf(temp_str, "%3d%%", PWM_Duty / 10);
      OLED_ShowString(30, 6, temp_str);			//显示PWM
		}
		if(a==1)
		{
			OLED_Clear();
			
			while(a==1)
			{
				OLED_ShowCHinese(20,1,10);
				OLED_ShowCHinese(35,1,11);
				OLED_ShowCHinese(50,1,12);
				OLED_ShowCHinese(75,1,13);
				OLED_ShowCHinese(90,1,14);
				OLED_ShowCHinese(105,1,15);						//显示姓名
					
				char tem3[10];
				sprintf(tem3, "%.1f", tem2);
				OLED_ShowCHinese(0,5,8);
				OLED_ShowCHinese(15,5,9);
				OLED_ShowCHinese(30,5,0);
				OLED_ShowCHinese(45,5,1);
				OLED_ShowString(65,5,"=");
				OLED_ShowString(75,5,tem3);					//OLED显示设定温度
				
				if(KEY3_Scan())
					tem2=tem2+1;
				if(KEY4_Scan())
					tem2=tem2-1;
				
				if(KEY2_Scan())
				{
					a=0;
					delay_ms(200);
					OLED_Clear();
				}
//				uart1_sent_tem(PWM_Duty);
			}
		}
	}
}


