#include "ds18b20.h"
#include "ds18b20_platform.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief ds18b20 命令
 */
#define DS18B20_READ_ROM          0x33
#define DS18B20_MATCH_ROM         0x55
#define DS18B20_SKIP_ROM          0xCC
#define DS18B20_SEARCH_ROM        0xF0
#define DS18B20_ALARM_SEARCH      0xEC
#define DS18B20_WRITE_SCRATCHPAD  0x4E
#define DS18B20_READ_SCRATCHPAD   0xBE
#define DS18B20_COPY_SCRATCHPAD   0x48
#define DS18B20_CONVERT_T         0x44
#define DS18B20_RECALL_E2         0xB8
#define DS18B20_READ_POWER_SUPPLY 0xB4

/**
 * @brief 初始化
 * @note  平台相关
 */
static uint8_t ds18b20_init(ds18b20_dev_t *dev) { return ds18b20_platform_init(dev); }

/**
 * @brief 反初始化
 * @note  平台相关
 */
static uint8_t ds18b20_deinit(ds18b20_dev_t *dev) { return ds18b20_platform_deinit(dev); }

/**
 * @brief 切换读取模式，读取数据
 * @note  平台相关
 */
static uint8_t ds18b20_gpio_read(ds18b20_dev_t *dev, uint8_t *value) { return ds18b20_platform_gpio_read(dev, value); }

/**
 * @brief 切换写入模式，输出数据
 * @note  平台相关
 */
static uint8_t ds18b20_gpio_write(ds18b20_dev_t *dev, uint8_t value) { return ds18b20_platform_gpio_write(dev, value); }

/**
 * @brief 延时函数
 * @note  平台相关
 */
static uint8_t ds18b20_delay_us(uint32_t us) { return ds18b20_platform_delay_us(us); }

/**
 * @brief 延时函数
 * @note  平台相关
 */
static uint8_t ds18b20_delay_ms(uint32_t ms) { return ds18b20_platform_delay_ms(ms); }

/**
 * @brief ds18b20 复位
 *
 * @param dev      ds18b20 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
static uint8_t ds18b20_reset(ds18b20_dev_t *dev)
{
    uint8_t value = 0;
    uint8_t retry = 0;
    uint8_t err   = 0;

    /* 输出低电平 480us - 960us */
    err = ds18b20_gpio_write(dev, 0);
    if (err)
        return 1;

    ds18b20_delay_us(720);

    /* 输出高电平 15us - 60us */
    err = ds18b20_gpio_write(dev, 1);
    if (err)
        return 2;

    ds18b20_delay_us(60);

    /* 检测低电平 */
    value = 1;
    retry = 0;
    err   = ds18b20_gpio_read(dev, &value);
    if (err)
        return 3;

    while (value != 0 && retry < 200)
    {
        retry++;
        ds18b20_delay_us(1);
        err = ds18b20_gpio_read(dev, &value);
        if (err)
            return 3;
    }

    if (retry >= 200)
        return 4;

    /* 输入低电平 60us - 240us */
    value = 1;
    retry = 0;
    err   = ds18b20_gpio_read(dev, &value);
    if (err)
        return 5;

    while (value != 0 && retry < 240)
    {
        retry++;
        ds18b20_delay_us(1);
        err = ds18b20_gpio_read(dev, &value);
        if (err)
            return 5;
    }

    if (retry >= 240)
        return 6;

    return 0;
}

/**
 * @brief ds18b20 写入一个字节
 *
 * @param dev      ds18d20 设备
 * @param value    写入的数据
 * @return uint8_t 0: 成功; 其他: 失败
 */
