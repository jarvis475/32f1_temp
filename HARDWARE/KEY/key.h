#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define K3 PBin(10)   	//PB10  K3
#define K4 PBin(11)			//PB11  K4 
#define WK_UP PAin(0)		//PA0  WK_UP

void KEY_Init(void);//IO��ʼ��
u8 KEY2_Scan(void);  	//����ɨ�躯��
u8 KEY3_Scan(void);  	//����ɨ�躯��					    
u8 KEY4_Scan(void);  	//����ɨ�躯��					    
#endif
