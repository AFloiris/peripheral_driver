/**
 * @note 添加自定义字体时，1. 高度必须为8bit的倍数; 2. 字体数据取模为列行式; 3. 字体数据从上低位在前
 */
#ifndef __AF_SSD1306_FONT_H__
#define __AF_SSD1306_FONT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AF_USE_SSD1306_FONT_ASCII_8X16  1 /* 使用 16x8 ascii 字体 */
#define AF_USE_SSD1306_FONT_ASCII_12X24 1 /* 使用 12X24 ascii 字体 */
#define AF_USE_SSD1306_FONT_LXGW_24X24  1 /* 使用 24x24 LXGW 字体 */

typedef struct ssd1306_font ssd1306_font_t;

struct ssd1306_font {
    uint8_t        width;  /* 字体宽度 */
    uint8_t        height; /* 字体高度 */
    uint8_t        size;   /* 字体大小 */
    uint8_t        start;  /* 字体起始 ASCII 码 */
    uint8_t        end;    /* 字体结束 ASCII 码 */
    const uint8_t *data;   /* 字体取模数据 */
};

#if AF_USE_SSD1306_FONT_ASCII_8X16 == 1
extern const ssd1306_font_t ssd1306_font_ascii_8x16;
#endif /* AF_USE_SSD1306_FONT_ASCII_8X16 */

#if AF_USE_SSD1306_FONT_ASCII_12X24 == 1
extern const ssd1306_font_t ssd1306_font_ascii_12x24;
#endif /* AF_USE_SSD1306_FONT_ASCII_12X24 */

#if AF_USE_SSD1306_FONT_LXGW_24X24 == 1
extern const ssd1306_font_t ssd1306_font_lxgw_24x24;
#endif /* AF_USE_SSD1306_FONT_LXGW_24X24 */

#ifdef __cplusplus
}
#endif

#endif /* __AF_SSD1306_FONT_H__ */