static uint8_t ds18b20_write_byte(ds18b20_dev_t *dev, uint8_t value)
{
    uint8_t i   = 0;
    uint8_t bit = 0;
    uint8_t err = 0;
    for (; i < 8; i++)
    {
        bit = value & 0x01;
        value >>= 1;
        /* 输出低电平 2us */
        err = ds18b20_gpio_write(dev, 0);
        if (err)
            return 1;

        ds18b20_delay_us(2);

        if (bit == 1)
        {
            /* 输出高电平 60us */
            err = ds18b20_gpio_write(dev, 1);
            if (err)
                return 2;

            ds18b20_delay_us(60);
        }
        else
        {
            /* 输出低电平 60us */
            err = ds18b20_gpio_write(dev, 0);
            if (err)
                return 3;
            ds18b20_delay_us(60);
            /* 输出高电平 2us */
            err = ds18b20_gpio_write(dev, 1);
            if (err)
                return 4;

            ds18b20_delay_us(2);
        }
    }
    return 0;
}

/**
 * @brief ds18b20 读取一个字节
 *
 * @param dev      ds18d20 设备
 * @param value    读取的数据
 * @return uint8_t 0: 成功; 其他: 失败
 */
static uint8_t ds18b20_read_byte(ds18b20_dev_t *dev, uint8_t *value)
{
    uint8_t err = 0;
    uint8_t i   = 0;
    uint8_t bit = 0;
    for (; i < 8; i++)
    {
        /* 输出低电平 2us */
        err = ds18b20_gpio_write(dev, 0);
        if (err)
            return 1;

        ds18b20_delay_us(2);

        /* 释放,输出高电平 */
        err = ds18b20_gpio_write(dev, 1);
        if (err)
            return 2;

        /* 等待 10us, 采集数据 */
        ds18b20_delay_us(10);
        err = ds18b20_gpio_read(dev, &bit);
        if (err)
            return 3;

        *value = (*value >> 1) | (bit << 7);

        /* slot >= 60us */
        ds18b20_delay_us(50);
    }
    return 0;
}

ds18b20_dev_t *ds18b20_open(void)
{
    ds18b20_dev_t *dev = malloc(sizeof(ds18b20_dev_t));
    if (dev == NULL)
        return NULL;
    memset(dev, 0, sizeof(ds18b20_dev_t));

    /* 初始化平台相关 */
    if (ds18b20_init(dev) != 0)
    {
        memset(dev, 0, sizeof(ds18b20_dev_t));
        free(dev);
        return NULL;
    }
    return dev;
}

uint8_t ds18b20_close(ds18b20_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    /* 反初始化平台相关 */
    if (ds18b20_deinit(dev) != 0)
        return 2;

    memset(dev, 0, sizeof(ds18b20_dev_t));
    free(dev);
    return 0;
}

uint8_t ds18b20_read(ds18b20_dev_t *dev)
{
    uint8_t  err  = 0;
    uint16_t temp = 0;

    /* 复位 */
    err = ds18b20_reset(dev);
    if (err)
        return 1;

    /* 跳过rom */
    err = ds18b20_write_byte(dev, DS18B20_SKIP_ROM);
    if (err)
        return 2;

    /* 开始转化 */
    err = ds18b20_write_byte(dev, DS18B20_CONVERT_T);
    if (err)
        return 3;

    /* 等待转化 */
    ds18b20_delay_ms(750);

    /* 复位 */
    err = ds18b20_reset(dev);
    if (err)
        return 4;

    /* 跳过rom */
    err = ds18b20_write_byte(dev, DS18B20_SKIP_ROM);
    if (err)
        return 5;

    /* 读取温度 */
    err = ds18b20_write_byte(dev, DS18B20_READ_SCRATCHPAD);
    if (err)
        return 6;

    /* 读取低位 */
    err = ds18b20_read_byte(dev, &dev->raw_data[0]);
    if (err)
        return 7;

    /* 读取高位 */
    err = ds18b20_read_byte(dev, &dev->raw_data[1]);
    if (err)
        return 8;

    /* 计算温度, 默认设置为12位精度 */
    temp = (dev->raw_data[1] << 8) | dev->raw_data[0];
    if (temp & 0x8000)
    {
        temp             = ~temp + 1;
        dev->temperature = -temp * 0.0625f;
    }
    else
    {
        dev->temperature = temp * 0.0625f;
    }

    return 0;
}
