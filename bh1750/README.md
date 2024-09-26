# bh1750


## 使用示例

### STM32

* STM32F407ZGT6
* HAL 库, STM32CubeMX
* GPIOD15
* bh1750

1. 移植 `bh1750.c` `bh1750.h` `bh1750_platform.h` `bh1750_platform_stm32_hal.c` 到工程目录下, `af_delay.h` `af_delay_platform_stm32_hal.c` 可选
2. 根据实际情况修改 `bh1750_platform_stm32_hal.c` 中的函数
3. 在 `main.c` 中调用 `bh1750_test()` 函数

```c
#include "bh1750.h"
#include <stdio.h>
void bh1750_test(void)
{
    uint8_t i   = 0;
    uint8_t err = 0;

    bh1750_dev_t *dev = bh1750_open(0x23);
    if (dev == NULL)
    {
        printf("bh1750 open failed\n");
        return;
    }

    err = bh1750_raed(dev, BH1750_READ_ONE_TIME_LOW_RES_MODE);
    if (err)
    {
        printf("bh1750 one time low res mode read failed\n");
        bh1750_close(dev);
        return;
    }
    printf("bh1750 one time low res mode read: %.2f lux\n", dev->lux);

    err = bh1750_raed(dev, BH1750_READ_ONE_TIME_HIGH_RES_MODE);
    if (err)
    {
        printf("bh1750 one time high res mode read failed\n");
        bh1750_close(dev);
        return;
    }
    printf("bh1750 one time high res mode read: %.2f lux\n", dev->lux);

    err = bh1750_raed(dev, BH1750_READ_ONE_TIME_HIGH_RES_MODE2);
    if (err)
    {
        printf("bh1750 one time high res mode2 read failed\n");
        bh1750_close(dev);
        return;
    }
    printf("bh1750 one time high res mode2 read: %.2f lux\n", dev->lux);

    err = bh1750_raed(dev, BH1750_READ_CONTINUOUS_LOW_RES_MODE);
    if (err)
    {
        printf("bh1750 continuous low res mode read failed\n");
        bh1750_close(dev);
        return;
    }
    printf("bh1750 continuous low res mode read: %.2f lux\n", dev->lux);

    err = bh1750_raed(dev, BH1750_READ_CONTINUOUS_HIGH_RES_MODE);
    if (err)
    {
        printf("bh1750 continuous high res mode read failed\n");
        bh1750_close(dev);
        return;
    }
    printf("bh1750 continuous high res mode read: %.2f lux\n", dev->lux);

    err = bh1750_raed(dev, BH1750_READ_CONTINUOUS_HIGH_RES_MODE2);
    if (err)
    {
        printf("bh1750 continuous high res mode2 read failed\n");
        bh1750_close(dev);
        return;
    }
    printf("bh1750 continuous high res mode2 read: %.2f lux\n", dev->lux);

    bh1750_close(dev);
}

```

运行结果
```
// TODO 待测试

```