#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  

#define SYSTEM_SUPPORT_OS 0		//����ϵͳ�ļ����Ƿ�֧��UCOS


void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u32 nms);

#endif





























