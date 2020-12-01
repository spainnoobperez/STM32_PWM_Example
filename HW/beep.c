#include "beep.h"

void Beep_Init() {
    GPIO_InitTypeDef initstu;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    initstu.GPIO_Pin = GPIO_Pin_8;
    initstu.GPIO_Mode = GPIO_Mode_OUT;
    initstu.GPIO_OType = GPIO_OType_PP;
    initstu.GPIO_PuPd = GPIO_PuPd_DOWN;
    initstu.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &initstu);
    GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}