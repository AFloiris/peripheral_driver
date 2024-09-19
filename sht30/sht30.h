#ifndef __AF_SHT30_H__
#define __AF_SHT30_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sht30_dev sht30_dev_t;

struct sht30_dev {
    uint8_t id;          /* 设备 id */
    uint8_t addr;        /* i2c 地址 */
    uint8_t data[6];     /* 接收到的数据 */
    float   temperature; /* 温度 */
    float   humidity;    /* 湿度 */
};

/**
 * @brief 打开 sht30 设备
 *
 * @param i2c   i2c 配置
 * @param addr  i2c 地址
 * @return sht30_dev_t* sht30 设备
 */
sht30_dev_t *sht30_open(uint8_t addr);

/**
 * @brief 关闭 sht30 设备
 *
 * @param dev  sht30 设备
 * @return uint8_t  0: 成功，其他: 失败
 */
uint8_t sht30_close(sht30_dev_t *dev);

/**
 * @brief 读取 sht30 数据
 *
 * @param dev  sht30 设备
 * @return uint8_t  0: 读取成功，其他: 读取失败
 */
uint8_t sht30_read(sht30_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* __AF_SHT30_H__ */
