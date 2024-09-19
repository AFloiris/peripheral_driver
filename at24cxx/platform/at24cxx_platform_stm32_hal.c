#include "at24cxx_platform.h"

#include "i2c.h"

uint8_t at24cxx_platform_init(at24cxx_dev_t *dev)
{
    // MX_I2C1_Init();
    return 0;
}

uint8_t at24cxx_platform_deinit(at24cxx_dev_t *dev)
{
    //
    return 0;
}

uint8_t at24cxx_platform_i2c_write(at24cxx_dev_t *dev, uint8_t addr, uint8_t mem_addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Mem_Write(&hi2c1, addr << 1 | 0x00, mem_addr, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

uint8_t at24cxx_platform_i2c_read(at24cxx_dev_t *dev, uint8_t addr, uint8_t mem_addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, addr << 1 | 0x01, mem_addr, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

uint8_t at24cxx_platform_i2c_write_addr16(at24cxx_dev_t *dev, uint8_t addr, uint16_t mem_addr, uint8_t *data,
                                          uint16_t len)
{
    return HAL_I2C_Mem_Write(&hi2c1, addr << 1 | 0x00, mem_addr, I2C_MEMADD_SIZE_16BIT, data, len, HAL_MAX_DELAY);
}

uint8_t at24cxx_platform_i2c_read_addr16(at24cxx_dev_t *dev, uint8_t addr, uint16_t mem_addr, uint8_t *data,
                                         uint16_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, addr << 1 | 0x01, mem_addr, I2C_MEMADD_SIZE_16BIT, data, len, HAL_MAX_DELAY);
}

void at24cxx_platform_delay_ms(uint32_t ms) { HAL_Delay(ms); }
