#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

extern u8 flag_led0;
extern u8 flag_led1;
extern u32 led0_counter;
extern u32 led1_counter;
extern u32 led0_time;
extern u32 led1_time;
extern u32 time_now;
void TIM3_ENABLE(void);
void TIM3_DISABLE(void);
void TIM3_Int_Init(u16 arr,u16 psc);


void TIM4_Int_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
#endif
