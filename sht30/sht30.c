#include "sht30.h"
#include <stdlib.h>
#include <string.h>
/**
 * @brief I2C 读取
 * @note  平台相关
 * @param dev  sht30 设备
 * @param reg  寄存器
 * @param data 数据
 * @param len  数据长度
 */
static void sht30_i2c_read(sht30_dev_t *dev, uint8_t reg, uint8_t *data, uint16_t len)
{

#if defined(USE_HAL_DRIVER)
    HAL_I2C_Mem_Read(dev->i2c.hi2c, dev->addr << 1 | 0x01, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
#endif
}

/**
 * @brief I2C 写入
 * @note  平台相关
 * @param dev  sht30 设备
 * @param reg  寄存器
 * @param data 数据
 * @param len  数据长度
 */
static void sht30_i2c_write(sht30_dev_t *dev, uint8_t reg, uint8_t *data, uint16_t len)
{

#if defined(USE_HAL_DRIVER)
    HAL_I2C_Mem_Write(dev->i2c.hi2c, dev->addr << 1 | 0x00, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
#endif
}

sht30_dev_t *sht30_open(sht30_i2c_t i2c, uint8_t addr)
{
    sht30_dev_t *dev = (sht30_dev_t *)malloc(sizeof(sht30_dev_t));
    if (dev != NULL)
    {
        memset(dev, 0, sizeof(sht30_dev_t));
        dev->i2c = i2c;
        dev->addr = addr;
    }
    return dev;
}

void sht30_close(sht30_dev_t *dev)
{
    if (dev == NULL)
    {
        return;
    }
    // maybe need to free iic config here

    free(dev);
}

/**
 * @brief 校验数据准确性
 * @param data 读取到的数据
 * @param nbrOfBytes 需要校验的数量
 * @param checkSum 读取到的校对比验值
 * @return 校验结果，返回0成功，1失败
 */
static uint8_t sht30_check_crc(uint8_t *data, uint8_t nbrOfBytes, uint8_t checkSum)
{
    uint8_t crc = 0xFF;
    uint8_t bit = 0;
    uint8_t byteCtr;
    const int16_t POLYNOMIAL = 0x131;
    // calculates 8-Bit checksum with given polynomial
    for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
    {
        crc ^= (data[byteCtr]);
        for (bit = 8; bit > 0; --bit)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ POLYNOMIAL;
            else
                crc = (crc << 1);
        }
    }

    if (crc != checkSum)
        return 1;
    else
        return 0;
}

/**
 * @brief 计算温度
 * @param data 读取到的原始温度数据
 * @return 计算后的温度值
 */
static float sht30_calc_temperature(uint16_t data)
{
    float temperature = 0;

    data &= ~0x0003;
    temperature = (175 * (float)data / 65535 - 45); // T = -45 + 175 * rawValue / (2^16-1)

    return temperature;
}

/**
 * @brief 计算湿度
 * @param data 读取到的原始湿度数据
 * @return 计算后的湿度值
 */
static float sht30_calc_humidity(uint16_t data)
{
    float humidity = 0;

    data &= ~0x0003;
    humidity = (100 * (float)data / 65535); // RH = rawValue / (2^16-1) * 10

    return humidity;
}

uint8_t sht30_read(sht30_dev_t *dev)
{
    // send 0xE0 0x00 first,then read iic data[6]
    // 0-2 is temperature,3-5 is humidity
    uint16_t ret;
    uint8_t check_temp_buffer[3] = {0};

    uint8_t send_data[2] = {0xE0, 0x00};
    sht30_i2c_write(dev, NULL, send_data, 2);

    // read iic data here

    check_temp_buffer[0] = dev->data[0];
    check_temp_buffer[1] = dev->data[1];
    check_temp_buffer[2] = dev->data[2];

    ret = sht30_check_crc(check_temp_buffer, 2, check_temp_buffer[2]);
    if (ret)
        return 1;
    dev->temperature = sht30_calc_temperature((uint16_t)(check_temp_buffer[0] << 8 | check_temp_buffer[1]));

    check_temp_buffer[0] = dev->data[3];
    check_temp_buffer[1] = dev->data[4];
    check_temp_buffer[2] = dev->data[5];

    ret = sht30_check_crc(check_temp_buffer, 2, check_temp_buffer[2]);
    if (ret)
        return 2;
    dev->humidity = sht30_calc_humidity((uint16_t)(check_temp_buffer[0] << 8 | check_temp_buffer[1]));

    return 0;
}