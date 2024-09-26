# DHT11


## 使用示例

### STM32

* STM32F407ZGT6
* HAL 库, STM32CubeMX
* GPIOD15
* DHT11

1. 移植 `dht11.c` `dht11.h` `dht11_platform.h` `dht11_platform_stm32_hal.c` 到工程目录下, `af_delay.h` `af_delay_platform_stm32_hal.c` 可选
2. 根据实际情况修改 `dht11_platform_stm32_hal.c` 中的函数
3. 在 `main.c` 中调用 `dht11_test()` 函数

```c
#include "dht11.h"
#include <stdio.h>
void dht11_test(void)
{
    uint8_t i = 0;
    uint8_t ret = 0;

    dht11_dev_t *dev = dht11_open();
    if (dev == NULL)
    {
        printf("dht11 open failed\n");
        return;
    }

    while (i++ < 3)
    {
        ret = dht11_read(dev);
        if (ret)
        {
            printf("dht11 read failed ret : %d\n", ret);
            dht11_close(dev);
            return;
        }
        printf("[%d] raw [%d] [%d] [%d] [%d] [%d]\n",i, dev->data[0], dev->data[1], dev->data[2], dev->data[3], dev->data[4]);
        printf("[%d] humidity: %.2f\n", i, dev->humidity);
        printf("[%d] temperature: %.2f\n", i, dev->temperature);
        HAL_Delay(2000);
    }
    dht11_close(dev);
}


```

运行结果
```
# RECV ASCII/75 <<<
[1] raw [84] [0] [28] [5] [127]
[1] humidity: 84.00
[1] temperature: 28.50

# RECV ASCII/75 <<<
[2] raw [67] [0] [28] [0] [105]
[2] humidity: 67.00
[2] temperature: 28.00

# RECV ASCII/75 <<<
[3] raw [68] [0] [28] [0] [106]
[3] humidity: 68.00
[3] temperature: 28.00

```