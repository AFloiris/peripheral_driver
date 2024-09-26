#include "bh1750_platform.h"
#include "i2c.h"

uint8_t bh1750_platform_init(bh1750_dev_t *dev)
{
    //
    return 0;
}

uint8_t bh1750_platform_deinit(bh1750_dev_t *dev)
{
    //
    return 0;
}

uint8_t bh1750_platform_i2c_write(bh1750_dev_t *dev, uint8_t i2c_addr, uint8_t data)
{
    return HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1 | 0x00, &data, 1, 1000);
}

uint8_t bh1750_platform_i2c_read(bh1750_dev_t *dev, uint8_t i2c_addr, uint8_t *data, uint8_t len)
{
    return HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1 | 0x01, data, len, 1000);
}

uint8_t bh1750_platform_delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
    return 0;
}
