#include "af_delay.h"
#include "dht11.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief 切换读取模式，读取数据
 * @note  平台相关
 */
static uint8_t dht11_wire_read(dht11_dev_t *dev)
{
    uint8_t value = 0;
    if (dev->gpio.mode != AF_GPIO_MODE_INPUT)
    {
        af_gpio_set_mode(&dev->gpio, AF_GPIO_MODE_INPUT);
    }
    af_gpio_read(&dev->gpio, &value);
    return value;
}

/**
 * @brief 切换写入模式，输出数据
 * @note  平台相关
 */
static void dht11_wire_write(dht11_dev_t *dev, uint8_t value)
{
    if (dev->gpio.mode != AF_GPIO_MODE_OUTPUT_PP)
    {
        af_gpio_set_mode(&dev->gpio, AF_GPIO_MODE_OUTPUT_PP);
    }
    af_gpio_write(&dev->gpio, value);
}

/**
 * @brief 延时函数
 * @note  平台相关
 */
static void dht11_delay_us(uint32_t us) { af_delay_us(us); }

/**
 * @brief 延时函数
 * @note  平台相关
 */
static void dht11_delay_ms(uint32_t ms) { af_delay_ms(ms); }

/**
 * @brief dht11 复位
 * @note  驱动相关
 */
static uint8_t dht11_reset(dht11_dev_t *dev)
{

    uint8_t value = 0, retry = 0;

    /* 主机输出 20ms 低电平 */
    dht11_wire_write(dev, 0);
    dht11_delay_ms(20);

    /* 主机输出 20~40us 高电平 */
    dht11_wire_write(dev, 1);
    dht11_delay_us(30);

    /* 等待 dht11 拉低电平 40-50us  */
    value = dht11_wire_read(dev);
    while (value == 1 && retry < 100)
    {
        retry++;
        dht11_delay_us(1);
        value = dht11_wire_read(dev);
    }
    if (retry >= 100)
        return 1;
    else
        retry = 0;

    /* 等待 dht11 拉高电平 40-50us */
    value = dht11_wire_read(dev);
    while (value == 0 && retry < 100)
    {
        retry++;
        dht11_delay_us(1);
        value = dht11_wire_read(dev);
    }
    if (retry >= 100)
        return 2;
    else
        return 0;
}

/**
 * @brief dht11 读取bit数据
 * @note  驱动相关
 */
static uint8_t dht11_read_bit(dht11_dev_t *dev, uint8_t *value)
{

    uint8_t retry = 0;

    /* 等待 dht11 拉低电平 */
    *value = dht11_wire_read(dev);
    while (*value == 1 && retry < 100)
    {
        retry++;
        dht11_delay_us(1);
        *value = dht11_wire_read(dev);
    }
    if (retry >= 100)
        return 1;
    else
        retry = 0;

    /* 等待 dht11 拉高电平 */
    *value = dht11_wire_read(dev);
    while (*value == 0 && retry < 100)
    {
        retry++;
        dht11_delay_us(1);
        *value = dht11_wire_read(dev);
    }
    if (retry >= 100)
        return 2;

    /* 40us 后判断bit */
    dht11_delay_us(40);
    *value = dht11_wire_read(dev);
    return 0;
}

/**
 * @brief dht11 读取byte数据
 * @note  驱动相关
 */
static uint8_t dht11_read_byte(dht11_dev_t *dev, uint8_t *value)
{

    uint8_t i = 0, ret = 0, bit = 0;
    for (; i < 8; i++)
    {
        ret = dht11_read_bit(dev, &bit);
        if (ret)
            return ret;
        *value = (*value << 1) | bit;
    }
    return 0;
}

dht11_dev_t *dht11_open(af_gpio_t gpio)
{

    dht11_dev_t *dev = malloc(sizeof(dht11_dev_t));
    if (dev != NULL)
    {
        memset(dev, 0, sizeof(dht11_dev_t));
        dev->gpio = gpio;
    }
    if (dev->gpio.init == 0)
    {
        af_gpio_init(&dev->gpio);
    }
    return dev;
}

void dht11_close(dht11_dev_t *dev)
{

    if (dev == NULL)
    {
        return;
    }

    if (dev->gpio.init == 1)
    {
        af_gpio_deinit(&dev->gpio);
    }

    memset(dev, 0, sizeof(dht11_dev_t));
    free(dev);
}

uint8_t dht11_read(dht11_dev_t *dev)
{

    uint8_t ret = 0;
    uint8_t i   = 0;

    if (dev == NULL)
        return 1;

    /* 复位 */
    ret = dht11_reset(dev);
    if (ret)
        return 2;

    /* 读取数据 */
    for (; i < 5; i++)
    {
        ret = dht11_read_byte(dev, &dev->data[i]);
        if (ret)
            return 3;
    }

    /* 校验数据 */
    if (dev->data[4] != ((dev->data[0] + dev->data[1] + dev->data[2] + dev->data[3]) & 0xFF))
        return 4;

    /* 计算数据 */
    dev->humidity    = ((float)dev->data[0]) + ((float)dev->data[1]) / 10.0f;
    dev->temperature = ((float)(dev->data[2])) + ((float)(dev->data[3])) / 10.0f;

    return 0;
}
