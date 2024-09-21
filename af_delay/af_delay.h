#ifndef __AF_DELAY_H__
#define __AF_DELAY_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 毫秒级延时函数
 * @param ms 延时时间，单位：毫秒
 */
void af_delay_ms(uint32_t ms);

/**
 * @brief 微秒级延时函数
 * @param us 延时时间，单位：微秒
 */
void af_delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* __AF_DELAY_H__ */
