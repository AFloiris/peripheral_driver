#ifndef __AF_AT24CXX_H__
#define __AF_AT24CXX_H__

#include <stdlib.h>
#include <string.h>

#include "af_delay.h"
#include "af_i2c.h"

#include "main.h"

typedef struct at24cxx_dev at24cxx_dev_t;
typedef enum at24cxx_type  at24cxx_type_t;

enum at24cxx_type {
    AT24C01  = 128,
    AT24C02  = 256,
    AT24C04  = 512,
    AT24C08  = 1024,
    AT24C16  = 2048,
    AT24C32  = 4096,
    AT24C64  = 8192,
    AT24C128 = 16384,
    AT24C256 = 32768,
    AT24C512 = 65536,
    AT24CM01 = 131072,
    AT24CM02 = 262144,
};

struct at24cxx_dev {
    uint8_t        addr;
    af_i2c_t       i2c;
    at24cxx_type_t type;
};

/**
 * @brief 打开 at24cxx 设备
 *
 * @param i2c   i2c 配置
 * @param addr  i2c 地址
 * @return at24cxx_dev_t* at24cxx 设备
 */
at24cxx_dev_t *at24cxx_open(af_i2c_t i2c, at24cxx_type_t type, uint8_t addr);

/**
 * @brief 关闭 at24cxx 设备
 *
 * @param dev  at24cxx 设备
 */
void at24cxx_close(at24cxx_dev_t *dev);

/**
 * @brief at24cxx 设备写入
 *
 * @param dev  at24cxx 设备
 * @param mem_addr  at24cxx 设备的目标地址
 * @param data  数据
 * @param len  数据长度
 * @return uint8_t  0: 写入成功，其他: 写入失败
 */
uint8_t at24cxx_write(at24cxx_dev_t *dev, uint32_t mem_addr, uint8_t *data, uint8_t len);

/**
 * @brief at24cxx 设备读取
 *
 * @param dev  at24cxx 设备
 * @param mem_addr  at24cxx 设备的目标地址
 * @param data  数据
 * @param len  数据长度
 * @return uint8_t  0: 读取成功，其他: 读取失败
 */
uint8_t at24cxx_read(at24cxx_dev_t *dev, uint32_t mem_addr, uint8_t *data, uint8_t len);

#endif