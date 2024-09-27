#ifndef __AF_SHT3X_PLATFORM_H__
#define __AF_SHT3X_PLATFORM_H__

#include "sht3x.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  sht3x 平台接口, 相关初始化,如 i2c,gpio,时钟
 *
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t sht3x_platform_init(sht3x_dev_t *dev);

/**
 * @brief  sht3x 平台接口, 相关资源释放
 *
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t sht3x_platform_deinit(sht3x_dev_t *dev);

/**
 * @brief  sht3x 平台接口, i2c 读数据
 *
 * @param dev       sht3x 设备
 * @param i2c_addr  i2c 设备地址
 * @param mem_addr  存储器地址
 * @param data      待读数据
 * @param len       待读数据长度
 * @return uint8_t  0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t sht3x_platform_i2c_read_addr16(sht3x_dev_t *dev, uint16_t i2c_addr, uint16_t mem_addr, uint8_t *data,
                                       uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* __AF_SHT3X_PLATFORM_H__ */
