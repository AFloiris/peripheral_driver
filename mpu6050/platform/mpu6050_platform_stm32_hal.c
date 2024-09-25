#include "i2c.h"
#include "mpu6050_platform.h"

uint8_t mpu6050_platform_init(mpu6050_dev_t *dev)
{
    //
    return 0;
}
uint8_t mpu6050_platform_deinit(mpu6050_dev_t *dev)
{
    //
    return 0;
}
uint8_t mpu6050_platform_i2c_write(mpu6050_dev_t *dev, uint8_t i2c_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Mem_Write(&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}
uint8_t mpu6050_platform_i2c_read(mpu6050_dev_t *dev, uint8_t i2c_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}
