#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

/* ���Ͷ��� */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

/* ȫ�ֱ������� */
extern u8 flag_led0;

/* �������� */
void uart1_init(u32 bound);
void uart1_sent_byte(u8 text);
void uart1_sent_string(char* buf);
void uart1_sent_tem(float tem,float set_temp);
void uart1_sent_set(float set);

#endif /* __USART_H */