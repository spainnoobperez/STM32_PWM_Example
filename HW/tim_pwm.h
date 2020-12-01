#ifndef __TIM_PWM_H_
#define __TIM_PWM_H_

#include <stm32f4xx.h>
#include <stdint.h>

static u8  fac_us = 0;
static u16 fac_ms = 0;

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

void TIMLED_Init(u32 psc, u32 arr);
void TIMBEEP_Init(u32 psc, u32 arr, u32 pulse);

#endif