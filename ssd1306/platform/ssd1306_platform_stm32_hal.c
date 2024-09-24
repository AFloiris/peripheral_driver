#include "i2c.h"
#include "ssd1306_platform.h"

uint8_t ssd1306_platform_init(ssd1306_dev_t *dev)
{
    //
    return 0;
}
uint8_t ssd1306_platform_deinit(ssd1306_dev_t *dev)
{
    //
    return 0;
}
uint8_t ssd1306_platform_i2c_write(ssd1306_dev_t *dev, uint8_t addr, uint8_t mem_addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Mem_Write(&hi2c1, addr, mem_addr, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}
uint8_t ssd1306_platform_i2c_read(ssd1306_dev_t *dev, uint8_t addr, uint8_t mem_addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, addr, mem_addr, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}

uint8_t ssd1306_platform_spi_write(ssd1306_dev_t *dev, uint8_t *data, uint16_t len)
{
    // todo
    return 0;
}
uint8_t ssd1306_platform_spi_read(ssd1306_dev_t *dev, uint8_t *data, uint16_t len)
{
    // todo
    return 0;
}
