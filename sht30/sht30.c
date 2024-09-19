#include "sht30.h"
#include "sht30_platform.h"
#include <stdlib.h>
#include <string.h>

static const uint16_t POLYNOMIAL = 0x131;

/**
 * @brief 初始化
 * @note  平台相关
 */
static uint8_t sht30_init(sht30_dev_t *dev) { return sht30_platform_init(dev); }

/**
 * @brief 反初始化
 * @note  平台相关
 */
static uint8_t sht30_deinit(sht30_dev_t *dev) { return sht30_platform_deinit(dev); }

/**
 * @brief I2C 读取
 * @note  平台相关
 * @param dev       sht30 设备
 * @param mem_addr  寄存器地址
 * @param data      数据
 * @param len       数据长度
 * @return 0 成功，其他失败
 */
static uint8_t sht30_i2c_read_addr16(sht30_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint16_t len)
{
    return sht30_platform_i2c_read_addr16(dev, dev->addr, mem_addr, data, len);
}

/**
 * @brief crc 校验
 * @note  驱动相关
 * @param data 读取到的数据
 * @param size 需要校验的数量
 * @param check 读取到的校对比验值
 * @return 校验结果，返回0成功，1失败
 */
static uint8_t sht30_check_crc(uint8_t *data, uint8_t size, uint8_t check)
{
    uint8_t crc = 0xFF;
    uint8_t bit = 0;

    for (uint8_t i = 0; i < size; ++i)
    {
        crc ^= data[i];
        for (bit = 8; bit > 0; --bit)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ POLYNOMIAL;
            else
                crc = (crc << 1);
        }
    }

    if (crc != check)
        return 1;
    else
        return 0;
}

sht30_dev_t *sht30_open(uint8_t addr)
{
    sht30_dev_t *dev = (sht30_dev_t *)malloc(sizeof(sht30_dev_t));
    if (dev == NULL)
        return NULL;

    memset(dev, 0, sizeof(sht30_dev_t));
    dev->addr = addr;

    if (sht30_init(dev) != 0)
    {
        free(dev);
        return NULL;
    }

    return dev;
}

uint8_t sht30_close(sht30_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    if (sht30_deinit(dev) != 0)
        return 2;

    memset(dev, 0, sizeof(sht30_dev_t));
    free(dev);
    return 0;
}

uint8_t sht30_read(sht30_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    uint8_t  ret = 0;
    uint16_t cmd = 0x2C06;

    /* 发送 0x2C 0x06 命令 读取 6 个字节的数据*/
    ret = sht30_i2c_read_addr16(dev, cmd, dev->data, 6);
    if (ret)
        return 1;

    /* 校验温度 */
    ret = sht30_check_crc(dev->data, 2, dev->data[2]);
    if (ret)
        return 2;

    /* 计算温度 */
    dev->temperature = (175.0f * (float)(dev->data[0] << 8 | dev->data[1]) / 65535.0f - 45.0f);

    /* 校验湿度 */
    ret = sht30_check_crc(dev->data + 3, 2, dev->data[5]);
    if (ret)
        return 3;

    /* 计算湿度 */
    dev->humidity = (100.0f * (float)(dev->data[3] << 8 | dev->data[4]) / 65535.0f);

    return 0;
}
