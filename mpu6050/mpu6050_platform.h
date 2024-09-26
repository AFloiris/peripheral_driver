#ifndef __AF_MPU6050_PLATFORM_H__
#define __AF_MPU6050_PLATFORM_H__

#include "mpu6050.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief mpu6050 平台接口, 相关初始化,如 i2c,gpio,时钟
 *
 * @param dev      mpu6050 设备
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t mpu6050_platform_init(mpu6050_dev_t *dev);

/**
 * @brief mpu6050 平台接口, 相关资源释放
 *
 * @param dev      mpu6050 设备
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t mpu6050_platform_deinit(mpu6050_dev_t *dev);

/**
 * @brief mpu6050 平台接口, i2c 写数据
 *
 * @param dev      mpu6050 设备
 * @param i2c_addr i2c 设备地址
 * @param reg_addr 存储器地址
 * @param data     待写入数据
 * @param len      数据长度
 * @return uint8_t 0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t mpu6050_platform_i2c_write(mpu6050_dev_t *dev, uint8_t i2c_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
 * @brief mpu6050 平台接口, i2c 读数据
 *
 * @param dev      mpu6050 设备
 * @param i2c_addr i2c 设备地址
 * @param reg_addr 存储器地址
 * @param data     待读数据
 * @param len      数据长度
 * @return uint8_t  0: 成功, 其他: 失败
 * @note 如有多个相同设备,可根据dev->id区分
 */
uint8_t mpu6050_platform_i2c_read(mpu6050_dev_t *dev, uint8_t i2c_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /*__AF_MPU6050_PLATFORM_H__*/
