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
static void sht30_i2c_read(sht30_dev_t *dev, uint8_t reg, uint8_t *data, uint16_t len) {

#if defined(USE_HAL_DRIVER)
    HAL_I2C_Mem_Read(dev->i2c.hi2c, dev->addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
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
static void sht30_i2c_write(sht30_dev_t *dev, uint8_t reg, uint8_t *data, uint16_t len) {

#if defined(USE_HAL_DRIVER)
    HAL_I2C_Mem_Write(dev->i2c.hi2c, dev->addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
#endif
}

sht30_dev_t *sht30_open(sht30_i2c_t i2c, uint8_t addr) {
    sht30_dev_t *dev = (sht30_dev_t *) malloc(sizeof(sht30_dev_t));
    if(dev != NULL) {
        memset(dev, 0, sizeof(sht30_dev_t));
        dev->i2c  = i2c;
        dev->addr = addr;
    }
    return dev;
}
void         sht30_close(sht30_dev_t *dev);
uint8_t      sht30_read(sht30_dev_t *dev);