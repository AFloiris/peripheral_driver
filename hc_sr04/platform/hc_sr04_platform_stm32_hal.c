#include "af_delay.h"
#include "gpio.h"
#include "hc_sr04_platform.h"
#include "stm32f4xx_hal_tim.h"

#define HC_SR04_TRIG_PIN       GPIO_PIN_0
#define HC_SR04_ECHO_PIN       GPIO_PIN_1
#define HC_SR04_TRIG_GPIO_PORT GPIOA
#define HC_SR04_ECHO_GPIO_PORT GPIOA

extern TIM_HandleTypeDef htim2;

uint8_t hc_sr04_platform_init(hc_sr04_dev_t *dev)
{
    // tim2 计时器时钟为 1MHz
    return 0;
}


uint8_t hc_sr04_platform_deinit(hc_sr04_dev_t *dev)
{
    //
    return 0;
}

uint8_t hc_sr04_platform_trig_gpio_write(hc_sr04_dev_t *dev, uint8_t value)
{
    HAL_GPIO_WritePin(HC_SR04_TRIG_GPIO_PORT, HC_SR04_TRIG_PIN, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
    return 0;
}

uint8_t hc_sr04_platform_echo_gpio_read(hc_sr04_dev_t *dev, uint8_t *value)
{
    *value = HAL_GPIO_ReadPin(HC_SR04_ECHO_GPIO_PORT, HC_SR04_ECHO_PIN);
    return 0;
}

uint8_t hc_sr04_platform_start_clock(hc_sr04_dev_t *dev)
{
    HAL_TIM_Base_Start(&htim2);
    return 0;
}

uint8_t hc_sr04_platform_stop_clock(hc_sr04_dev_t *dev)
{
    HAL_TIM_Base_Stop(&htim2);
    return 0;
}

uint8_t hc_sr04_platform_get_clock_us(hc_sr04_dev_t *dev, uint32_t *us)
{
    *us = __HAL_TIM_GET_COUNTER(&htim2);
    return 0;
}

uint8_t hc_sr04_platform_delay_us(uint32_t us)
{
    af_delay_us(us);
    return 0;
}
