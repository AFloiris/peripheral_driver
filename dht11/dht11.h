#ifndef __AF_DHT11_H__
#define __AF_DHT11_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dht11_dev dht11_dev_t;

struct dht11_dev {       /* dht11 设备 */
    uint8_t id;          /* 设备 id */
    uint8_t data[5];     /* 原始数据 */
    float   temperature; /* 温度 */
    float   humidity;    /* 湿度 */
};

/**
 * @brief 打开 dht11 设备
 *
 * @return dht11_dev_t* dht11 设备
 */
dht11_dev_t *dht11_open(void);

/**
 * @brief 关闭 dht11 设备
 *
 * @param dev dht11 设备
 */
uint8_t dht11_close(dht11_dev_t *dev);

/**
 * @brief 读取 dht11 数据
 *
 * @param dev dht11 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t dht11_read(dht11_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* __AF_DHT11_H__ */
