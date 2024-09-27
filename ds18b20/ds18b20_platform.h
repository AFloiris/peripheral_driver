#ifndef __AF_DS18B20_PLATFORM_H__
#define __AF_DS18B20_PLATFORM_H__

#include "ds18b20.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ds18b20 平台接口相关初始化,如 gpio,时钟
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t ds18b20_platform_init(ds18b20_dev_t *dev);

/**
 * @brief ds18b20 平台接口相关资源释放
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t ds18b20_platform_deinit(ds18b20_dev_t *dev);

/**
 * @brief ds18b20 平台接口, gpio读取数据
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分; 注意切换为读模式
 */
uint8_t ds18b20_platform_gpio_read(ds18b20_dev_t *dev, uint8_t *value);

/**
 * @brief ds18b20 平台接口, gpio写入数据
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分; 注意切换为写模式
 */
uint8_t ds18b20_platform_gpio_write(ds18b20_dev_t *dev, uint8_t value);

/**
 * @brief ds18b20 平台接口, 时钟延时
 */
uint8_t ds18b20_platform_delay_ms(uint32_t ms);

/**
 * @brief ds18b20 平台接口, 时钟延时
 */
uint8_t ds18b20_platform_delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* __AF_DS18B20_PLATFORM_H__ */
