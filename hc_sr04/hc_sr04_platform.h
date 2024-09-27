#ifndef __AF_HC_SR04_PLATFORM_H__
#define __AF_HC_SR04_PLATFORM_H__

#include "hc_sr04.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief hc_sr04 平台接口相关初始化,如 gpio,时钟
 *
 * @return uint8_t 0: 成功; 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t hc_sr04_platform_init(hc_sr04_dev_t *dev);

/**
 * @brief hc_sr04 平台接口相关资源释放
 *
 * @return uint8_t 0: 成功; 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t hc_sr04_platform_deinit(hc_sr04_dev_t *dev);

/**
 * @brief hc_sr04 平台接口, trig 引脚写入
 *
 * @param dev      hc_sr04 设备
 * @param value    写入值
 * @return uint8_t 0: 成功; 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t hc_sr04_platform_trig_gpio_write(hc_sr04_dev_t *dev, uint8_t value);

/**
 * @brief hc_sr04 平台接口, echo 引脚读取
 *
 * @param dev      hc_sr04 设备
 * @param value    读取值
 * @return uint8_t 0: 成功; 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t hc_sr04_platform_echo_gpio_read(hc_sr04_dev_t *dev, uint8_t *value);

/**
 * @brief hc_sr04 平台接口, 开始计时
 *
 * @param dev      hc_sr04 设备
 * @return uint8_t 0: 成功; 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t hc_sr04_platform_start_clock(hc_sr04_dev_t *dev);

/**
 * @brief hc_sr04 平台接口, 停止计时
 *
 * @param dev      hc_sr04 设备
 * @return uint8_t 0: 成功; 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t hc_sr04_platform_stop_clock(hc_sr04_dev_t *dev);

/**
 * @brief hc_sr04 平台接口, 获取计时时间(us)
 *
 * @param dev      hc_sr04 设备
 * @param us       计时时间(us)
 * @return uint8_t 0: 成功; 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t hc_sr04_platform_get_clock_us(hc_sr04_dev_t *dev, uint32_t *us);

/**
 * @brief hc_sr04 平台接口, 时钟延时
 */
uint8_t hc_sr04_platform_delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* __AF_HC_SR04_PLATFORM_H__ */
