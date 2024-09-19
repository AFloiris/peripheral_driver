#include "dht11.h"
#include "dht11_platform.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief 初始化
 * @note  平台相关
 */
static uint8_t dht11_init(dht11_dev_t *dev) { return dht11_platform_init(dev); }

/**
 * @brief 反初始化
 * @note  平台相关
 */
static uint8_t dht11_deinit(dht11_dev_t *dev) { return dht11_platform_deinit(dev); }

/**
 * @brief 切换读取模式，读取数据
 * @note  平台相关
 */
static uint8_t dht11_gpio_read(dht11_dev_t *dev, uint8_t *value) { return dht11_platform_gpio_read(dev, value); }

/**
 * @brief 切换写入模式，输出数据
 * @note  平台相关
 */
static void dht11_gpio_write(dht11_dev_t *dev, uint8_t value) { dht11_platform_gpio_write(dev, value); }

/**
 * @brief 延时函数
 * @note  平台相关
 */
static void dht11_delay_us(uint32_t us) { dht11_platform_delay_us(us); }

/**
 * @brief 延时函数
 * @note  平台相关
 */
static void dht11_delay_ms(uint32_t ms) { dht11_platform_delay_ms(ms); }

/**
 * @brief dht11 复位
 * @note  驱动相关
 */
static uint8_t dht11_reset(dht11_dev_t *dev)
{
    uint8_t value = 0, retry = 0;

    /* 主机输出 20ms 低电平 */
    dht11_gpio_write(dev, 0);
    dht11_delay_ms(20);

    /* 主机输出 20~40us 高电平 */
    dht11_gpio_write(dev, 1);
    dht11_delay_us(30);

    /* 等待 dht11 拉低电平 40-50us  */
    dht11_gpio_read(dev, &value);
    while (value == 1 && retry < 100)
    {
        retry++;
        dht11_delay_us(1);
        dht11_gpio_read(dev, &value);
    }
    if (retry >= 100)
        return 1;
    else
        retry = 0;

    /* 等待 dht11 拉高电平 40-50us */
    dht11_gpio_read(dev, &value);
    while (value == 0 && retry < 100)
    {
        retry++;
        dht11_delay_us(1);
        dht11_gpio_read(dev, &value);
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
    dht11_gpio_read(dev, value);
    while (*value == 1 && retry < 100)
    {
        retry++;
        dht11_delay_us(1);
        dht11_gpio_read(dev, value);
    }
    if (retry >= 100)
        return 1;
    else
        retry = 0;

    /* 等待 dht11 拉高电平 */
    dht11_gpio_read(dev, value);
    while (*value == 0 && retry < 100)
    {
        retry++;
        dht11_delay_us(1);
        dht11_gpio_read(dev, value);
    }
    if (retry >= 100)
        return 2;

    /* 40us 后判断bit */
    dht11_delay_us(40);
    dht11_gpio_read(dev, value);
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

dht11_dev_t *dht11_open(void)
{

    dht11_dev_t *dev = malloc(sizeof(dht11_dev_t));
    if (dev == NULL)
        return NULL;
    memset(dev, 0, sizeof(dht11_dev_t));

    /* 初始化平台相关 */
    if (dht11_init(dev) != 0)
    {
        free(dev);
        return NULL;
    }
    return dev;
}

uint8_t dht11_close(dht11_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    /* 反初始化平台相关 */
    if (dht11_deinit(dev) != 0)
        return 2;

    memset(dev, 0, sizeof(dht11_dev_t));
    free(dev);
    return 0;
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
