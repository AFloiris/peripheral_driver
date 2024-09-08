#ifndef __AF_AT24C02_H__
#define __AF_AT24C02_H__

#include "af_i2c.h"
#include "main.h"

typedef struct at24c02_dev at24c02_dev_t;

struct at24c02_dev {
    uint8_t  addr;
    af_i2c_t i2c;
};

/**
 * @brief 打开 at24c02 设备
 *
 * @param i2c   i2c 配置
 * @param addr  i2c 地址
 * @return at24c02_dev_t* at24c02 设备
 */
at24c02_dev_t *at24c02_open(af_i2c_t i2c, uint8_t addr);

/**
 * @brief 关闭 at24c02 设备
 *
 * @param dev  at24c02 设备
 */
void at24c02_close(at24c02_dev_t *dev);

/**
 * @brief at24c02 设备页写入
 *
 * @param dev  at24c02 设备
 * @param mem_addr  at24c02 设备的目标地址
 * @param data  数据
 * @param len  数据长度
 * @return uint8_t  0: 写入成功，其他: 写入失败
 */
uint8_t at24c02_page_write(at24c02_dev_t *dev, uint8_t mem_addr, uint8_t *data, uint8_t len);

/**
 * @brief at24c02 设备字节写入
 *
 * @param dev  at24c02 设备
 * @param mem_addr  at24c02 设备的目标地址
 * @param data  数据
 * @return uint8_t  0: 写入成功，其他: 写入失败
 */
uint8_t at24c02_byte_write(at24c02_dev_t *dev, uint8_t mem_addr, uint8_t data);

/**
 * @brief at24c02 设备随机读取
 *
 * @param dev  at24c02 设备
 * @param mem_addr  at24c02 设备的目标地址
 * @param data  数据
 * @return uint8_t  0: 读取成功，其他: 读取失败
 */
uint8_t at24c02_random_read(at24c02_dev_t *dev, uint8_t mem_addr, uint8_t *data);

/**
 * @brief at24c02 设备当前地址读取
 *
 * @param dev  at24c02 设备
 * @param data  数据
 * @return uint8_t  0: 读取成功，其他: 读取失败
 */
uint8_t at24c02_current_address_read(at24c02_dev_t *dev, uint8_t *data);

#endif