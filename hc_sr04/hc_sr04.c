#include "hc_sr04.h"
#include "hc_sr04_platform.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief 初始化
 * @note  平台相关
 */
static uint8_t hc_sr04_init(hc_sr04_dev_t *dev) { return hc_sr04_platform_init(dev); }

/**
 * @brief 反初始化
 * @note  平台相关
 */
static uint8_t hc_sr04_deinit(hc_sr04_dev_t *dev) { return hc_sr04_platform_deinit(dev); }

/**
 * @brief trig 引脚写入
 *
 * @param dev      hc_sr04 设备
 * @param value    写入值
 * @return uint8_t 0:成功; 其他:失败
 * @note  平台相关
 */
static uint8_t hc_sr04_trig_gpio_write(hc_sr04_dev_t *dev, uint8_t value)
{
    return hc_sr04_platform_trig_gpio_write(dev, value);
}

/**
 * @brief echo 引脚读取
 *
 * @param dev      hc_sr04 设备
 * @param value    读取值
 * @return uint8_t 0:成功; 其他:失败
 * @note  平台相关
 */
static uint8_t hc_sr04_echo_gpio_read(hc_sr04_dev_t *dev, uint8_t *value)
{
    return hc_sr04_platform_echo_gpio_read(dev, value);
}

/**
 * @brief 开始计时
 *
 * @param dev      hc_sr04 设备
 * @return uint8_t 0:成功; 其他:失败
 * @note  平台相关
 */
static uint8_t hc_sr04_start_clock(hc_sr04_dev_t *dev) { return hc_sr04_platform_start_clock(dev); }

/**
 * @brief 停止计时
 *
 * @param dev      hc_sr04 设备
 * @return uint8_t 0:成功; 其他:失败
 * @note  平台相关
 */
static uint8_t hc_sr04_stop_clock(hc_sr04_dev_t *dev) { return hc_sr04_platform_stop_clock(dev); }

/**
 * @brief 获取计时时间, 单位:us
 *
 * @param dev      hc_sr04 设备
 * @param us       计时时间
 * @return uint8_t 0:成功; 其他:失败
 * @note  平台相关
 */
static uint8_t hc_sr04_get_clock_us(hc_sr04_dev_t *dev, uint32_t *us) { return hc_sr04_platform_get_clock_us(dev, us); }

/**
 * @brief 延时函数
 * @note  平台相关
 */
static uint8_t hc_sr04_delay_us(uint32_t us) { return hc_sr04_platform_delay_us(us); }

hc_sr04_dev_t *hc_sr04_open(void)
{
    hc_sr04_dev_t *dev = malloc(sizeof(hc_sr04_dev_t));
    if (dev == NULL)
        return NULL;

    memset(dev, 0, sizeof(hc_sr04_dev_t));

    /* 初始化平台相关 */
    if (hc_sr04_init(dev) != 0)
    {
        memset(dev, 0, sizeof(hc_sr04_dev_t));
        free(dev);
        return NULL;
    }
    return dev;
}

uint8_t hc_sr04_close(hc_sr04_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    /* 反初始化平台相关 */
    if (hc_sr04_deinit(dev) != 0)
        return 2;

    memset(dev, 0, sizeof(hc_sr04_dev_t));
    free(dev);
    return 0;
}

uint8_t hc_sr04_read(hc_sr04_dev_t *dev)
{
    uint8_t err  = 0;
    uint8_t echo = 0;
    if (dev == NULL)
        return 1;

    /* 发送一个 10us 的脉冲 */
    err = hc_sr04_trig_gpio_write(dev, 1);
    if (err)
        return 2;

    hc_sr04_delay_us(10);

    err = hc_sr04_trig_gpio_write(dev, 0);
    if (err)
        return 3;

    /* 等待回响信号 */
    err = hc_sr04_echo_gpio_read(dev, &echo);
    if (err)
        return 4;

    while (echo == 0)
    {
        err = hc_sr04_echo_gpio_read(dev, &echo);
        if (err)
            return 5;
    }

    /* 开始计时 */
    err = hc_sr04_start_clock(dev);
    if (err)
        return 6;

    err = hc_sr04_echo_gpio_read(dev, &echo);
    if (err)
        return 7;

    while (echo == 1)
    {
        err = hc_sr04_echo_gpio_read(dev, &echo);
        if (err)
            return 8;
    }

    /* 结束计时 */
    err = hc_sr04_stop_clock(dev);
    if (err)
        return 9;

    /* 获取时间 */
    err = hc_sr04_get_clock_us(dev, &dev->time);
    if (err)
        return 10;

    /* 计算距离 */
    dev->distance = dev->time * 0.017f;

    return 0;
}
