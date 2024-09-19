# MQX


## 使用示例

### STM32

* STM32F407ZGT6
* HAL 库, STM32CubeMX
* ADC1,GPIOA1
* MQ5

1. 移植 `mqx.c` `mqx.h` `mqx_platform.h` `mqx_platform_stm32_hal.c` 到工程目录下
2. 根据实际情况修改 `mqx_platform_stm32_hal.c` 中的函数
3. 在 `main.c` 中调用 `mqx_test()` 函数

```c
#include "mqx.h"
#include <stdio.h>
void mqx_test(void)
{
    uint8_t i   = 0;
    uint8_t ret = 0;

    mqx_dev_t *dev = mqx_open(MQ5, 3.3, 5000);
    if (dev == NULL)
    {
        printf("mqx open failed\n");
        return;
    }

    while (i++ < 3)
    {
        ret = mqx_reset(dev);
        if (ret)
        {
            printf("mqx reset failed ret : %d\n", ret);
            mqx_close(dev);
            return;
        }
    }
    printf("mqx reset success\n");
    i = 0;

    while (i++ < 3)
    {
        ret = mqx_read(dev);
        if (ret)
        {
            printf("mqx read failed ret : %d\n", ret);
            mqx_close(dev);
            return;
        }
        printf("[%d] mq5 adc : %d, voltage : %.2f, r0 : %d, rs : %d, ppm : %.2f\n", i, dev->adc_value, dev->voltage,
               dev->r0, dev->rs, dev->ppm);
        HAL_Delay(2000);
    }
    mqx_close(dev);
}

```

运行结果
```
# RECV ASCII/88 <<<
mqx reset success
[1] mq5 adc : 2070, voltage : 1.67, r0 : 10000, rs : 9986, ppm : 4.90

# RECV ASCII/71 <<<
[2] mq5 adc : 2041, voltage : 1.64, r0 : 10000, rs : 10199, ppm : 4.97

# RECV ASCII/71 <<<
[3] mq5 adc : 2019, voltage : 1.63, r0 : 10000, rs : 10365, ppm : 5.02

```