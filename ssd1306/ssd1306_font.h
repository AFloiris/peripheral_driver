#ifndef __AF_SSD1306_FONT_H__
#define __AF_SSD1306_FONT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AF_USE_FONT_12X6  1 /* 使用 12x6 字体 */
#define AF_USE_FONT_16X8  1 /* 使用 16x8 字体 */
#define AF_USE_FONT_24X12 1 /* 使用 24x12 字体 */

typedef struct ssd1306_font ssd1306_font_t;

struct ssd1306_font {
    uint8_t        width;  /* 字体宽度 */
    uint8_t        height; /* 字体高度 */
    uint8_t        size;   /* 字体大小 */
    const uint8_t *data;   /* 字体数据 */
};

#if AF_USE_FONT_12X6 == 1
extern const ssd1306_font_t ssd1306_font_ascii_12x6;
#endif

#if AF_USE_FONT_16X8 == 1
extern const ssd1306_font_t ssd1306_font_ascii_16x8;
#endif

#if AF_USE_FONT_24X12 == 1
extern const ssd1306_font_t ssd1306_font_ascii_24x12;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AF_SSD1306_FONT_H__ */

// 0x00,0x08,0x1f,0x00,0x00,0x00,0x00,0x00,  0x00,0x04,0xfc,0x04,0x00,0x00,0x00,0x00

