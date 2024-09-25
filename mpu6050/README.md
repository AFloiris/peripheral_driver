# MPU6050

## 使用示例

### STM32

* STM32F407ZGT6
* HAL 库, STM32CubeMX
* I2C1
* MPU6050

1. 移植 `mpu6050.c` `mpu6050.h` `mpu6050_platform.h` `mpu6050_platform_stm32_hal.c` 到工程目录下
2. 根据实际情况修改 `mpu6050_platform_stm32_hal.c` 中的函数
3. 在 `main.c` 中调用 `mpu6050_test()` 函数
```C
#include "mpu6050.h"
#include <stdio.h>

void mpu6050_test(void)
{
    uint8_t        i   = 100;
    uint8_t        ret = 0;
    mpu6050_dev_t *dev = mpu6050_open(0x68);
    if (dev == NULL)
    {
        printf("mpu6050 open failed!\r\n");
        return;
    }
    while (i-- > 0)
    {
        ret = mpu6050_read(dev);
        if (ret)
        {
            printf("mpu6050 read failed!\r\n");
            mpu6050_close(dev);
            return;
        }
        printf("x_accel:%5d,y_accel:%5d,z_accel:%5d,x_gyro:%5d,y_gyro:%5d,z_gyro:%5d\r\n", dev->x_accel, dev->y_accel,
               dev->z_accel, dev->x_gyro, dev->y_gyro, dev->z_gyro);
    }
    mpu6050_close(dev);
}
```