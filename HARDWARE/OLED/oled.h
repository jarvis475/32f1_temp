#ifndef __OLED__H
#define __OLED__H			  	 


#include "stm32f10x.h"
#include "myiic.h"

///*--------------------���Ŷ���--------------------------*/
//#define 		OLED_SCLK_Set()			GPIO_SetBits(GPIOB,GPIO_Pin_6)	//PA5��SCL�������
//#define			OLED_SCLK_Clr()			GPIO_ResetBits(GPIOB,GPIO_Pin_6)	//PA5��SCL�������
//#define			OLED_SDIN_Set()			GPIO_SetBits(GPIOB,GPIO_Pin_7)	//PA7��SDA�������
//#define			OLED_SDIN_Clr()			GPIO_ResetBits(GPIOB,GPIO_Pin_7)	//PA7��SDA�������
//#define 		OLED_READ_SDIN()		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)	//��ȡPA7��SDA����ƽ
//		

/*definition--------------------------------------------*/
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define SIZE 		16		//��ʾ�ַ��Ĵ�С
#define Max_Column	128		//�������
#define Max_Row		64		//�������
#define X_WIDTH 	128		//X��Ŀ��
#define Y_WIDTH 	64	    //Y��Ŀ��					  				   
#define	IIC_ACK		0		//Ӧ��
#define	IIC_NO_ACK	1		//��Ӧ��




/*-----------------��������-----------------------------*/
void OLED_WR_Byte(unsigned char dat,unsigned char cmd);	  //OLEDд�ֽں���
void OLED_Display_On(void);	//����ʾ����
void OLED_Display_Off(void);//����ʾ����
void OLED_Init(void);	//OLED��ʼ������
void OLED_Clear(void);  //��������
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr); //��ʾ�ַ�����
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2); //��ָ����λ�ã���ʾһ��ָ�����ĳ��ȴ�С����
void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p);	 //��ָ��λ�ÿ�ʼ��ʾ�ַ�������
void OLED_Set_Pos(unsigned char x, unsigned char y);		//���㺯��
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no); //������ָ��λ����ʾ���ֺ���
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]); //��ʾͼƬ����
void OLED_Scroll(void);	//��������

#endif  
	 



