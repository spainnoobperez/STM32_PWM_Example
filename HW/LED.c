#include <LED.h>

void LED_Init() {
    GPIO_InitTypeDef g1;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    g1.GPIO_Mode = GPIO_Mode_OUT | GPIO_Mode_AF;
    g1.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    g1.GPIO_OType = GPIO_OType_PP;
    g1.GPIO_PuPd = GPIO_PuPd_UP;
    g1.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOF, &g1);
    GPIO_SetBits(GPIOF, GPIO_Pin_9 | GPIO_Pin_10);
}