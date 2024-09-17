#include "af_i2c.h"

static uint16_t af_mem_addr_size_to_hal(af_mem_addr_size_t size)
{
    switch (size)
    {
    case AF_MEM_ADDR_SIZE_8BIT:
        return I2C_MEMADD_SIZE_8BIT;

    case AF_MEM_ADDR_SIZE_16BIT:
        return I2C_MEMADD_SIZE_16BIT;

    default:
        return I2C_MEMADD_SIZE_8BIT;
    }
}

uint8_t af_i2c_init(af_i2c_t *i2c)
{
    i2c->init = 1;
    //
    return 0;
}

void af_i2c_deinit(af_i2c_t *i2c)
{
    i2c->init = 0;
    //
}

uint8_t af_i2c_write(af_i2c_t *i2c, uint16_t addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Master_Transmit(i2c->hi2c, addr, data, len, HAL_MAX_DELAY);
}

uint8_t af_i2c_read(af_i2c_t *i2c, uint16_t addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Master_Receive(i2c->hi2c, addr, data, len, HAL_MAX_DELAY);
}

uint8_t af_i2c_mem_write(af_i2c_t *i2c, uint16_t addr, uint16_t mem_addr, af_mem_addr_size_t mem_addr_size,
                         uint8_t *data, uint16_t len)
{
    uint16_t hal_mem_addr_size = af_mem_addr_size_to_hal(mem_addr_size);
    return HAL_I2C_Mem_Write(i2c->hi2c, addr, mem_addr, hal_mem_addr_size, data, len, HAL_MAX_DELAY);
}

uint8_t af_i2c_mem_read(af_i2c_t *i2c, uint16_t addr, uint16_t mem_addr, af_mem_addr_size_t mem_addr_size,
                        uint8_t *data, uint16_t len)
{
    uint16_t hal_mem_addr_size = af_mem_addr_size_to_hal(mem_addr_size);
    return HAL_I2C_Mem_Read(i2c->hi2c, addr, mem_addr, hal_mem_addr_size, data, len, HAL_MAX_DELAY);
}
