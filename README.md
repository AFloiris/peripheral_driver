# peripheral driver 外设驱动库

本仓库为外设驱动库, 包含了各种外设的驱动, 包括传感器, 显示屏, 存储器等.

**只针对与外设的简单驱动和使用, 不包含复杂的算法和数据处理.**

基本保证在 STM32 HAL 库的使用, 但做了平台化处理, 简单修改即可移植到其他平台.

## 框架介绍

### 文件结构

每一个外设驱动基本包含四个文件: `driver.h`, `driver.c`, `driver_platform.h`, `driver_platform.c`

`driver.h` : 外设驱动设备头文件, 包含了外设驱动的接口函数和结构体定义  
`driver.c` : 外设驱动设备源文件, 包含了外设驱动的接口函数实现, 内部调用 `driver_platform.h` 中的函数, 实现了平台无关性  
`driver_platform.h` : 外设驱动平台头文件, 包含了改外设驱动需要的一些平台函数声明  
`driver_platform.c` : 外设驱动平台源文件, 包含了改外设驱动需要的一些平台函数实现  

所以在移植时, 只需要修改 `driver_platform.c` 中的函数即可.

### 接口函数

每一个外设驱动基本包含以下几个接口函数:

- `driver_dev_t* driver_open(...)` : 初始化外设驱动  
- `uint8_t driver_close(driver_dev_t* dev)` : 关闭外设驱动  
- `uint8_t driver_read(driver_dev_t* dev, ...)` : 读取外设数据  
- `uint8_t driver_write(driver_dev_t* dev, ...)` : 写入外设数据  

然后基于不同外设的特性, 可能会添加一些其他的接口函数, 具体可以参考每个外设驱动的文档.

## 仓库计划

[ 已完成 ] : 驱动已完成, 且已进行实物测试, 有运行结果  

[ 待测试 ] : 驱动已完成, 但未进行实物测试  

[ 开发中 ] : 驱动正在开发中  

[ 计划中 ] : 计划开发, 但不一定开发  

### 温湿度传感器

[ 已完成 ] : [DHT11](./dht11/README.md)  
[ 计划中 ] : DHT22  

[ 已完成 ] : [SHT3x](./sht3x/README.md) (已测: SHT310)

[ 待测试 ] : [DS18B20](./ds18b20/README.md)

[ 计划中 ] : AHT10
[ 计划中 ] : AHT20

[ 计划中 ] : HTS221

[ 计划中 ] : MLX90614


### 距离传感器

[ 待测试 ] : [HC-SR04](./hc_sr04/README.md)



### 光照传感器

[ 待测试 ] : [BH1750](./bh1750/README.md)


### 气体传感器

[ 已完成 ] : [MQX 系列](./mqx/README.md) (已测: MQ5, 但未补充其他公式)


### 姿态传感器

[ 已完成 ] : [MPU6050](./mpu6050/README.md)

### 压力传感器

[ 计划中 ] : HX711


### 磁力传感器

[ 计划中 ] : HMC5883L


### 电流功率传感器

[ 计划中 ] : INA226


### 显示屏

[ 已完成 ] : [SSD1306](./ssd1306/README.md) (已测: 128x64 I2C)

[ 计划中 ] : ST7735

[ 计划中 ] : ILI9341



### 存储器

[ 已完成 ] : [AT24CXX](./at24cxx/README.md) (已测: AT24C02)

[ 开发中 ] : W25QXX


### 摄像头

[ 计划中 ] : OV2640


### 片上外设

[ 计划中 ] : SW_I2C

[ 计划中 ] : SW_SPI