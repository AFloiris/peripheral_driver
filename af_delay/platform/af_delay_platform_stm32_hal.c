#include "af_delay.h"
#include "stm32f4xx_hal.h"

/* 每微秒的时钟周期数 */
static uint32_t af_clk_cyc_us = 0;

static void af_delay_get_clk_cyc_us(void)
{
    uint32_t system_clk_freq = HAL_RCC_GetSysClockFreq();
    uint32_t reload_value    = SysTick->LOAD;
    af_clk_cyc_us            = system_clk_freq / reload_value;
}

void af_delay_ms(uint32_t ms) { HAL_Delay(ms); }

void af_delay_us(uint32_t us)
{

    if (af_clk_cyc_us == 0)
    {
        af_delay_get_clk_cyc_us();
    }

    uint32_t ticks = us * af_clk_cyc_us;
    uint32_t told  = SysTick->VAL;
    uint32_t tnow;
    uint32_t tcnt   = 0;
    uint32_t reload = SysTick->LOAD;

    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}
