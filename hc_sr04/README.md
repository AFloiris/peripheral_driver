# HC_SR04


## 使用示例

### STM32

* STM32F407ZGT6
* HAL 库, STM32CubeMX
* GPIOA0, GPIOA1
* HC_SR04

1. 移植 `hc_sr04.c` `hc_sr04.h` `hc_sr04_platform.h` `hc_sr04_platform_stm32_hal.c` 到工程目录下, `af_delay.h` `af_delay_platform_stm32_hal.c` 可选
2. 根据实际情况修改 `hc_sr04_platform_stm32_hal.c` 中的函数
3. 在 `main.c` 中调用 `hc_sr04_test()` 函数

```c
#include "hc_sr04.h"
#include <stdio.h>
void hc_sr04_test(void)
{
    uint8_t i   = 0;
    uint8_t ret = 0;

    hc_sr04_dev_t *dev = hc_sr04_open();
    if (dev == NULL)
    {
        printf("hc_sr04 open failed\n");
        return;
    }

    while (i++ < 3)
    {
        ret = hc_sr04_read(dev);
        if (ret)
        {
            printf("hc_sr04 read failed ret : %d\n", ret);
            hc_sr04_close(dev);
            return;
        }
        printf("hc_sr04 time : %u\n", dev->time);
        printf("hc_sr04 distance : %.3f\n", dev->distance);
        HAL_Delay(2000);
    }
    hc_sr04_close(dev);
}

```

运行结果
```
// TODO 待测试

```