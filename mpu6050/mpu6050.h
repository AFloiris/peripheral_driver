#ifndef __AF_MPU6050_H__
#define __AF_MPU6050_H__

#include <stdint.h>>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mpu6050_dev mpu6050_dev_t;

struct mpu6050_dev {
    uint8_t id;       /* 设备 id */
    uint8_t i2c_addr; /* i2c 地址 */
    int16_t x_accel;  /* X轴上的加速度值 */
    int16_t x_gyro;   /* X轴上的角速度值 */
    int16_t y_accel;  /* Y轴上的加速度值 */
    int16_t y_gyro;   /* Y轴上的角速度值 */
    int16_t z_accel;  /* Z轴上的加速度值 */
    int16_t z_gyro;   /* Z轴上的角速度值 */
};

/**
 * @brief 打开 mpu6050 设备
 *
 * @param addr  i2c 地址
 * @return mpu6050_dev_t* mpu6050 设备
 */
mpu6050_dev_t *mpu6050_open(uint8_t addr);

/**
 * @brief 关闭 mpu6050 设备
 *
 * @param dev  mpu6050 设备
 * @return uint8_t  0: 成功,其他: 失败
 */
uint8_t mpu6050_close(mpu6050_dev_t *dev);

/**
 * @brief 读取 mpu6050 数据
 *
 * @param dev  mpu6050 设备
 * @return uint8_t  0: 读取成功，其他: 读取失败
 */
uint8_t mpu6050_read(mpu6050_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* __AF_MPU6050_H__ */
