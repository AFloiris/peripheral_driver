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
x_accel:   0.44,y_accel:  -0.06,z_accel:   0.91,x_gyro:  -7.50,y_gyro:  -4.70,z_gyro:   1.22,temp: 223.81
x_accel:   0.46,y_accel:  -0.09,z_accel:   0.88,x_gyro: -28.96,y_gyro: -15.98,z_gyro:  -3.29,temp: 223.81
x_accel:   0.49,y_accel:  -0.23,z_accel:   0.88,x_gyro:-130.55,y_gyro: -30.12,z_gyro: -38.05,temp: 223.82
x_accel:   0.68,y_accel:  -0.54,z_accel:   0.62,x_gyro:-386.46,y_gyro:-109.02,z_gyro:-146.83,temp: 223.82
x_accel:   0.87,y_accel:  -0.37,z_accel:   0.00,x_gyro:-311.77,y_gyro: -80.00,z_gyro:-202.68,temp: 223.82
x_accel:   0.96,y_accel:   0.22,z_accel:  -0.29,x_gyro:-260.73,y_gyro: -54.76,z_gyro:-189.09,temp: 223.82
x_accel:   0.89,y_accel:   0.53,z_accel:  -0.36,x_gyro:  54.45,y_gyro:  -3.60,z_gyro: -81.28,temp: 223.82
x_accel:   0.82,y_accel:   0.44,z_accel:  -0.54,x_gyro: 102.62,y_gyro:   9.76,z_gyro: -24.63,temp: 223.84
x_accel:   0.87,y_accel:   0.27,z_accel:  -0.54,x_gyro: 271.34,y_gyro:  80.00,z_gyro: -11.22,temp: 223.84
x_accel:   0.99,y_accel:   0.01,z_accel:  -0.40,x_gyro: 228.60,y_gyro: 135.30,z_gyro:  22.87,temp: 223.85
x_accel:   0.99,y_accel:   0.14,z_accel:   0.04,x_gyro:  58.35,y_gyro:  41.22,z_gyro:-112.07,temp: 223.85
x_accel:   0.92,y_accel:   0.15,z_accel:  -0.30,x_gyro: 105.67,y_gyro:-142.56,z_gyro: -99.27,temp: 223.86
x_accel:   0.79,y_accel:   0.36,z_accel:  -0.81,x_gyro:  57.50,y_gyro:-130.73,z_gyro: -88.17,temp: 223.85
x_accel:   0.69,y_accel:  -0.04,z_accel:  -1.18,x_gyro:  52.87,y_gyro:  22.80,z_gyro:  37.07,temp: 223.85
x_accel:   0.65,y_accel:   0.11,z_accel:  -0.56,x_gyro: -71.16,y_gyro: 314.88,z_gyro: -10.37,temp: 223.86
x_accel:   0.71,y_accel:   0.20,z_accel:   0.32,x_gyro: 304.76,y_gyro: 394.70,z_gyro:  44.45,temp: 223.86
x_accel:   0.57,y_accel:   0.47,z_accel:   0.64,x_gyro:   8.29,y_gyro: 172.32,z_gyro:-114.76,temp: 223.87
x_accel:   0.23,y_accel:   0.48,z_accel:   0.85,x_gyro: -70.98,y_gyro: 161.83,z_gyro: -39.70,temp: 223.85
x_accel:   0.02,y_accel:   0.20,z_accel:   1.21,x_gyro: -75.49,y_gyro:  45.91,z_gyro:  -5.55,temp: 223.86
x_accel:   0.06,y_accel:   0.31,z_accel:   1.08,x_gyro: 388.54,y_gyro: -51.59,z_gyro: 116.10,temp: 223.85
x_accel:   0.49,y_accel:   0.77,z_accel:   0.15,x_gyro: 317.74,y_gyro:-102.13,z_gyro: 147.44,temp: 223.85
x_accel:   0.68,y_accel:   0.55,z_accel:  -0.40,x_gyro: 393.17,y_gyro: -21.40,z_gyro:  96.52,temp: 223.84
x_accel:   0.80,y_accel:  -0.10,z_accel:  -0.55,x_gyro: 225.79,y_gyro: -12.32,z_gyro:  92.32,temp: 223.85
x_accel:   0.63,y_accel:  -0.46,z_accel:  -0.78,x_gyro:  87.13,y_gyro:-109.27,z_gyro:  39.15,temp: 223.87
x_accel:   0.48,y_accel:  -0.46,z_accel:  -0.92,x_gyro:  22.62,y_gyro: -86.95,z_gyro:   2.99,temp: 223.89
x_accel:   0.41,y_accel:  -0.43,z_accel:  -1.02,x_gyro: -11.83,y_gyro: -38.78,z_gyro:  -3.66,temp: 223.92
x_accel:   0.43,y_accel:  -0.10,z_accel:  -1.15,x_gyro:-430.55,y_gyro: 115.37,z_gyro:  19.39,temp: 223.96
x_accel:   0.62,y_accel:   0.42,z_accel:  -0.42,x_gyro:-855.98,y_gyro:  -7.74,z_gyro: 181.59,temp: 223.95
x_accel:   0.81,y_accel:  -0.18,z_accel:   0.03,x_gyro:-510.73,y_gyro: -28.35,z_gyro: 122.56,temp: 223.93
x_accel:   0.73,y_accel:  -0.59,z_accel:   0.39,x_gyro:  76.52,y_gyro: 157.62,z_gyro: 147.26,temp: 223.92
```