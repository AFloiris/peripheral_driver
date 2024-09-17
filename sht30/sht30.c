#include "af_i2c.h"
#include "sht30.h"
#include <stdlib.h>
#include <string.h>

static const uint16_t POLYNOMIAL = 0x131;

/**
 * @brief I2C 读取
 * @note  平台相关
 * @param dev  sht30 设备
 * @param data 数据
 * @param len  数据长度
 * @return 0 成功，其他失败
 */
static uint8_t sht30_i2c_read(sht30_dev_t *dev, uint8_t *data, uint16_t len)
{
    return af_i2c_read(&dev->i2c, dev->addr << 1 | 0x01, data, len);
}

/**
 * @brief I2C 写入
 * @note  平台相关
 * @param dev  sht30 设备
 * @param data 数据
 * @param len  数据长度
 * @return 0 成功，其他失败
 */
static uint8_t sht30_i2c_write(sht30_dev_t *dev, uint8_t *data, uint16_t len)
{
    return af_i2c_write(&dev->i2c, dev->addr << 1 | 0x00, data, len);
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

sht30_dev_t *sht30_open(af_i2c_t i2c, uint8_t addr)
{
    sht30_dev_t *dev = (sht30_dev_t *)malloc(sizeof(sht30_dev_t));
    if (dev == NULL)
        return NULL;

    memset(dev, 0, sizeof(sht30_dev_t));
    dev->i2c  = i2c;
    dev->addr = addr;

    if (dev->i2c.init == 0 && (af_i2c_init(&dev->i2c) != 0))
    {
        free(dev);
        return NULL;
    }

    return dev;
}

void sht30_close(sht30_dev_t *dev)
{
    if (dev == NULL)
        return;

    af_i2c_init(&dev->i2c);
    memset(dev, 0, sizeof(sht30_dev_t));
    free(dev);
}

uint8_t sht30_read(sht30_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    uint16_t ret    = 0;
    uint8_t  cmd[2] = {0x2C, 0x06};

    /* 发送 0x2C 0x06 命令 */
    ret = sht30_i2c_write(dev, cmd, 2);
    if (ret)
        return 2;

    /* 读取 6 个字节的数据 */
    ret = sht30_i2c_read(dev, dev->data, 6);
    if (ret)
        return 3;

    /* 校验温度 */
    ret = sht30_check_crc(dev->data, 2, dev->data[2]);
    if (ret)
        return 4;

    /* 计算温度 */
    dev->temperature = (175.0f * (float)(dev->data[0] << 8 | dev->data[1]) / 65535.0f - 45.0f);

    /* 校验湿度 */
    ret = sht30_check_crc(dev->data + 3, 2, dev->data[5]);
    if (ret)
        return 5;

    /* 计算湿度 */
    dev->humidity = (100.0f * (float)(dev->data[3] << 8 | dev->data[4]) / 65535.0f);

    return 0;
}
