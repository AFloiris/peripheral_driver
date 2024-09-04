#ifndef __AF_GPIO_H__
#define __AF_GPIO_H__

#include "main.h"

typedef struct af_gpio    af_gpio_t;
typedef enum af_gpio_mode af_gpio_mode_t;
typedef enum af_gpio_pull af_gpio_pull_t;

enum af_gpio_mode {                         /* 引脚模式 */
                    AF_GPIO_MODE_INPUT,     /* 输入模式 */
                    AF_GPIO_MODE_OUTPUT_OD, /* 开漏输出模式 */
                    AF_GPIO_MODE_OUTPUT_PP, /* 推挽输出模式 */
};

enum af_gpio_pull {
    AF_GPIO_PULL_NONE, /* 无上拉/下拉 */
    AF_GPIO_PULL_UP,   /* 上拉 */
    AF_GPIO_PULL_DOWN, /* 下拉 */
};

struct af_gpio {
    uint8_t        init; /* gpio 初始化状态 */
    af_gpio_mode_t mode; /* gpio 模式 */
    af_gpio_pull_t pull; /* gpio 上拉/下拉 */

#if defined(USE_HAL_DRIVER) || defined(USE_STDPERIPH_DRIVER) /* STM32 系列 HAL库/标准库 */
    GPIO_TypeDef    *port;
    uint16_t         pin;
    GPIO_InitTypeDef init_struct;
#endif
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