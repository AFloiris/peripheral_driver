# SSD1306

## 使用示例

### STM32

* STM32F407ZGT6
* HAL 库, STM32CubeMX
* I2C1
* SSD1306 I2C 128x64 OLED

1. 移植 `ssd1306.c` `ssd1306.h` `ssd1306_font.h` `ssd1306_font.c` `ssd1306_platform.h` `ssd1306_platform_stm32_hal.c` 到工程目录下
2. 根据实际情况修改 `ssd1306_platform_stm32_hal.c` 中的函数
3. 在 `main.c` 中调用 `ssd1306_test()` 函数
```C
#include "ssd1306.h"
#include <stdio.h>
void ssd1306_test(void)
{
    uint8_t err       = 0;
    uint8_t y         = 0;
    uint8_t zh_idx[4] = {0, 1, 3, 4};

    /* 打开 ssd1306 设备 */
    ssd1306_dev_t *oled = ssd1306_open(128, 64, SSD1306_INTERFACE_I2C, 0x78);
    if (oled == NULL)
    {
        printf("open ssd1306 failed\r\n");
        return;
    }

    /* 写 ascii 字符 */
    err = ssd1306_gram_write_string(oled, 0, y, (uint8_t *)"1234567890", 10, ssd1306_font_ascii_8x16, 1);
    if (err)
    {
        printf("write number string failed\r\n");
        ssd1306_close(oled);
        return;
    }
    y += ssd1306_font_ascii_8x16.height;

    err = ssd1306_gram_write_string(oled, 0, y, (uint8_t *)"ABCxyz!<=>", 10, ssd1306_font_ascii_12x24, 1);
    if (err)
    {
        printf("write string failed\r\n");
        ssd1306_close(oled);
        return;
    }
    y += ssd1306_font_ascii_12x24.height;

    /* 写汉字 */
    err = ssd1306_gram_write_string(oled, 0, y, zh_idx, 4, ssd1306_font_lxgw_24x24, 1);
    if (err)
    {
        printf("write chinese string failed\r\n");
        ssd1306_close(oled);
        return;
    }

    /* 更新显示 */
    err = ssd1306_gram_update(oled);
    if (err)
    {
        printf("update display failed\r\n");
        ssd1306_close(oled);
        return;
    }

    /* 关闭 ssd1306 设备 */
    ssd1306_close(oled);
}

```

运行结果
