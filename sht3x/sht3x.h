#ifndef __AF_SHT3X_H__
#define __AF_SHT3X_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sht3x_dev sht3x_dev_t;

struct sht3x_dev {
    uint8_t id;          /* 设备 id */
    uint8_t i2c_addr;    /* i2c 地址 */
    uint8_t raw_data[6]; /* 原始数据 */
    float   temperature; /* 温度 */
    float   humidity;    /* 湿度 */
};

/**
 * @brief 打开 sht3x 设备
 *
 * @param i2c_addr      i2c 地址
 * @return sht3x_dev_t* sht3x 设备
 */
sht3x_dev_t *sht3x_open(uint8_t i2c_addr);

/**
 * @brief 关闭 sht3x 设备
 *
 * @param dev       sht3x 设备
 * @return uint8_t  0: 成功，其他: 失败
 */
uint8_t sht3x_close(sht3x_dev_t *dev);

/**
 * @brief 读取 sht3x 数据
 *
 * @param dev       sht3x 设备
 * @return uint8_t  0: 读取成功，其他: 读取失败
 */
uint8_t sht3x_read(sht3x_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* __AF_SHT3X_H__ */
