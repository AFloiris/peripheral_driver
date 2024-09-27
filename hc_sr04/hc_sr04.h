#ifndef __AF_HC_SR04_H__
#define __AF_HC_SR04_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hc_sr04_dev hc_sr04_dev_t;

struct hc_sr04_dev {
    uint8_t  id;       /* 设备 id */
    uint32_t time;     /* 时间 (us) */
    float    distance; /* 距离 (cm) */
};

/**
 * @brief 打开 hc_sr04 设备
 *
 * @return hc_sr04_dev_t*  hc_sr04 设备
 */
hc_sr04_dev_t *hc_sr04_open(void);

/**
 * @brief 关闭 hc_sr04 设备
 *
 * @param dev      hc_sr04 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t hc_sr04_close(hc_sr04_dev_t *dev);

/**
 * @brief 读取 hc_sr04 距离
 *
 * @param dev      hc_sr04 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t hc_sr04_read(hc_sr04_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* __AF_HC_SR04_H__ */
