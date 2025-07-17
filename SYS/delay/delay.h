#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  

#define SYSTEM_SUPPORT_OS 0		//定义系统文件夹是否支持UCOS


void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u32 nms);

#endif





























