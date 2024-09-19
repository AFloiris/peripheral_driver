#include "af_delay.h"
#include "dht11_platform.h"
#include "stm32f4xx_hal.h"

/* DHT11 GPIO */
#define DHT11_PLATFORM_GPIO_PORT GPIOD
#define DHT11_PLATFORM_GPIO_PIN  GPIO_PIN_15

/* 0: input, 1: output */
volatile static uint8_t dht11_gpio_state = 0;

uint8_t dht11_platform_init(dht11_dev_t *dev)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin   = DHT11_PLATFORM_GPIO_PIN;
    GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_PLATFORM_GPIO_PORT, &GPIO_InitStructure);
    return 0;
}

uint8_t dht11_platform_deinit(dht11_dev_t *dev)
{
    __HAL_RCC_GPIOB_CLK_DISABLE();
    HAL_GPIO_DeInit(DHT11_PLATFORM_GPIO_PORT, DHT11_PLATFORM_GPIO_PIN);
    return 0;
}

uint8_t dht11_platform_gpio_read(dht11_dev_t *dev, uint8_t *value)
{
    if (dht11_gpio_state != 0)
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.Pin   = DHT11_PLATFORM_GPIO_PIN;
        GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
        GPIO_InitStructure.Pull  = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(DHT11_PLATFORM_GPIO_PORT, &GPIO_InitStructure);
        dht11_gpio_state = 0;
    }
    *value = HAL_GPIO_ReadPin(DHT11_PLATFORM_GPIO_PORT, DHT11_PLATFORM_GPIO_PIN);
    return 0;
}

uint8_t dht11_platform_gpio_write(dht11_dev_t *dev, uint8_t value)
{
    if (dht11_gpio_state != 1)
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.Pin   = DHT11_PLATFORM_GPIO_PIN;
        GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.Pull  = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(DHT11_PLATFORM_GPIO_PORT, &GPIO_InitStructure);
        dht11_gpio_state = 1;
    }
    HAL_GPIO_WritePin(DHT11_PLATFORM_GPIO_PORT, DHT11_PLATFORM_GPIO_PIN, (GPIO_PinState)value);
    return 0;
}

void dht11_platform_delay_ms(uint32_t ms) { af_delay_ms(ms); }

void dht11_platform_delay_us(uint32_t us) { af_delay_us(us); }
