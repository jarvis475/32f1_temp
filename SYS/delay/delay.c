#include "delay.h"
static u8  fac_us;							//us��ʱ������			   
static u16 fac_ms;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��
			   
void delay_init()
{
	// 设置SysTick时钟源为HCLK/8
SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
	fac_us=SystemCoreClock/8000000;				//Ϊϵͳʱ�ӵ�1/8  
	fac_ms=(u16)fac_us*1000;					//��OS��,����ÿ��ms��Ҫ��systickʱ����   
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;

}								    

//��ʱnus
//nusΪҪ��ʱ��us��.	
u32 TimingDelay;
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					
	SysTick->VAL=0x00;        					
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	
	SysTick->VAL =0X00;      					 	 
}

//��ʱnms
//nmsΪҪ��ʱ��ms��.	
void delay_ms(u32 nms)
{		
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;
}







































