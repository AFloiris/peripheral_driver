#ifndef __AF_I2C_H__
#define __AF_I2C_H__

#include "main.h"

typedef struct af_i2c         af_i2c_t;
typedef enum af_mem_addr_size af_mem_addr_size_t;

enum af_mem_addr_size {
    MEM_ADDR_SIZE_8BIT  = 0x00000001U,
    MEM_ADDR_SIZE_16BIT = 0x00000010U,
};

struct af_i2c {
    uint8_t init; /* 初始化 */
#if defined(USE_HAL_DRIVER)
    I2C_HandleTypeDef *hi2c;
    I2C_InitTypeDef    i2c_init;
#endif
};

/**
 * @brief i2c 初始化
 *
 * @param i2c i2c 设备
 * @return uint8_t 0:成功 其他:失败
 */
uint8_t af_i2c_init(af_i2c_t *i2c);

/**
 * @brief i2c 反初始化
 *
 * @param i2c i2c 设备
 * @return uint8_t 0:成功 其他:失败
 */
uint8_t af_i2c_deinit(af_i2c_t *i2c);

/**
 * @brief i2c 写入
 *
 * @param i2c  i2c 设备
 * @param addr 设备地址
 * @param data 写入数据
 * @param len  写入数据长度
 * @return uint8_t 0:成功 其他:失败
 */
uint8_t af_i2c_write(af_i2c_t *i2c, uint8_t addr, uint8_t *data, uint16_t len);

/**
 * @brief i2c 读取
 *
 * @param i2c  i2c 设备
 * @param addr 设备地址
 * @param data 读取数据
 * @param len  读取数据长度
 * @return uint8_t 0:成功 其他:失败
 */
uint8_t af_i2c_read(af_i2c_t *i2c, uint8_t addr, uint8_t *data, uint16_t len);

/**
 * @brief i2c 内存写入
 *
 * @param i2c  i2c 设备
 * @param addr 设备地址
 * @param mem_addr 内存地址
 * @param mem_addr_size 内存地址长度
 * @param data 写入数据
 * @param len  写入数据长度
 * @return uint8_t 0:成功 其他:失败
 */
uint8_t af_i2c_mem_write(af_i2c_t *i2c, uint8_t addr, uint16_t mem_addr, af_mem_addr_size_t mem_addr_size,
                         uint8_t *data, uint16_t len);

/**
 * @brief i2c 内存读取
 *
 * @param i2c  i2c 设备
 * @param addr 设备地址
 * @param mem_addr 内存地址
 * @param mem_addr_size 内存地址长度
 * @param data 写入数据
 * @param len  写入数据长度
 * @return uint8_t 0:成功 其他:失败
 */
uint8_t af_i2c_mem_read(af_i2c_t *i2c, uint8_t addr, uint16_t mem_addr, af_mem_addr_size_t mem_addr_size, uint8_t *data,
                        uint16_t len);

#endif /* __AF_I2C_H__ */
