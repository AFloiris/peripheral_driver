#include "ssd1306.h"
#include "ssd1306_platform.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief 命令定义
 */
#define SSD1306_CMD_LOWER_COLUMN_START_ADDRESS       0x00 /* 低列起始地址 */
#define SSD1306_CMD_HIGHER_COLUMN_START_ADDRESS      0x10 /* 高列起始地址 */
#define SSD1306_CMD_MEMORY_ADDRESSING_MODE           0x20 /* 内存寻址模式 */
#define SSD1306_CMD_SET_COLUMN_ADDRESS               0x21 /* 设置列地址 */
#define SSD1306_CMD_SET_PAGE_ADDRESS                 0x22 /* 设置页地址 */
#define SSD1306_CMD_SET_FADE_OUT_AND_BLINKING        0x23 /* 设置淡出和闪烁 */
#define SSD1306_CMD_RIGHT_HORIZONTAL_SCROLL          0x26 /* 向右水平滚动 */
#define SSD1306_CMD_LEFT_HORIZONTAL_SCROLL           0x27 /* 向左水平滚动 */
#define SSD1306_CMD_VERTICAL_RIGHT_HORIZONTAL_SCROLL 0x29 /* 向下垂直右水平滚动 */
#define SSD1306_CMD_VERTICAL_LEFT_HORIZONTAL_SCROLL  0x2A /* 向下垂直左水平滚动 */
#define SSD1306_CMD_DEACTIVATE_SCROLL                0x2E /* 停用滚动 */
#define SSD1306_CMD_ACTIVATE_SCROLL                  0x2F /* 激活滚动 */
#define SSD1306_CMD_DISPLAY_START_LINE               0x40 /* 显示起始行 */
#define SSD1306_CMD_CONTRAST_CONTROL                 0x81 /* 对比度控制 */
#define SSD1306_CMD_CHARGE_PUMP_SETTING              0x8D /* 充电泵设置 */
#define SSD1306_CMD_COLUMN_0_MAPPED_TO_SEG0          0xA0 /* 列0映射到SEG0 */
#define SSD1306_CMD_COLUMN_127_MAPPED_TO_SEG0        0xA1 /* 列127映射到SEG0 */
#define SSD1306_CMD_VERTICAL_SCROLL_AREA             0xA3 /* 垂直滚动区域 */
#define SSD1306_CMD_ENTIRE_DISPLAY_OFF               0xA4 /* 整屏关闭 */
#define SSD1306_CMD_ENTIRE_DISPLAY_ON                0xA5 /* 整屏开启 */
#define SSD1306_CMD_NORMAL_DISPLAY                   0xA6 /* 正常显示 */
#define SSD1306_CMD_INVERSE_DISPLAY                  0xA7 /* 反相显示 */
#define SSD1306_CMD_MULTIPLEX_RATIO                  0xA8 /* 多路复用比率 */
#define SSD1306_CMD_DISPLAY_OFF                      0xAE /* 显示关闭 */
#define SSD1306_CMD_DISPLAY_ON                       0xAF /* 显示开启 */
#define SSD1306_CMD_PAGE_ADDR                        0xB0 /* 页地址 */
#define SSD1306_CMD_SCAN_DIRECTION_COM0_START        0xC0 /* 扫描方向：COM0开始 */
#define SSD1306_CMD_SCAN_DIRECTION_COMN_1_START      0xC8 /* 扫描方向：COMN-1开始 */
#define SSD1306_CMD_DISPLAY_OFFSET                   0xD3 /* 显示偏移 */
#define SSD1306_CMD_DISPLAY_CLOCK_DIVIDE             0xD5 /* 显示时钟分频 */
#define SSD1306_CMD_SET_ZOOM_IN                      0xD6 /* 设置放大 */
#define SSD1306_CMD_PRE_CHARGE_PERIOD                0xD9 /* 预充电周期 */
#define SSD1306_CMD_COM_PINS_CONF                    0xDA /* COM引脚配置 */
#define SSD1306_CMD_COMH_DESLECT_LEVEL               0xDB /* COMH去选择级别 */
#define SSD1306_CMD_NOP                              0xE3 /* NOP */

static uint8_t ssd1306_init(ssd1306_dev_t *dev) { return ssd1306_platform_init(dev); };

static uint8_t ssd1306_deinit(ssd1306_dev_t *dev) { return ssd1306_platform_deinit(dev); }

static uint8_t ssd1306_write_data(ssd1306_dev_t *dev, uint8_t *data, uint16_t len)
{
    if (dev->interface == SSD1306_INTERFACE_I2C)
    {
        return ssd1306_platform_i2c_write(dev, dev->i2c_addr, 0x40, data, len);
    }
    else if (dev->interface == SSD1306_INTERFACE_SPI)
    {
        return ssd1306_platform_spi_write(dev, data, len);
    }
    return 1;
}

