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

void af_gpio_init(af_gpio_t *gpio)
{
    uint32_t mode = 0;
    uint32_t pull = 0;

    mode = af_gpio_mode_to_hal(gpio->mode);
    pull = af_gpio_pull_to_hal(gpio->pull);

    gpio->init_struct.Pin   = gpio->pin;
    gpio->init_struct.Mode  = mode;
    gpio->init_struct.Pull  = pull;
    gpio->init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(gpio->port, &gpio->init_struct);
    gpio->init = 1;
}

void af_gpio_deinit(af_gpio_t *gpio)
{
    HAL_GPIO_DeInit(gpio->port, gpio->pin);
    gpio->init = 0;
}

void af_gpio_set_mode(af_gpio_t *gpio, af_gpio_mode_t mode)
{
    uint32_t hal_mode      = af_gpio_mode_to_hal(mode);
    gpio->init_struct.Mode = hal_mode;
    HAL_GPIO_Init(gpio->port, &gpio->init_struct);
    gpio->mode = mode;
}

uint8_t af_gpio_read(af_gpio_t *gpio)
{
    return HAL_GPIO_ReadPin(gpio->port, gpio->pin);
}

void af_gpio_write(af_gpio_t *gpio, uint8_t value)
{
    HAL_GPIO_WritePin(gpio->port, gpio->pin, (GPIO_PinState)value);
}