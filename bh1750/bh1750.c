#include "bh1750.h"
#include "bh1750_platform.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief 初始化
 *
 * @param dev bh1750 设备
 * @return uint8_t 0: 成功; 其他: 失败
 * @note  平台相关
 */
uint8_t bh1750_init(bh1750_dev_t *dev) { return bh1750_platform_init(dev); }

/**
 * @brief 反初始化
 *
 * @param dev bh1750 设备
 * @return uint8_t 0: 成功; 其他: 失败
 * @note  平台相关
 */
uint8_t bh1750_deinit(bh1750_dev_t *dev) { return bh1750_platform_deinit(dev); }

/**
 * @brief i2c写数据
 *
 * @param dev      bh1750 设备
 * @param i2c_addr i2c地址
 * @param data      要写入的数据
 * @return uint8_t 0: 成功; 其他: 失败
 * @note  平台相关
 */
uint8_t bh1750_i2c_write(bh1750_dev_t *dev, uint8_t i2c_addr, uint8_t data)
{
    return bh1750_platform_i2c_write(dev, i2c_addr, data);
}

uint8_t bh1750_delay_ms(uint32_t ms) { return bh1750_platform_delay_ms(ms); }

/**
 * @brief i2c读数据
 *
 * @param dev      bh1750 设备
 * @param i2c_addr i2c地址
 * @param data     待读取数据
 * @param len      读取长度
 * @return uint8_t 0: 成功; 其他: 失败
 * @note  平台相关
 */
uint8_t bh1750_i2c_read(bh1750_dev_t *dev, uint8_t i2c_addr, uint8_t *data, uint8_t len)
{
    return bh1750_platform_i2c_read(dev, i2c_addr, data, len);
}

bh1750_dev_t *bh1750_open(uint8_t i2c_addr)
{
    bh1750_dev_t *dev = (bh1750_dev_t *)malloc(sizeof(bh1750_dev_t));
    if (dev == NULL)
        return NULL;

    memset(dev, 0, sizeof(bh1750_dev_t));
    dev->i2c_addr = i2c_addr;

    if (bh1750_init(dev) != 0)
    {
        memset(dev, 0, sizeof(bh1750_dev_t));
        free(dev);
        return NULL;
    }

    return dev;
}

uint8_t bh1750_close(bh1750_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    if (bh1750_deinit(dev) != 0)
        return 2;

    memset(dev, 0, sizeof(bh1750_dev_t));
    free(dev);
    return 0;
}

uint8_t bh1750_raed(bh1750_dev_t *dev, bh1750_read_mode_t mode)
{

    uint8_t err = 0;

    if (dev == NULL)
        return 1;

    /* 发送开机指令 */
    err = bh1750_i2c_write(dev, dev->i2c_addr, BH1750_CMD_POWER_ON);
    if (err)
        return 2;

    /* 发送读取指令 */
    err = bh1750_i2c_write(dev, dev->i2c_addr, mode);
    if (err != 0)
        return 3;

    if (mode == BH1750_READ_CONTINUOUS_LOW_RES_MODE || mode == BH1750_READ_ONE_TIME_LOW_RES_MODE)
    {
        /* L : type: 12ms, max: 24ms */
        bh1750_delay_ms(30);
    }
    else
    {
        /* H : type: 120ms, max: 180ms */
        bh1750_delay_ms(200);
    }

    /* 读取数据 */
    err = bh1750_i2c_read(dev, dev->i2c_addr, dev->raw_data, 2);
    if (err)
        return 4;

    /* 连续模式手动关机 */
    if (mode == BH1750_READ_CONTINUOUS_LOW_RES_MODE || mode == BH1750_READ_CONTINUOUS_HIGH_RES_MODE ||
        mode == BH1750_READ_CONTINUOUS_HIGH_RES_MODE)
    {
        /* 发送关机指令 */
        err = bh1750_i2c_write(dev, dev->i2c_addr, BH1750_CMD_POWER_OFF);
        if (err)
            return 5;
    }

    /* 计算 lux */
    dev->lux = (uint16_t)((dev->raw_data[0] << 8) | dev->raw_data[1]) / 1.2f;

    return 0;
}
