#ifndef __AF_DHT11_H__
#define __AF_DHT11_H__

#include "af_gpio.h"
#include "main.h"

typedef struct dht11_device dht11_device_t;

struct dht11_device {      /* DHT11 设备 */
    uint8_t   data[5];     /* 接收到的数据 */
    float     temperature; /* 温度 */
    float     humidity;    /* 湿度 */
    af_gpio_t gpio;        /* 引脚配置 */
};

/**
 * @brief 打开 DHT11 设备
 *
 * @param gpio DHT11 引脚配置
 * @return dht11_device_t* DHT11 设备
 */
dht11_device_t *dht11_open(af_gpio_t gpio);

/**
 * @brief 关闭 DHT11 设备
 *
 * @param dev DHT11 设备
 */
void dht11_close(dht11_device_t *dev);

/**
 * @brief 读取 DHT11 数据
 *
 * @param dev DHT11 设备
 * @return uint8_t 0: 读取成功; 其他: 读取失败
 */
uint8_t dht11_read(dht11_device_t *dev);

#endif /* __AF_DHT11_H__ */