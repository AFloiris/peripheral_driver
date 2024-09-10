#include "at24cxx.h"

static uint8_t at24cxx_i2c_write(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint8_t len)
{
    uint8_t ret;
    ret = af_i2c_mem_write(&dev->i2c, dev->addr << 1 | 0x00, mem_addr, MEM_ADDR_SIZE_8BIT, data, len);
    return ret;
}

static uint8_t at24cxx_i2c_write_addr16(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint8_t len)
{
    uint8_t ret;
    ret = af_i2c_mem_write(&dev->i2c, dev->addr << 1 | 0x00, mem_addr, MEM_ADDR_SIZE_16BIT, data, len);
    return ret;
}

static uint8_t at24cxx_i2c_read(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint8_t len)
{
    uint8_t ret;
    ret = af_i2c_mem_read(&dev->i2c, dev->addr << 1 | 0x00, mem_addr, MEM_ADDR_SIZE_8BIT, data, len);
    return ret;
}

static uint8_t at24cxx_i2c_read_addr16(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint8_t len)
{
    uint8_t ret;
    ret = af_i2c_mem_read(&dev->i2c, dev->addr << 1 | 0x00, mem_addr, MEM_ADDR_SIZE_16BIT, data, len);
    return ret;
}

at24cxx_dev_t *at24cxx_open(af_i2c_t i2c, at24cxx_type_t type, uint8_t addr)
{
    at24cxx_dev_t *dev = (at24cxx_dev_t *)malloc(sizeof(at24cxx_dev_t));
    if (dev != NULL)
    {
        memset(dev, 0, sizeof(at24cxx_dev_t));
        dev->i2c  = i2c;
        dev->type = type;
        dev->addr = addr;
    }
    if (dev->i2c.init == 0)
        af_i2c_init(&dev->i2c);

    return dev;
}

void at24cxx_close(at24cxx_dev_t *dev)
{
    if (dev == NUll)
        return;
    af_i2c_deinit(&dev->i2c);
    memset(dev, 0, sizeof(at24cxx_dev_t));
    free(dev);
}

uint8_t at24cxx_write(at24cxx_dev_t *dev, uint32_t mem_addr, uint8_t *data, uint8_t len)
{
    if (dev == NULL)
        return 1;

    if (mem_addr + len > dev->type)
        return 2;

    uint8_t page_remain = ((uint8_t)(8 - mem_addr % 8) >= len) ? len : (uint8_t)(8 - mem_addr % 8);
    if (dev->type > AT24C512)
    {
        while (1)
        {
            if (at24cxx_i2c_write_addr16(dev, mem_addr, data, len) != 0)
                return 3;

            af_delay_ms(6);
            if (page_remain == len)
                break;
            else
            {
                mem_addr += page_remain;
                data += page_remain;
                len -= page_remain;
                if (len < 8)
                    page_remain = (uint8_t)len;
                else
                    page_remain = 8;
            }
        }
    }
    else if (dev->type > AT24C16)
    {
        while (1)
        {
            if (at24cxx_i2c_write_addr16(dev, mem_addr, data, len) != 0)
                return 3;

            af_delay_ms(6);
            if (page_remain == len)
                break;
            else
            {
                mem_addr += page_remain;
                data += page_remain;
                len -= page_remain;
                if (len < 8)
                    page_remain = (uint8_t)len;
                else
                    page_remain = 8;
            }
        }
    }
    else
    {
        while (1)
        {
            if (at24cxx_i2c_write(dev, mem_addr, data, len) != 0)
                return 3;

            af_delay_ms(6);
            if (page_remain == len)
                break;
            else
            {
                mem_addr += page_remain;
                data += page_remain;
                len -= page_remain;
                if (len < 8)
                    page_remain = (uint8_t)len;
                else
                    page_remain = 8;
            }
        }
    }
    return 0;
}

uint8_t at24cxx_read(at24cxx_dev_t *dev, uint32_t mem_addr, uint8_t *data, uint8_t len)
{
    if (dev == NULL)
        return 1;

    if (mem_addr + len > dev->type)
        return 2;

    uint8_t page_remain = ((uint8_t)(8 - mem_addr % 8) >= len) ? len : (uint8_t)(8 - mem_addr % 8);
    if (dev->type > AT24C512)
    {
        while (1)
        {
            if (at24cxx_i2c_read_addr16(dev, mem_addr, data, len) != 0)
                return 3;

            if (page_remain == len)
                break;
            else
            {
                mem_addr += page_remain;
                data += page_remain;
                len -= page_remain;
                if (len < 8)
                    page_remain = (uint8_t)len;
                else
                    page_remain = 8;
            }
        }
    }
    else if (dev->type > AT24C16)
    {
        while (1)
        {
            if (at24cxx_i2c_read_addr16(dev, mem_addr, data, len) != 0)
                return 3;

            if (page_remain == len)
                break;
            else
            {
                mem_addr += page_remain;
                data += page_remain;
                len -= page_remain;
                if (len < 8)
                    page_remain = (uint8_t)len;
                else
                    page_remain = 8;
            }
        }
    }
    else
    {
        while (1)
        {
            if (at24cxx_i2c_read(dev, mem_addr, data, len) != 0)
                return 3;

            if (page_remain == len)
                break;
            else
            {
                mem_addr += page_remain;
                data += page_remain;
                len -= page_remain;
                if (len < 8)
                    page_remain = (uint8_t)len;
                else
                    page_remain = 8;
            }
        }
    }
    return 0;
}