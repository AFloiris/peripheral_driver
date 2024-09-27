#ifndef __AF_DS18B20_H__
#define __AF_DS18B20_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ds18b20_dev ds18b20_dev_t;

struct ds18b20_dev {
    uint8_t id;          /* 设备 id */
    uint8_t raw_data[2]; /* 原始数据 */
    float   temperature; /* 温度 */
};

/**
 * @brief 打开 ds18b20 设备
 *
 * @return ds18b20_dev_t*  ds18b20 设备
 */
ds18b20_dev_t *ds18b20_open(void);

/**
 * @brief 关闭 ds18b20 设备
 *
 * @param dev      ds18b20 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t ds18b20_close(ds18b20_dev_t *dev);

/**
 * @brief 读取 ds18b20 温度
 *
 * @param dev      ds18b20 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t ds18b20_read(ds18b20_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* __AF_DS18B20_H__ */
