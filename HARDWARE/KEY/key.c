#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTBʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;//K3,K4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB10,11

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}
//����������
u8 KEY2_Scan(void)
{	 
	if(WK_UP==1)
	{
		return 1;
	}
 	return 0;// �ް�������
}

//����������
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

//����������
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
