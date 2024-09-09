#include "af_delay.h"
#include "main.h"

/* 全局计时变量 */
volatile unsigned long af_time_delay;

/**
 * @brief 使用系统滴答定时器实现延时功能,注意冲突
 */
void SysTick_Handler()
{
    if (af_time_delay)
        af_time_delay--;
}

void af_delay_ms(volatile unsigned long ms)
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

void af_delay_us(volatile unsigned long us)
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

/* 以下为使用了FreeRTOS的延时函数 */

/**

void a_delay_us(volatile unsigned long us) {

    uint32_t ticks;
    uint32_t told, tnow, reload, tcnt = 0;

    reload = SysTick->LOAD;                     //获取重装载寄存器值
    ticks = us * (SystemCoreClock / 1000000);  //计数时间值
    told = SysTick->VAL;                          //获取当前数值寄存器值（开始时数值）

    while (1) {
        tnow = SysTick->VAL;			//获取当前数值寄存器值
        if (tnow != told) {           	//当前值不等于开始值说明已在计数
            if (tnow < told) {
                tcnt += told - tnow;     		//计数值=开始值-当前值
            }          							//当前值小于开始数值，说明未计到0
            else {								//当前值大于开始数值，说明已计到0并重新计数
                tcnt += reload - tnow + told;   //计数值=重装载值-当前值+开始值  （已从开始值计到0）
            }
            told = tnow;                //更新开始值
            if (tcnt >= ticks) {
                break;     //时间超过/等于要延迟的时间,则退出.
            }

        }
    }
}

void a_delay_ms(volatile unsigned long ms) {
    vTaskDelay(ms);
}

*/
