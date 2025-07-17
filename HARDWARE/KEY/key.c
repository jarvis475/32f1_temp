#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
}

//����������
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
 	return 0;// �ް�������
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
 	return 0;// �ް�������
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
 	return 0;// �ް�������
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
 	return 0;// �ް�������
}