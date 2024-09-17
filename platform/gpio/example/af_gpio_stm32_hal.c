#include "af_gpio.h"

static uint32_t af_gpio_mode_to_hal(af_gpio_mode_t mode)
{
    uint32_t hal_mode = 0;
    switch (mode)
    {
    case AF_GPIO_MODE_INPUT:
        hal_mode = GPIO_MODE_INPUT;
        break;
    case AF_GPIO_MODE_OUTPUT_PP:
        hal_mode = GPIO_MODE_OUTPUT_PP;
        break;
    case AF_GPIO_MODE_OUTPUT_OD:
        hal_mode = GPIO_MODE_OUTPUT_OD;
        break;
    default:
        hal_mode = GPIO_MODE_OUTPUT_PP;
        break;
    }
    return hal_mode;
}

static uint32_t af_gpio_pull_to_hal(af_gpio_pull_t pull)
{
    uint32_t hal_pull = 0;
    switch (pull)
    {
    case AF_GPIO_PULL_NONE:
        hal_pull = GPIO_NOPULL;
        break;
    case AF_GPIO_PULL_UP:
        hal_pull = GPIO_PULLUP;
        break;
    case AF_GPIO_PULL_DOWN:
        hal_pull = GPIO_PULLDOWN;
        break;
    default:
        hal_pull = GPIO_NOPULL;
        break;
    }
    return hal_pull;
}

uint8_t af_gpio_init(af_gpio_t *gpio)
{
    uint32_t mode = 0;
    uint32_t pull = 0;

    mode = af_gpio_mode_to_hal(gpio->mode);
    pull = af_gpio_pull_to_hal(gpio->pull);

    gpio->gpio_init.Pin   = gpio->pin;
    gpio->gpio_init.Mode  = mode;
    gpio->gpio_init.Pull  = pull;
    gpio->gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(gpio->port, &gpio->gpio_init);
    gpio->init = 1;
    return 0;
}

void af_gpio_deinit(af_gpio_t *gpio)
{
    HAL_GPIO_DeInit(gpio->port, gpio->pin);
    gpio->init = 0;
}

uint8_t af_gpio_set_mode(af_gpio_t *gpio, af_gpio_mode_t mode)
{
    uint32_t hal_mode    = af_gpio_mode_to_hal(mode);
    gpio->gpio_init.Mode = hal_mode;
    HAL_GPIO_Init(gpio->port, &gpio->gpio_init);
    gpio->mode = mode;
    return 0;
}

uint8_t af_gpio_read(af_gpio_t *gpio, uint8_t *value)
{
    *value = (uint8_t)HAL_GPIO_ReadPin(gpio->port, gpio->pin);
    return 0;
}

uint8_t af_gpio_write(af_gpio_t *gpio, uint8_t value)
{
    HAL_GPIO_WritePin(gpio->port, gpio->pin, (GPIO_PinState)value);
    return 0;
}
