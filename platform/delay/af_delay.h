#ifndef __AF_DELAY_H__
#define __AF_DELAY_H__

extern volatile unsigned long af_time_delay;

/**
 * @brief 毫秒级延时函数
 * @param ms 延时时间，单位：毫秒
 */
void af_delay_ms(volatile unsigned long ms);

/**
 * @brief 微秒级延时函数
 * @param us 延时时间，单位：微秒
 */
void af_delay_us(volatile unsigned long us);


#endif /* __AF_DELAY_H__ */
