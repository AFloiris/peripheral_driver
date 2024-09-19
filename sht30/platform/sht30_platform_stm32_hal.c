#include "sht30_platform.h"

#include "i2c.h"

uint8_t sht30_platform_init(sht30_dev_t *dev)
{
    // MX_I2C1_Init();
    return 0;
}

uint8_t sht30_platform_deinit(sht30_dev_t *dev)
{
    //
    return 0;
}

uint8_t sht30_platform_i2c_read_addr16(sht30_dev_t *dev, uint16_t addr, uint16_t mem_addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, addr << 1 | 0x01, mem_addr, I2C_MEMADD_SIZE_16BIT, data, len, HAL_MAX_DELAY);
}