#include "mq_x.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 读取ADC值
 * @note  平台相关
 */
static void mq_x_adc_read(mq_x_device_t *dev) {
#if defined(USE_HAL_DRIVER)
    HAL_ADC_Start(dev->adc.handle);                 /* 启动ADC转换 */
    HAL_ADC_PollForConversion(dev->adc.handle, 20); /* 等待转换完成，20为最大等待时间，单位为ms */

    if (HAL_IS_BIT_SET(HAL_ADC_GetState(dev->adc.handle), HAL_ADC_STATE_REG_EOC)) {
        dev->adc_value = HAL_ADC_GetValue(dev->adc.handle); /* 获取AD值 */
    }
#endif
}

/**
 * @brief 计算mq-5的ppm值
 * @note  驱动相关
 * R0 = (Vc - Vrl) * Rl / Vrl  R0 为正常浓度下的电阻值
 * Rs = (Vc - Vrl) * Rl / Vrl  Rs 为实际测量的电阻值
 * Rs/R0 = 11.54 * ppm ^ (-0.65)
 * ppm = (11.54 * Rs/R0 )^ 0.65
 * @param handle MQ-X传感器句柄
 * @param type 0 正常浓度,用于计算R0, 其他 实际测量,用于计算RS
 */
static void mq_5_calc_ppm(mq_x_device_t *dev, uint8_t type) {

    float vrl = dev->voltage;
    float rl  = (float)dev->rl;

    if (type == 0) {
        dev->r0 = (uint32_t)(5.0 / vrl - 1) * rl;
    } else {
        dev->rs  = (5.0 / vrl - 1) * rl;
        dev->ppm = pow((11.54 * dev->rs / dev->r0), 0.65);
    }
}

mq_x_device_t *mq_x_open(mq_x_adc_t adc, mq_x_type_t type) {

    mq_x_device_t *dev = (mq_x_device_t *)malloc(sizeof(mq_x_device_t));
    if (dev != NULL) {
        memset(dev, 0, sizeof(mq_x_device_t));
        dev->adc = adc;
    }
    return dev;
}

void mq_x_close(mq_x_device_t *dev) {
    if (dev == NULL) return;

    memset(dev, 0, sizeof(mq_x_device_t));
    free(dev);
}

uint8_t mq_x_reset(mq_x_device_t *dev) {

    if (dev == NULL) return 1;

    mq_x_adc_read(dev);
    dev->voltage = (float)dev->adc_value * dev->adc.vref / 4095.0;

    if (dev->type == MQ_X_TYPE_MQ5) {
        mq_5_calc_ppm(dev, 0);
    }

    return 1;
}

uint8_t mq_x_read(mq_x_device_t *dev) {

    if (dev == NULL) return 1;

    mq_x_adc_read(dev);
    dev->voltage = (float)dev->adc_value * dev->adc.vref / 4095.0;

    if (dev->type == MQ_X_TYPE_MQ5) {
        mq_5_calc_ppm(dev, 1);
    }

    return 0;
}