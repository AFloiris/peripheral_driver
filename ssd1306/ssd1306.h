#ifndef __AF_SSD1306_H__
#define __AF_SSD1306_H__

#include "ssd1306_font.h"
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct ssd1306_dev     ssd1306_dev_t;
typedef enum ssd1306_interface ssd1306_interface_t;

enum ssd1306_interface {
    SSD1306_INTERFACE_I2C,
    SSD1306_INTERFACE_SPI,
};

struct ssd1306_dev {
    uint8_t             id;        /* 设备 id */
    uint8_t             i2c_addr;  /* i2c 地址 */
    uint8_t            *gram;      /* 显示缓存 */
    uint8_t             width;     /* 显示宽度 */
    uint8_t             height;    /* 显示高度 */
    ssd1306_interface_t interface; /* 接口类型 */
};

/**
 * @brief 打开 ssd1306 设备
 *
 * @param width     宽度
 * @param height    高度
 * @param interface 接口类型
 * @return ssd1306_dev_t* ssd1306 设备
 */
ssd1306_dev_t *ssd1306_open(uint8_t width, uint8_t height, ssd1306_interface_t interface, uint8_t i2c_addr);

/**
 * @brief 关闭 ssd1306 设备
 *
 * @param dev ssd1306 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t ssd1306_close(ssd1306_dev_t *dev);

/**
 * @brief 复位 ssd1306 设备
 *
 * @param dev ssd1306 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t ssd1306_reset(ssd1306_dev_t *dev);

/**
 * @brief 清除屏幕,同时清除gram
 *
 * @param dev ssd1306 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t ssd1306_clear(ssd1306_dev_t *dev, uint8_t color);

/**
 * @brief 更新显示缓存
 *
 * @param dev ssd1306 设备
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t ssd1306_gram_update(ssd1306_dev_t *dev);

/**
 * @brief gram 写入一个点
 *
 * @param dev   ssd1306 设备
 * @param x     x 坐标
 * @param y     y 坐标
 * @param color 颜色
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t ssd1306_gram_write_point(ssd1306_dev_t *dev, uint8_t x, uint8_t y, uint8_t color);

/**
 * @brief gram 写入一个字符
 *
 * @param dev   ssd1306 设备
 * @param x     x 坐标
 * @param y     y 坐标
 * @param ch    字符
 * @param font  字体
 * @param color 颜色
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t ssd1306_gram_write_char(ssd1306_dev_t *dev, uint8_t x, uint8_t y, uint8_t ch, ssd1306_font_t font,
                                uint8_t color);

/**
 * @brief gram 写入字符串
 *
 * @param dev   ssd1306 设备
 * @param x     x 坐标
 * @param y     y 坐标
 * @param str   字符串
 * @param font  字体
 * @param color 颜色
 * @return uint8_t 0: 成功; 其他: 失败
 */
uint8_t ssd1306_gram_write_string(ssd1306_dev_t *dev, uint8_t x, uint8_t y, uint8_t *str, uint8_t len,
                                  ssd1306_font_t font, uint8_t color);

#ifdef __cplusplus
}
#endif

#endif /* __AF_SSD1306_H__ */
