#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define K1 PAin(7)   		//PA7  K1
#define K2 PAin(6)			//PA6  K2 
#define K3 PAin(5)   		//PA5  K3
#define K4 PAin(3)			//PA3  K4 

void KEY_Init(void);//IO初始化
u8 KEY1_Scan(void);		//按键扫描函数
u8 KEY2_Scan(void);  	//按键扫描函数
u8 KEY3_Scan(void);  	//按键扫描函数					    
u8 KEY4_Scan(void);  	//按键扫描函数					    
#endif
