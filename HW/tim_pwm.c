#include "tim_pwm.h"





void delay_init(u8 SYSCLK) {
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SYSCLK / 8;
    fac_ms = (u16)fac_us * 1000;
}

void delay_us(u32 nus) {
    u32 temp;
    SysTick->LOAD = nus * fac_us;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;
    do {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}






void delay_xms(u16 nms) {
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;
    do {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}


void delay_ms(u16 nms) {
    u8 repeat = nms / 540;
    u16 remain = nms % 540;
    while(repeat) {
        delay_xms(540);
        repeat--;
    }
    if(remain)delay_xms(remain);
}

void TIMBEEP_Init(u32 psc, u32 arr, u32 pulse) {
    GPIO_InitTypeDef git;
    TIM_TimeBaseInitTypeDef tbi;
    TIM_OCInitTypeDef toi;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM13);
    git.GPIO_Pin = GPIO_Pin_8;
    git.GPIO_Mode = GPIO_Mode_AF;
    git.GPIO_Speed = GPIO_Speed_100MHz;
    git.GPIO_OType = GPIO_OType_PP;
    git.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOF, &git);
    tbi.TIM_ClockDivision = TIM_CKD_DIV1;
    tbi.TIM_CounterMode = TIM_CounterMode_Up;
    tbi.TIM_Period = arr;
    tbi.TIM_Prescaler = psc;
    TIM_TimeBaseInit(TIM13, &tbi);
    toi.TIM_OCMode = TIM_OCMode_PWM1;
    toi.TIM_OCPolarity = TIM_OCPolarity_High;
    toi.TIM_OutputState = TIM_OutputState_Enable;
    toi.TIM_Pulse = pulse;
    TIM_OC2Init(TIM13, &toi);
    TIM_OC2PreloadConfig(TIM13, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM13, ENABLE);
    TIM_Cmd(TIM13, ENABLE);
}

void TIMLED_Init(u32 psc, u32 arr) {
    GPIO_InitTypeDef git;
    TIM_TimeBaseInitTypeDef tbi;
    TIM_OCInitTypeDef toi;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);
    git.GPIO_Pin = GPIO_Pin_9;
    git.GPIO_Mode = GPIO_Mode_AF;
    git.GPIO_Speed = GPIO_Speed_100MHz;
    git.GPIO_OType = GPIO_OType_PP;
    git.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &git);
    tbi.TIM_ClockDivision = TIM_CKD_DIV1;
    tbi.TIM_CounterMode = TIM_CounterMode_Up;
    tbi.TIM_Period = arr;
    tbi.TIM_Prescaler = psc;
    TIM_TimeBaseInit(TIM14, &tbi);
    toi.TIM_OCMode = TIM_OCMode_PWM1;
    toi.TIM_OCPolarity = TIM_OCPolarity_Low;
    toi.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC1Init(TIM14, &toi);
    TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM14, ENABLE);
    TIM_Cmd(TIM14, ENABLE);
}