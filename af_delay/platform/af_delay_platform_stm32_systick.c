#include "af_delay.h"
#include "stm32f407xx.h"

/* 全局计时变量 */
volatile uint32_t af_time_delay;

/**
 * @brief 使用系统滴答定时器实现延时功能,注意冲突
 */
void SysTick_Handler()
{
    if (af_time_delay)
        af_time_delay--;
}

void af_delay_ms(uint32_t ms)
{
    /* SYSTICK分频--1ms的系统时钟中断 */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        while (1)
        {};
    }
    af_time_delay = ms; /* 读取定时时间 */
    while (af_time_delay)
    {};                   /* 循环等待时间到达 */
    SysTick->CTRL = 0x00; /* 关闭计数器 */
    SysTick->VAL  = 0X00; /* 清空计数器 */
}

void af_delay_us(uint32_t us)
{
    /* SYSTICK分频--1us的系统时钟中断 */
    if (SysTick_Config(SystemCoreClock / 1000000))
    {
        while (1)
        {};
    }
    af_time_delay = us; /* 读取定时时间 */
    while (af_time_delay)
    {};                   /* 循环等待时间到达 */
    SysTick->CTRL = 0x00; /* 关闭计数器 */
    SysTick->VAL  = 0X00; /* 清空计数器 */
}
