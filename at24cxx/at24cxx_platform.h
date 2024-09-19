#ifndef __AF_AT24CXX_PLATFORM_H__
#define __AF_AT24CXX_PLATFORM_H__

#include "at24cxx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief at24cxx 平台接口, 相关初始化,如 i2c,gpio,时钟
 *
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t at24cxx_platform_init(at24cxx_dev_t *dev);

/**
 * @brief at24cxx 平台接口, 相关资源释放
 *
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t at24cxx_platform_deinit(at24cxx_dev_t *dev);

/**
 * @brief at24cxx 平台接口, i2c 写数据
 *
 * @param dev at24cxx 设备
 * @param addr i2c 设备地址
 * @param mem_addr 存储器地址
 * @param data 待写入数据
 * @param len 待写入数据长度
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t at24cxx_platform_i2c_write(at24cxx_dev_t *dev, uint8_t addr, uint8_t mem_addr, uint8_t *data, uint16_t len);

/**
 * @brief at24cxx 平台接口, i2c 读数据
 *
 * @param dev  at24cxx 设备
 * @param addr  i2c 设备地址
 * @param mem_addr  存储器地址
 * @param data  待读数据
 * @param len   待读数据长度
 * @return uint8_t  0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t at24cxx_platform_i2c_read(at24cxx_dev_t *dev, uint8_t addr, uint8_t mem_addr, uint8_t *data, uint16_t len);

/**
 * @brief at24cxx 平台接口, i2c 写数据, 带地址16位
 *
 * @param dev at24cxx 设备
 * @param addr i2c 设备地址
 * @param mem_addr 存储器地址
 * @param data 待写入数据
 * @param len 待写入数据长度
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t at24cxx_platform_i2c_write_addr16(at24cxx_dev_t *dev, uint8_t addr, uint16_t mem_addr, uint8_t *data,
                                          uint16_t len);

/**
 * @brief at24cxx 平台接口, i2c 读数据, 带地址16位
 *
 * @param dev  at24cxx 设备
 * @param addr  i2c 设备地址
 * @param mem_addr  存储器地址
 * @param data  待读数据
 * @param len   待读数据长度
 * @return uint8_t  0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t at24cxx_platform_i2c_read_addr16(at24cxx_dev_t *dev, uint8_t addr, uint16_t mem_addr, uint8_t *data,
                                         uint16_t len);

/**
 * @brief at24cxx 平台接口, 时钟延时
 */
void at24cxx_platform_delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* __AF_AT24CXX_PLATFORM_H__ */
