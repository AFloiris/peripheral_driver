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
    uint8_t        i   = 30;
    uint8_t        ret = 0;
    uint8_t        id  = 0;
    mpu6050_dev_t *dev = mpu6050_open(0x3, 0x03, 0x68);
    if (dev == NULL)
    {
        printf("mpu6050 open failed!\r\n");
        return;
    }
    ret = mpu6050_get_id(dev, &id);
    if (ret)
    {
        printf("mpu6050 get id failed!\r\n");
        mpu6050_close(dev);
        return;
    }
    printf("mpu6050 id:%d\r\n", id);
    while (i-- > 0)
    {
        ret = mpu6050_read_data(dev);
        if (ret)
        {
            printf("mpu6050 read failed!\r\n");
            mpu6050_close(dev);
            return;
        }
        printf("x_accel:%7.2f,y_accel:%7.2f,z_accel:%7.2f,x_gyro:%7.2f,y_gyro:%7.2f,z_gyro:%7.2f,temp:%7.2f\r\n", dev->x_accel,
               dev->y_accel, dev->z_accel, dev->x_gyro, dev->y_gyro, dev->z_gyro, dev->temp);
    }
    mpu6050_close(dev);
}
```
运行结果：
```
mpu6050 id is 104
x_accel:   0.13,y_accel:  -0.01,z_accel:   0.97,x_gyro:  -8.11,y_gyro:  -4.09,z_gyro:   0.18,temp:  28.28
x_accel:   0.14,y_accel:  -0.04,z_accel:   0.99,x_gyro: -13.48,y_gyro:  -7.13,z_gyro:  -5.91,temp:  28.29
x_accel:   0.16,y_accel:  -0.06,z_accel:   0.95,x_gyro: -14.76,y_gyro:   1.40,z_gyro:   0.98,temp:  28.29
x_accel:   0.15,y_accel:  -0.05,z_accel:   0.98,x_gyro:   5.43,y_gyro: -10.91,z_gyro:  14.82,temp:  28.29
x_accel:   0.14,y_accel:  -0.02,z_accel:   1.06,x_gyro:   3.66,y_gyro: -22.93,z_gyro:  -0.18,temp:  28.28
x_accel:   0.24,y_accel:   0.19,z_accel:   1.01,x_gyro: 124.88,y_gyro:-177.80,z_gyro: -20.67,temp:  28.29
x_accel:   0.60,y_accel:   0.25,z_accel:   0.58,x_gyro:   0.67,y_gyro:-247.62,z_gyro:  12.32,temp:  28.29
x_accel:   0.94,y_accel:   0.21,z_accel:   0.16,x_gyro: -42.20,y_gyro:-182.01,z_gyro:  46.40,temp:  28.28
x_accel:   1.06,y_accel:   0.02,z_accel:  -0.07,x_gyro: -28.90,y_gyro: -80.85,z_gyro:  43.41,temp:  28.29
x_accel:   1.07,y_accel:   0.03,z_accel:  -0.06,x_gyro:  13.72,y_gyro:  -2.13,z_gyro:  -4.88,temp:  28.30
x_accel:   1.06,y_accel:   0.02,z_accel:  -0.03,x_gyro:   3.17,y_gyro:  -4.70,z_gyro:   7.99,temp:  28.30
x_accel:   1.06,y_accel:   0.04,z_accel:  -0.05,x_gyro: -10.18,y_gyro:  -9.76,z_gyro:  16.46,temp:  28.30
x_accel:   1.00,y_accel:  -0.08,z_accel:  -0.11,x_gyro: -73.48,y_gyro: -16.04,z_gyro: 141.59,temp:  28.31
x_accel:   0.89,y_accel:  -0.42,z_accel:  -0.20,x_gyro:-223.35,y_gyro:  -8.41,z_gyro: 186.71,temp:  28.32
x_accel:   0.52,y_accel:  -0.47,z_accel:  -0.74,x_gyro:-434.27,y_gyro:-143.29,z_gyro: 248.23,temp:  28.32
x_accel:   0.08,y_accel:   0.30,z_accel:  -1.17,x_gyro:-395.98,y_gyro:-237.50,z_gyro:  86.71,temp:  28.33
x_accel:  -0.06,y_accel:   0.61,z_accel:  -0.87,x_gyro:-114.82,y_gyro:-125.61,z_gyro:  73.35,temp:  28.34
x_accel:  -0.08,y_accel:   0.63,z_accel:  -0.82,x_gyro:   3.66,y_gyro:  -5.98,z_gyro:  15.55,temp:  28.34
x_accel:  -0.07,y_accel:   0.64,z_accel:  -0.83,x_gyro:   1.34,y_gyro:  -1.95,z_gyro:  -3.35,temp:  28.34
x_accel:  -0.05,y_accel:   0.61,z_accel:  -0.86,x_gyro:  41.95,y_gyro:  34.63,z_gyro:  -0.85,temp:  28.35
x_accel:   0.01,y_accel:   0.51,z_accel:  -0.99,x_gyro: 113.54,y_gyro:  87.99,z_gyro: -44.45,temp:  28.36
x_accel:   0.24,y_accel:   0.16,z_accel:  -1.13,x_gyro: 284.76,y_gyro: 220.61,z_gyro: -70.49,temp:  28.37
x_accel:   0.67,y_accel:  -0.48,z_accel:  -0.55,x_gyro: 953.90,y_gyro:  84.94,z_gyro:-213.54,temp:  28.39
x_accel:   0.90,y_accel:   0.46,z_accel:  -0.07,x_gyro: 535.43,y_gyro:-151.22,z_gyro:-273.48,temp:  28.40
x_accel:   0.65,y_accel:   0.65,z_accel:  -0.43,x_gyro: 242.80,y_gyro: -74.70,z_gyro:-209.51,temp:  28.41
x_accel:   0.35,y_accel:   0.70,z_accel:  -0.87,x_gyro: 269.51,y_gyro: -50.24,z_gyro:-175.30,temp:  28.43
x_accel:   0.11,y_accel:   0.31,z_accel:  -1.14,x_gyro: 171.71,y_gyro: -64.09,z_gyro:-115.67,temp:  28.44
x_accel:   0.10,y_accel:   0.12,z_accel:  -1.07,x_gyro:  29.76,y_gyro:  22.07,z_gyro: -11.22,temp:  28.46
x_accel:   0.13,y_accel:   0.06,z_accel:  -1.06,x_gyro:  -0.98,y_gyro:  -2.74,z_gyro:   9.63,temp:  28.47
x_accel:   0.13,y_accel:   0.05,z_accel:  -1.06,x_gyro: -12.20,y_gyro:  -6.83,z_gyro:  13.05,temp:  28.47

```