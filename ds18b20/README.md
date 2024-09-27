# DS18B20


## 使用示例

### STM32

* STM32F407ZGT6
* HAL 库, STM32CubeMX
* GPIOD15
* DS18B20

1. 移植 `ds18b20.c` `ds18b20.h` `ds18b20_platform.h` `ds18b20_platform_stm32_hal.c` 到工程目录下, `af_delay.h` `af_delay_platform_stm32_hal.c` 可选
2. 根据实际情况修改 `ds18b20_platform_stm32_hal.c` 中的函数
3. 在 `main.c` 中调用 `ds18b20_test()` 函数

```c
#include "ds18b20.h"
#include <stdio.h>
void ds18b20_test(void)
{
    uint8_t i   = 0;
    uint8_t ret = 0;

    ds18b20_dev_t *dev = ds18b20_open();
    if (dev == NULL)
    {
        printf("ds18b20 open failed\n");
        return;
    }

    while (i++ < 3)
    {
        ret = ds18b20_read(dev);
        if (ret)
        {
            printf("ds18b20 read failed ret : %d\n", ret);
            ds18b20_close(dev);
            return;
        }
        printf("ds18d20 raw data [0]: 0x%X  [1]: 0x%X\n", dev->raw_data[0], dev->raw_data[1]);
        printf("ds18d20 temperature : %.2f\n", dev->temperature);
        HAL_Delay(2000);
    }
    ds18b20_close(dev);
}

```

运行结果
```
// TODO 待测试

```