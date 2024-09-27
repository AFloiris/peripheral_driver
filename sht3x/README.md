# SHT30


## 使用示例

### STM32

* STM32F407ZGT6
* HAL 库, STM32CubeMX
* I2C1

1. 移植 `sht30.c` `sht30.h` `sht30_platform.h` `sht30_platform_stm32_hal.c` 到工程目录下
2. 根据实际情况修改 `sht30_platform_stm32_hal.c` 中的函数
3. 在 `main.c` 中调用 `sht30_test()` 函数
```C
#include "sht3x.h"
#include <stdio.h>
void sht3x_test(void)
{
    uint8_t i   = 0;
    uint8_t ret = 0;

    sht3x_dev_t *dev = sht3x_open(0x44);
    if (dev == NULL)
    {
        printf(" sht3x open failed\n");
        return;
    }

    while (i++ < 3)
    {
        ret = sht3x_read(dev);
        if (ret)
        {
            printf(" sht3x read failed ret : %d\n", ret);
            sht3x_close(dev);
            return;
        }
        printf("[%d] raw [%d] [%d] [%d] [%d] [%d] [%d]\n", i, dev->raw_data[0], dev->raw_data[1], dev->raw_data[2],
               dev->raw_data[3], dev->raw_data[4], dev->raw_data[5]);
        printf("[%d] humidity: %.2f\n", i, dev->humidity);
        printf("[%d] temperature: %.2f\n", i, dev->temperature);
        HAL_Delay(2000);
    }

    sht3x_close(dev);
}
```

运行结果
```
# RECV ASCII/85 <<<
[1] raw [108] [97] [234] [200] [34] [248]
[1] humidity: 78.18
[1] temperature: 29.09

# RECV ASCII/86 <<<
[2] raw [108] [97] [234] [199] [101] [203]
[2] humidity: 77.89
[2] temperature: 29.09

# RECV ASCII/86 <<<
[3] raw [108] [103] [76] [198] [203] [220]
[3] humidity: 77.65
[3] temperature: 29.10
```