static uint8_t ssd1306_write_cmd(ssd1306_dev_t *dev, uint8_t cmd)
{
    if (dev->interface == SSD1306_INTERFACE_I2C)
    {
        return ssd1306_platform_i2c_write(dev, dev->i2c_addr, 0x00, &cmd, 1);
    }
    else if (dev->interface == SSD1306_INTERFACE_SPI)
    {
        return ssd1306_platform_spi_write(dev, &cmd, 1);
    }
    return 1;
}

ssd1306_dev_t *ssd1306_open(uint8_t width, uint8_t height, ssd1306_interface_t interface, uint8_t i2c_addr)
{
    ssd1306_dev_t *dev = (ssd1306_dev_t *)malloc(sizeof(ssd1306_dev_t));
    if (dev == NULL)
        return NULL;
    memset(dev, 0, sizeof(ssd1306_dev_t));

    dev->gram = (uint8_t *)malloc(width * height / 8);
    if (dev->gram == NULL)
    {
        memset(dev, 0, sizeof(ssd1306_dev_t));
        free(dev);
        return NULL;
    }
    memset(dev->gram, 0, width * height / 8);

    dev->width     = width;
    dev->height    = height;
    dev->interface = interface;
    if (interface == SSD1306_INTERFACE_I2C)
        dev->i2c_addr = i2c_addr;

    if (ssd1306_init(dev))
    {
        memset(dev, 0, sizeof(ssd1306_dev_t));
        memset(dev->gram, 0, width * height / 8);
        free(dev->gram);
        free(dev);
        return NULL;
    }

    ssd1306_reset(dev);

    return dev;
}

uint8_t ssd1306_close(ssd1306_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    if (ssd1306_deinit(dev))
        return 2;

    memset(dev->gram, 0, dev->width * dev->height / 8);
    free(dev->gram);
    memset(dev, 0, sizeof(ssd1306_dev_t));
    free(dev);
    return 0;
}

uint8_t ssd1306_reset(ssd1306_dev_t *dev)
{
    /* 关闭显示 */
    ssd1306_write_cmd(dev, SSD1306_CMD_DISPLAY_OFF);
    /* 设置显示时钟分频比/振荡器频率 */
    ssd1306_write_cmd(dev, SSD1306_CMD_DISPLAY_CLOCK_DIVIDE);
    ssd1306_write_cmd(dev, 0x80);
    /* 设置多路复用率 */
    ssd1306_write_cmd(dev, SSD1306_CMD_MULTIPLEX_RATIO);
    ssd1306_write_cmd(dev, 0x3F);
    /* 设置显示偏移 */
    ssd1306_write_cmd(dev, SSD1306_CMD_DISPLAY_OFFSET);
    ssd1306_write_cmd(dev, 0x00);
    /* 设置显示开始行 */
    ssd1306_write_cmd(dev, SSD1306_CMD_DISPLAY_START_LINE);
    ssd1306_write_cmd(dev, 0x00);
    /* 设置左右方向 */
    ssd1306_write_cmd(dev, SSD1306_CMD_COLUMN_127_MAPPED_TO_SEG0);
    /* 设置上下方向 */
    ssd1306_write_cmd(dev, SSD1306_CMD_SCAN_DIRECTION_COMN_1_START);
    /* 设置COM引脚配置 */
    ssd1306_write_cmd(dev, SSD1306_CMD_COM_PINS_CONF);
    ssd1306_write_cmd(dev, 0x12);
    /* 设置对比度控制 */
    ssd1306_write_cmd(dev, SSD1306_CMD_CONTRAST_CONTROL);
    ssd1306_write_cmd(dev, 0xCF);
    /* 设置预充电周期 */
    ssd1306_write_cmd(dev, SSD1306_CMD_PRE_CHARGE_PERIOD);
    ssd1306_write_cmd(dev, 0xF1);
    /* 设置VCOMH取消选择级别 */
    ssd1306_write_cmd(dev, SSD1306_CMD_COMH_DESLECT_LEVEL);
    ssd1306_write_cmd(dev, 0x30);
    /* 设置充电泵设置 */
    ssd1306_write_cmd(dev, SSD1306_CMD_CHARGE_PUMP_SETTING);
    ssd1306_write_cmd(dev, 0x14);
    /* 设置整个显示打开/关闭 */
    ssd1306_write_cmd(dev, SSD1306_CMD_ENTIRE_DISPLAY_OFF);
    /* 设置正常/倒转显示 */
    ssd1306_write_cmd(dev, SSD1306_CMD_NORMAL_DISPLAY);
    /* 显示开启 */
    ssd1306_write_cmd(dev, SSD1306_CMD_DISPLAY_ON);
    /* 清除屏幕 */
    ssd1306_clear(dev, 0);
    return 0;
}

