#include "mpu6050.h"
#include "mpu6050_platform.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief 命令定义
 */
#define MPU6050_REG_SMPLRT_DIV   0x19 /*陀螺仪采样率，典型值：0x07(125Hz)*/
#define MPU6050_REG_CONFIG       0x1A /*低通滤波频率，典型值：0x06(5Hz)*/
#define MPU6050_REG_GYRO_CONFIG  0x1B /*陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)*/
#define MPU6050_REG_ACCEL_CONFIG 0x1C /*加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)*/
#define MPU6050_REG_ACCEL_X_H    0x3B /*存储X轴加速度数据的高8位数据寄存器地址*/
#define MPU6050_REG_ACCEL_X_L    0x3C /*存储X轴加速度数据的低8位数据寄存器地址*/
#define MPU6050_REG_ACCEL_Y_H    0x3D /*存储Y轴加速度数据的高8位数据寄存器地址*/
#define MPU6050_REG_ACCEL_Y_L    0x3E /*存储Y轴加速度数据的低8位数据寄存器地址*/
#define MPU6050_REG_ACCEL_Z_H    0x3F /*存储Z轴加速度数据的高8位数据寄存器地址*/
#define MPU6050_REG_ACCEL_Z_L    0x40 /*存储Z轴加速度数据的低8位数据寄存器地址*/
#define MPU6050_REG_TEMP_OUT_H   0x41 /*存储温度数据的高8位数据寄存器地址*/
#define MPU6050_REG_TEMP_OUT_L   0x42 /*存储温度数据的低8位数据寄存器地址*/
#define MPU6050_REG_GYRO_X_H     0x43 /*存储X轴角速度数据的高8位数据寄存器地址*/
#define MPU6050_REG_GYRO_X_L     0x44 /*存储X轴角速度数据的低8位数据寄存器地址*/
#define MPU6050_REG_GYRO_Y_H     0x45 /*存储Y轴角速度数据的高8位数据寄存器地址*/
#define MPU6050_REG_GYRO_Y_L     0x46 /*存储Y轴角速度数据的低8位数据寄存器地址*/
#define MPU6050_REG_GYRO_Z_H     0x47 /*存储Z轴角速度数据的高8位数据寄存器地址*/
#define MPU6050_REG_GYRO_Z_L     0x48 /*存储Z轴角速度数据的低8位数据寄存器地址*/
#define MPU6050_REG_PWR_MGMT_1   0x6B /*电源管理，典型值：0x00(正常启用)*/
#define MPU6050_REG_PWR_MGMT_2   0x6C /* 控制6轴传感器分别是否待机*/
#define MPU6050_REG_WHO_AM_I     0x75 /* IIC地址寄存器(默认数值0x68，只读)*/
#define MPU6050_REG_SlaveAddress 0xD0 /* IIC写入时的地址字节数据，+1为读取*/

#define MPU6050_AFS_2G  16384.0 /* 加速度计算相关系数*/
#define MPU6050_AFS_4G  8192.0
#define MPU6050_AFS_8G  4096.0
#define MPU6050_AFS_16G 2048.0

#define MPU6050_GFS_250DPS  131.0 /* 角速度计算相关系数*/
#define MPU6050_GFS_500DPS  65.5
#define MPU6050_GFS_1000DPS 32.8
#define MPU6050_GFS_2000DPS 16.4

/**
 * @brief 初始化
 * @note  平台相关
 */
static uint8_t mpu6050_init(mpu6050_dev_t *dev) { return mpu6050_platform_init(dev); };

/**
 * @brief 反初始化
 * @note  平台相关
 */
static uint8_t mpu6050_deinit(mpu6050_dev_t *dev) { return mpu6050_platform_deinit(dev); }

/**
 * @brief mpu6050 i2c 写入
 *
 * @param dev           mpu6050设备
 * @param reg_addr      写入寄存器地址
 * @param data          写入数据
 * @return uint8_t  0:成功，其他：失败
 *
 * @note 平台相关
 */
static uint8_t mpu6050_reg_write(mpu6050_dev_t *dev, uint8_t reg_addr, uint8_t data)
{
    return mpu6050_platform_i2c_write(dev, (dev->i2c_addr << 1) | 0x00, reg_addr, &data, 1);
}

/**
 * @brief mpu6050 i2c 读取
 *
 * @param dev           mpu6050设备
 * @param reg_addr      读取寄存器地址
 * @param data          读取数据
 * @param len           读取长度
 * @return uint8_t  0:成功，其他：失败
 *
 * @note 平台相关
 */
static uint8_t mpu6050_reg_read(mpu6050_dev_t *dev, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    return mpu6050_platform_i2c_read(dev, (dev->i2c_addr << 1) | 0x01, reg_addr, data, len);
}

