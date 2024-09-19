#ifndef __AF_MQX_H__
#define __AF_MQX_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mqx_dev mqx_dev_t;
typedef enum mqx_type  mqx_type_t;

/* mqx 的类型 */
enum mqx_type {
    MQ2 = 0x10,
    MQ5,
    MQ6,
    MQ7,
};

struct mqx_dev {            /* mqx 设备 */
    uint8_t    id;          /* 设备 id */
    mqx_type_t type;        /* 设备类型 */
    uint16_t   adc_value;   /* adc 值 */
    float      ref_voltage; /* 参考电压值 */
    float      voltage;     /* 电压值 */
    float      ppm;         /* ppm 值 */
    uint32_t   rl;          /* RL 值 */
    uint32_t   r0;          /* R0 值 */
    uint32_t   rs;          /* RS 值 */
};

/**
 * @brief 打开 mqx 设备
 *
 * @param type        mqx 类型
 * @param ref_voltage adc 参考电压值
 * @param rl          RL 值
 * @return mqx_dev_t* mqx 设备
 */
mqx_dev_t *mqx_open(mqx_type_t type, float ref_voltage, uint32_t rl);

/**
 * @brief 关闭 mqx 设备
 *
 * @param dev  mqx 设备
 * @return uint8_t 0: 成功, 其他: 失败
 */
uint8_t mqx_close(mqx_dev_t *dev);

/**
 * @brief mqx 设备复位, 以当前环境为参考值
 *
 * @param dev mqx 设备
 * @return uint8_t 0: 成功, 其他: 失败
 */
uint8_t mqx_reset(mqx_dev_t *dev);

/**
 * @brief 读取 mqx 设备的 ppm 值
 *
 * @param dev mqx 设备
 * @return uint8_t 0: 成功, 其他: 失败
 */
uint8_t mqx_read(mqx_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* __AF_MQX_H__ */
