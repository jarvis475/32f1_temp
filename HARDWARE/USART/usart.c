#include "stm32f10x.h"
#include "usart.h" 
#include <string.h> 
u8 flag_led0;
// 初始化函数
void uart1_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    //使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE); 

    //USART1_TX  GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART1_RX  GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure); 

    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure); 
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

// 发送1个字节函数
void uart1_sent_byte(u8 text)
{
    USART_SendData(USART1, text);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

// 发送字符串函数
void uart1_sent_string(char* buf)
{
    u32 i=0;
    while(buf[i]!=0)
    {
        USART_SendData(USART1, buf[i]);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        i++;
    }
}

//发送温度读数  
void uart1_sent_tem(float tem,float set_temp)
{
	u8 buff[10];
	buff[0]=0xAA;
	memcpy(&buff[1], &tem, 4);
	memcpy(&buff[5], &set_temp, 4);
	buff[9]=0x55;
  for(int i=0;i<10;i++)
	{
		uart1_sent_byte(buff[i]);
	}
}

// 中断服务函数
void USART1_IRQHandler(void) 
{
    u8 Res;
    if(USART_GetITStatus(USART1, USART_IT_RXNE)!= RESET) 
    {
        uart1_sent_byte(Res); 

        if(Res=='0')
        {
            flag_led0=0;
        }
        if(Res=='1')
        {
            flag_led0=1;
        }
    }
    if(USART_GetFlagStatus(USART1, USART_FLAG_ORE) == SET) 
    {
        USART_ClearFlag(USART1, USART_FLAG_ORE);
        USART_ReceiveData(USART1);
    }
} 