static void mpu6050_start_cmd(mpu6050_dev_t *dev)
{
    /* 退出睡眠模式，选择陀螺仪时钟 */
    mpu6050_reg_write(dev, MPU6050_REG_PWR_MGMT_1, 0x01);

    /* 6轴均不待机 */
    mpu6050_reg_write(dev, MPU6050_REG_PWR_MGMT_2, 0x00);

    /* 采样分频为10 */
    mpu6050_reg_write(dev, MPU6050_REG_SMPLRT_DIV, 0x09);

    /* 滤波参数最大 */
    mpu6050_reg_write(dev, MPU6050_REG_CONFIG, 0x06);

    /* 设置陀螺仪量程 */
    mpu6050_reg_write(dev, MPU6050_REG_GYRO_CONFIG, 0x00 | (dev->gyro_range << 3));

    /* 设置加速度计量程 */
    mpu6050_reg_write(dev, MPU6050_REG_ACCEL_CONFIG, 0x00 | (dev->accel_range << 3));
}

static float mpu6050_calc_accel(int16_t raw_value, uint8_t accel_range)
{
    switch (accel_range)
    {
    case 0x00:
        return raw_value / MPU6050_AFS_2G;
    case 0x01:
        return raw_value / MPU6050_AFS_4G;
    case 0x02:
        return raw_value / MPU6050_AFS_8G;
    case 0x03:
        return raw_value / MPU6050_AFS_16G;
    default:
        return raw_value / MPU6050_AFS_16G;
    }
}

static float mpu6050_calc_gyro(int16_t raw_value, uint8_t gyro_range)
{
    switch (gyro_range)
    {
    case 0x00:
        return raw_value / MPU6050_GFS_250DPS;
    case 0x01:
        return raw_value / MPU6050_GFS_500DPS;
    case 0x02:
        return raw_value / MPU6050_GFS_1000DPS;
    case 0x03:
        return raw_value / MPU6050_GFS_2000DPS;
    default:
        return raw_value / MPU6050_GFS_2000DPS;
    }
}

mpu6050_dev_t *mpu6050_open(uint8_t accel_range, uint8_t gyro_range, uint8_t i2c_addr)
{
    if (accel_range > 0x03 || gyro_range > 0x03)
        return NULL;

    mpu6050_dev_t *dev = (mpu6050_dev_t *)malloc(sizeof(mpu6050_dev_t));
    if (dev == NULL)
        return NULL;

    memset(dev, 0, sizeof(mpu6050_dev_t));
    dev->accel_range = accel_range;
    dev->gyro_range  = gyro_range;
    dev->i2c_addr    = i2c_addr;

    if (mpu6050_init(dev))
    {
        free(dev);
        return NULL;
    }

    mpu6050_start_cmd(dev);

    return dev;
}

uint8_t mpu6050_close(mpu6050_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    if (mpu6050_deinit(dev))
        return 2;

    memset(dev, 0, sizeof(mpu6050_dev_t));
    free(dev);
    return 0;
}

uint8_t mpu6050_get_id(mpu6050_dev_t *dev, uint8_t *id)
{
    if (dev == NULL)
        return 1;

    uint8_t ret;
    ret = mpu6050_reg_read(dev, MPU6050_REG_WHO_AM_I, id, 1);
    if (ret)
        return 2;

    return 0;
}

uint8_t mpu6050_read_data(mpu6050_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    uint8_t  ret = 0;
    uint16_t temp_data;

    ret = mpu6050_reg_read(dev, MPU6050_REG_ACCEL_X_H, dev->raw_data, 14);
    if (ret)
        return 2;

    /* 处理加速度计数据 */
    temp_data    = (int16_t)(dev->raw_data[0] << 8 | dev->raw_data[1]);
    dev->x_accel = mpu6050_calc_accel(temp_data, dev->accel_range);

    temp_data    = (int16_t)(dev->raw_data[2] << 8 | dev->raw_data[3]);
    dev->y_accel = mpu6050_calc_accel(temp_data, dev->accel_range);

    temp_data    = (int16_t)(dev->raw_data[4] << 8 | dev->raw_data[5]);
    dev->z_accel = mpu6050_calc_accel(temp_data, dev->accel_range);

    /* 处理温度数据 */
    temp_data = (int16_t)(dev->raw_data[6] << 8 | dev->raw_data[7]);
    dev->temp = (float)temp_data / 340.0f + 36.53;

    /* 处理陀螺仪数据 */
    temp_data   = (int16_t)(dev->raw_data[8] << 8 | dev->raw_data[9]);
    dev->x_gyro = mpu6050_calc_gyro(temp_data, dev->gyro_range);

    temp_data   = (int16_t)(dev->raw_data[10] << 8 | dev->raw_data[11]);
    dev->y_gyro = mpu6050_calc_gyro(temp_data, dev->gyro_range);

    temp_data   = (int16_t)(dev->raw_data[12] << 8 | dev->raw_data[13]);
    dev->z_gyro = mpu6050_calc_gyro(temp_data, dev->gyro_range);
    return 0;
}
