#ifndef __AF_MQX_PLATFORM_H__
#define __AF_MQX_PLATFORM_H__

#include "mqx.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t mqx_platform_init(mqx_dev_t *dev);

uint8_t mqx_platform_deinit(mqx_dev_t *dev);

uint8_t mqx_platform_adc_read(mqx_dev_t *dev, uint16_t *adc_value);

#ifdef __cplusplus
}
#endif

#endif /* __AF_MQX_PLATFORM_H__ */
