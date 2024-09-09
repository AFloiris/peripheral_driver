#include "af_adc.h"

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