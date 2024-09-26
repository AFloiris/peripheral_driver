#ifndef __AF_BH1750_PLATFORM_H__
#define __AF_BH1750_PLATFORM_H__

#include "bh1750.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief bh1750 平台接口, 相关初始化,如 i2c,gpio,时钟
 *
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t bh1750_platform_init(bh1750_dev_t *dev);

/**
 * @brief bh1750 平台接口, 相关资源释放
 *
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t bh1750_platform_deinit(bh1750_dev_t *dev);

/**
 * @brief bh1750 平台接口, i2c 写数据
 *
 * @param dev       bh1750 设备
 * @param i2c_addr  i2c 设备地址
 * @param data      待写入数据
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t bh1750_platform_i2c_write(bh1750_dev_t *dev, uint8_t i2c_addr, uint8_t data);

/**
 * @brief bh1750 平台接口, i2c 读数据
 *
 * @param dev       bh1750 设备
 * @param i2c_addr  i2c 设备地址
 * @param data      待读取数据
 * @param len       待读取数据长度
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t bh1750_platform_i2c_read(bh1750_dev_t *dev, uint8_t i2c_addr, uint8_t *data, uint8_t len);

/**
 * @brief bh1750 平台接口, 延时函数
 *
 * @param ms        延时时间(ms)
 * @return uint8_t  0: 成功, 其他: 失败
 */
uint8_t bh1750_platform_delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* __AF_BH1750_PLATFORM_H__ */
