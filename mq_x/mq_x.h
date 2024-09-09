#ifndef __AF_MQ_X_H__
#define __AF_MQ_X_H__

#include "main.h"

typedef struct mq_x_device mq_x_device_t;
typedef struct mq_x_adc    mq_x_adc_t;
typedef enum mq_x_type     mq_x_type_t;

enum mq_x_type {
    MQ_X_TYPE_MQ2,
    MQ_X_TYPE_MQ5,
    MQ_X_TYPE_MQ6,
    MQ_X_TYPE_MQ7,
};

struct mq_x_adc {
#if defined(USE_HAL_DRIVER)
    ADC_HandleTypeDef *handle;
#endif
    float vref; /* 参考电压 */
};

struct mq_x_device {
    uint16_t    adc_value; /* ADC 值 */
    float       voltage;   /* 电压值 */
    float       ppm;       /* ppm 值 */
    mq_x_type_t type;      /* 传感器类型 */
    uint32_t    rl;        /* RL 值 */
    uint32_t    r0;        /* R0 值 */
    uint32_t    rs;        /* RS 值 */
    mq_x_adc_t  adc;       /* ADC 设备 */
};

/**
 * @brief 打开 MQ-X 设备
 *
 * @param adc adc 设备
 * @return mq_x_device_t* mq_x 设备
 */
mq_x_device_t *mq_x_open(mq_x_adc_t adc, mq_x_type_t type);

/**
 * @brief 关闭 MQ-X 设备
 *
 * @param dev mq_x 设备
 */
void mq_x_close(mq_x_device_t *dev);

/**
 * @brief 以当前环境为正常环境，校准 MQ-X 设备
 *
 * @param dev mq_x 设备
 * @return uint8_t 0: 校准成功; 其他: 校准失败
 */
uint8_t mq_x_reset(mq_x_device_t *dev);

/**
 * @brief 读取 MQ-X 设备数据
 *
 * @param dev   mq_x 设备
 * @return uint8_t  0: 读取成功; 其他: 读取失败
 */
uint8_t mq_x_read(mq_x_device_t *dev);

#endif /* __AF_MQ_X_H__ */