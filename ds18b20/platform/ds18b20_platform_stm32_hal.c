#include "af_delay.h"
#include "ds18b20_platform.h"
#include "gpio.h"

/* DS18B20 GPIO */
#define DS18B20_PLATFORM_GPIO_PORT GPIOD
#define DS18B20_PLATFORM_GPIO_PIN  GPIO_PIN_15

/* 0: input, 1: output */
volatile static uint8_t ds18b20_gpio_state = 0;

uint8_t ds18b20_platform_init(ds18b20_dev_t *dev)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin   = DS18B20_PLATFORM_GPIO_PIN;
    GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DS18B20_PLATFORM_GPIO_PORT, &GPIO_InitStructure);
    return 0;
}

uint8_t ds18b20_platform_deinit(ds18b20_dev_t *dev)
{
    __HAL_RCC_GPIOB_CLK_DISABLE();
    HAL_GPIO_DeInit(DS18B20_PLATFORM_GPIO_PORT, DS18B20_PLATFORM_GPIO_PIN);
    return 0;
}

uint8_t ds18b20_platform_gpio_read(ds18b20_dev_t *dev, uint8_t *value)
{
    if (ds18b20_gpio_state != 0)
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.Pin   = DS18B20_PLATFORM_GPIO_PIN;
        GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
        GPIO_InitStructure.Pull  = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(DS18B20_PLATFORM_GPIO_PORT, &GPIO_InitStructure);
        ds18b20_gpio_state = 0;
    }
    *value = HAL_GPIO_ReadPin(DS18B20_PLATFORM_GPIO_PORT, DS18B20_PLATFORM_GPIO_PIN);
    return 0;
}

uint8_t ds18b20_platform_gpio_write(ds18b20_dev_t *dev, uint8_t value)
{
    if (ds18b20_gpio_state != 1)
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.Pin   = DS18B20_PLATFORM_GPIO_PIN;
        GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.Pull  = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(DS18B20_PLATFORM_GPIO_PORT, &GPIO_InitStructure);
        ds18b20_gpio_state = 1;
    }
    HAL_GPIO_WritePin(DS18B20_PLATFORM_GPIO_PORT, DS18B20_PLATFORM_GPIO_PIN, (GPIO_PinState)value);
    return 0;
}

uint8_t ds18b20_platform_delay_ms(uint32_t ms)
{
    af_delay_ms(ms);
    return 0;
}

uint8_t ds18b20_platform_delay_us(uint32_t us)
{
    af_delay_us(us);
    return 0;
}
