#include "adc.h"
#include "mqx_platform.h"

uint8_t mqx_platform_init(mqx_dev_t *dev)
{
    // MX_ADC1_Init();
    return 0;
}

uint8_t mqx_platform_deinit(mqx_dev_t *dev)
{
    //
    return 0;
}

uint8_t mqx_platform_adc_read(mqx_dev_t *dev, uint16_t *adc_value)
{
    (void)dev;

    HAL_ADC_Start(&hadc1);                 /* 启动ADC转换 */
    HAL_ADC_PollForConversion(&hadc1, 20); /* 等待转换完成，20为最大等待时间，单位为ms */

    if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
    {
        *adc_value = HAL_ADC_GetValue(&hadc1); /* 获取AD值 */
    }
    return 0;
}
