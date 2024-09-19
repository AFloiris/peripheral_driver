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
#include "sht30.h"
#include <stdio.h>
void sht30_test(void)
{
    uint8_t i   = 0;
    uint8_t ret = 0;

    sht30_dev_t *dev = sht30_open(0x44);
    if (dev == NULL)
    {
        printf(" sht30 open failed\n");
        return;
    }

    while (i++ < 3)
    {
        ret = sht30_read(dev);
        if (ret)
        {
            printf(" sht30 read failed ret : %d\n", ret);
            sht30_close(dev);
            return;
        }
        printf("[%d] raw [%d] [%d] [%d] [%d] [%d] [%d]\n", i, dev->data[0], dev->data[1], dev->data[2], dev->data[3],
               dev->data[4], dev->data[5]);
        printf("[%d] humidity: %.2f\n", i, dev->humidity);
        printf("[%d] temperature: %.2f\n", i, dev->temperature);
        HAL_Delay(2000);
    }

    sht30_close(dev);
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