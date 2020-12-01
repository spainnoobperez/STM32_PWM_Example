#include <stm32f4xx.h>
#include "tim_pwm.h"
#include "LED.h"
#include "beep.h"
#include <misc.h>

void main() {
    int dir = 1, led0pwmval = 0;
    LED_Init();
    Beep_Init();
    TIMLED_Init(500 - 1, 84 - 1);
    TIMBEEP_Init(500 - 1, 84 - 1, 100);
    delay_init(168);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    while(1) {
        delay_ms(2);
        if(dir) led0pwmval++;
        else led0pwmval--;
        if(led0pwmval > 200) dir = 0;
        if(led0pwmval == 0) dir = 1;
        TIM_SetCompare1(TIM14, led0pwmval);
    }
}