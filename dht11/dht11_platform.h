#ifndef __AF_DHT11_PLATFORM_H__
#define __AF_DHT11_PLATFORM_H__

#include "dht11.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief dht11 平台接口相关初始化,如 gpio,时钟
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t dht11_platform_init(dht11_dev_t *dev);

/**
 * @brief dht11 平台接口相关资源释放
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t dht11_platform_deinit(dht11_dev_t *dev);

/**
 * @brief dht11 平台接口, gpio读取数据
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分; 注意切换为读模式
 */
uint8_t dht11_platform_gpio_read(dht11_dev_t *dev, uint8_t *value);

/**
 * @brief dht11 平台接口, gpio写入数据
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分; 注意切换为写模式
 */
uint8_t dht11_platform_gpio_write(dht11_dev_t *dev, uint8_t value);

/**
 * @brief dht11 平台接口, 时钟延时
 */
void dht11_platform_delay_ms(uint32_t ms);

/**
 * @brief dht11 平台接口, 时钟延时
 */
void dht11_platform_delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* __AF_DHT11_PLATFORM_H__ */