uint8_t ssd1306_clear(ssd1306_dev_t *dev, uint8_t color)
{
    /* 清除gram, 更新显示 */
    memset(dev->gram, color ? 0xFF : 0x00, dev->width * dev->height / 8);
    ssd1306_gram_update(dev);
    return 0;
}

uint8_t ssd1306_set_cursor(ssd1306_dev_t *dev, uint8_t x, uint8_t y)
{
    uint8_t page = y / 8;
    uint8_t err  = 0;

    if (dev == NULL || x >= dev->width || y >= dev->height)
        return 1;

    /* 设置页地址 */
    err = ssd1306_write_cmd(dev, SSD1306_CMD_PAGE_ADDR | page);
    if (err)
        return 2;

    /* 设置列地址 */
    err = ssd1306_write_cmd(dev, SSD1306_CMD_HIGHER_COLUMN_START_ADDRESS | ((x & 0xF0) >> 4));
    if (err)
        return 3;

    err = ssd1306_write_cmd(dev, SSD1306_CMD_LOWER_COLUMN_START_ADDRESS | (x & 0x0F));
    if (err)
        return 4;

    return 0;
}

uint8_t ssd1306_write_point(ssd1306_dev_t *dev, uint8_t x, uint8_t y, uint8_t color)
{
    uint8_t err = 0;

    if (dev == NULL || x >= dev->width || y >= dev->height)
        return 1;

    /* gram 写入数据 */
    err = ssd1306_gram_write_point(dev, x, y, color);
    if (err)
        return 2;

    /* 设置光标位置 */
    err = ssd1306_set_cursor(dev, x, y);
    if (err)
        return 3;

    /* 写入数据 */
    err = ssd1306_write_data(dev, &color, 1);
    if (err)
        return 4;
    return 0;
}

uint8_t ssd1306_gram_update(ssd1306_dev_t *dev)
{
    uint8_t err = 0;
    uint8_t i;

    if (dev == NULL)
        return 1;

    for (i = 0; i < dev->height / 8; i++)
    {
        /* 设置页地址 */
        err = ssd1306_set_cursor(dev, 0, i * 8);
        if (err)
            return 2;
        /* 写入当前页的数据 */
        err = ssd1306_write_data(dev, &dev->gram[i * dev->width], dev->width);
        if (err)
            return 3;
    }

    return 0;
}

uint8_t ssd1306_gram_write_point(ssd1306_dev_t *dev, uint8_t x, uint8_t y, uint8_t color)
{
    if (dev == NULL || x >= dev->width || y >= dev->height)
        return 1;

    /* 当前光标位置置0 */
    dev->gram[x + (y / 8) * dev->width] &= ~(1 << (y % 8));
    /* 当前光标位置置 color */
    dev->gram[x + (y / 8) * dev->width] |= ((color & 0x01) << (y % 8));
    return 0;
}

uint8_t ssd1306_gram_write_char(ssd1306_dev_t *dev, uint8_t x, uint8_t y, uint8_t ch, ssd1306_font_t font,
                                uint8_t color)
{
    // 确保字符不会超出显示区域
    if (x >= dev->width || y >= dev->height || x + font.width > dev->width || y + font.height > dev->height)
    {
        return 1; // 返回错误代码1，表示超出范围
    }

    const uint8_t *data = font.data + (ch - 32) * font.size;
    /* data为列行式, 考虑18x16的字体 */
    for (uint8_t i = 0; i < font.height / 8; i++) /* 遍历字体的每一行 */
    {
        for (uint8_t j = 0; j < font.width; j++) /* 遍历字体的每一列 */
        {
            uint8_t byte = data[i * font.width + j];
            for (uint8_t k = 0; k < 8; k++) /* 遍历字体的每一字节 */
            {
                uint8_t bit = (byte >> k) & 0x01;
                uint8_t x_  = x + j;
                uint8_t y_  = y + i * 8 + k;
                ssd1306_gram_write_point(dev, x_, y_, bit ? color : !color);
            }
        }
    }

    return 0; // 正常返回
}

uint8_t ssd1306_gram_write_string(ssd1306_dev_t *dev, uint8_t x, uint8_t y, uint8_t *str, uint8_t len,
                                  ssd1306_font_t font, uint8_t color)
{
    uint8_t err = 0;

    if (dev == NULL || x >= dev->width || y >= dev->height || str == NULL || len == 0)
        return 1;

    for (uint8_t i = 0; i < len; i++)
    {
        err = ssd1306_gram_write_char(dev, x + i * font.width, y, str[i], font, color);
        if (err)
            return 2;
    }
    return 0;
}
