#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

/* 类型定义 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

/* 全局变量声明 */
extern u8 flag_led0;

/* 函数声明 */
void uart1_init(u32 bound);
void uart1_sent_byte(u8 text);
void uart1_sent_string(char* buf);
void uart1_sent_tem(float tem,float set_temp);
void uart1_sent_set(float set);

#endif /* __USART_H */