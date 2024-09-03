#ifndef __AF_GPIO_H__
#define __AF_GPIO_H__

#include "main.h"

typedef struct af_gpio    af_gpio_t;
typedef enum af_gpio_mode af_gpio_mode_t;

enum af_gpio_mode {                      /* 引脚模式 */
                    AF_GPIO_MODE_INPUT,  /* 输入模式 */
                    AF_GPIO_MODE_OUTPUT, /* 输出模式 */
};

struct af_gpio {
#if defined(USE_HAL_DRIVER) || defined(USE_STDPERIPH_DRIVER) /* STM32 系列 HAL库/标准库 */
    GPIO_TypeDef *port;
    uint16_t      pin;
#endif
    af_gpio_mode_t mode; /* gpio 模式 */
    uint8_t        init; /* gpio 初始化状态 */
};

/**
 * @brief gpio 初始化
 *
 * @param gpio gpio 句柄
 */
void af_gpio_init(af_gpio_t *gpio);

/**
 * @brief gpio 反初始化
 *
 * @param gpio gpio 句柄
 */
void af_gpio_deinit(af_gpio_t *gpio);

/**
 * @brief 设置 gpio 模式
 *
 * @param gpio gpio 句柄
 * @param mode gpio 模式
 */
void af_gpio_set_mode(af_gpio_t *gpio, af_gpio_mode_t mode);

/**
 * @brief 读取 gpio 状态
 *
 * @param gpio gpio 句柄
 * @return uint8_t gpio 状态
 */
uint8_t af_gpio_read(af_gpio_t *gpio);

/**
 * @brief 设置 gpio 状态
 *
 * @param gpio  gpio 句柄
 * @param value gpio 状态
 */
void af_gpio_write(af_gpio_t *gpio, uint8_t value);

#endif /* __AF_GPIO_H__ */