#ifndef __AF_ADC_H__
#define __AF_ADC_H__

#include "main.h"

typedef struct af_adc af_adc_t;

struct af_adc {
    uint8_t  init;          /* 初始化 */
    uint8_t  channel;       /* 通道号 */
    float    vref;          /* 参考电压 */
    float    volt;          /* 电压值 */
    uint32_t value;         /* 采样值 */
#if defined(USE_HAL_DRIVER) /* STM32 HAL 库 */
    ADC_HandleTypeDef *hadc;
    ADC_InitTypeDef    adc_init;
#endif
};

/**
 * @brief 初始化ADC
 *
 * @param adc adc 句柄
 */
void af_adc_init(af_adc_t *adc);

/**
 * @brief 反初始化ADC
 *
 * @param adc  adc 句柄
 */
void af_adc_deinit(af_adc_t *adc);

/**
 * @brief 读取ADC值
 *
 * @param adc  adc 句柄
 */
void af_adc_read(af_adc_t *adc);

#endif /* __AF_ADC_H__ */