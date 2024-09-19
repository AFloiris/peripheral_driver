#include "at24cxx.h"
#include "at24cxx_platform.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief 初始化
 * @note  平台相关
 */
static uint8_t at24cxx_init(at24cxx_dev_t *dev) { return at24cxx_platform_init(dev); }

/**
 * @brief 反初始化
 * @note  平台相关
 */
static uint8_t at24cxx_deinit(at24cxx_dev_t *dev) { return at24cxx_platform_deinit(dev); }

/**
 * @brief at24cxx i2c 写入
 *
 * @param dev           at24cxx设备
 * @param mem_addr      写入内存地址
 * @param data          写入数据
 * @param len           写入数据长度
 * @return uint8_t  0:成功，其他：失败
 *
 * @note 平台相关
 */
static uint8_t at24cxx_i2c_write(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint16_t len)
{
    if (dev->type >= AT24C64)
    {
        return at24cxx_platform_i2c_write_addr16(dev, dev->addr, mem_addr, data, len);
    }
    return at24cxx_platform_i2c_write(dev, dev->addr, mem_addr & 0xff, data, len);
}

/**
 * @brief at24cxx i2c 读取
 *
 * @param dev           at24cxx设备
 * @param mem_addr      读取内存地址
 * @param data          读取数据
 * @param len           读取数据长度
 * @return uint8_t  0:成功，其他：失败
 *
 * @note 平台相关
 */
static uint8_t at24cxx_i2c_read(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint16_t len)
{
    if (dev->type >= AT24C64)
    {
        return at24cxx_platform_i2c_read_addr16(dev, dev->addr, mem_addr, data, len);
    }
    return at24cxx_platform_i2c_read(dev, dev->addr, mem_addr & 0xff, data, len);
}

/**
 * @brief 延时函数
 * @note 平台相关
 */
static void at24cxx_delay_ms(uint32_t ms) { at24cxx_platform_delay_ms(ms); }

/**
 * @brief 获取页大小
 */
static at24cxx_page_size_t at24cxx_get_page_size(at24cxx_type_t type)
{
    switch (type)
    {
    case AT24C01:
        return AT24C01_PAGE_SIZE;
    case AT24C02:
        return AT24C02_PAGE_SIZE;
    case AT24C04:
        return AT24C04_PAGE_SIZE;
    case AT24C08:
        return AT24C08_PAGE_SIZE;
    case AT24C16:
        return AT24C16_PAGE_SIZE;
    case AT24C32:
        return AT24C32_PAGE_SIZE;
    case AT24C64:
        return AT24C64_PAGE_SIZE;
    case AT24C128:
        return AT24C128_PAGE_SIZE;
    case AT24C256:
        return AT24C256_PAGE_SIZE;
    case AT24C512:
        return AT24C512_PAGE_SIZE;
    case AT24CM01:
        return AT24CM01_PAGE_SIZE;
    case AT24CM02:
        return AT24CM02_PAGE_SIZE;
    default:
        return AT24C01_PAGE_SIZE;
    }
}

at24cxx_dev_t *at24cxx_open(uint8_t addr, at24cxx_type_t type)
{
    at24cxx_dev_t *dev = (at24cxx_dev_t *)malloc(sizeof(at24cxx_dev_t));
    if (dev == NULL)
        return NULL;

    memset(dev, 0, sizeof(at24cxx_dev_t));
    dev->type      = type;
    dev->addr      = addr;
    dev->page_size = at24cxx_get_page_size(type);

    if (at24cxx_init(dev) != 0)
    {
        free(dev);
        return NULL;
    }
    return dev;
}

uint8_t at24cxx_close(at24cxx_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    if (at24cxx_deinit(dev) != 0)
        return 2;

    memset(dev, 0, sizeof(at24cxx_dev_t));
    free(dev);
    return 0;
}

uint8_t at24cxx_write(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint16_t len)
{
    if (dev == NULL)
        return 1;

    if (mem_addr + len > dev->type)
        return 2;

    /* 页大小 */
    uint16_t page_size = (uint16_t)dev->page_size;

    /* 计算页剩余字节数 */
    uint16_t page_remain = (uint8_t)(page_size - mem_addr % page_size);
    if (page_remain > len)
        page_remain = (uint16_t)len;

    while (1)
    {
        /* 写入数据 */
        if (at24cxx_i2c_write(dev, mem_addr, data, page_remain) != 0)
            return 4;

        /* 页读写延时 */
        at24cxx_delay_ms(7);

        /* 数据写入完成 */
        if (page_remain == len)
            break;

        /* 页地址递增 */
        mem_addr += page_remain;
        data += page_remain;
        len -= page_remain;
        if (len < page_size)
        {
            page_remain = (uint16_t)len;
        }
        else
        {
            page_remain = (uint16_t)page_size;
        }
    }

    return 0;
}

uint8_t at24cxx_read(at24cxx_dev_t *dev, uint16_t mem_addr, uint8_t *data, uint16_t len)
{
    if (dev == NULL)
        return 1;

    if (mem_addr + len > dev->type)
        return 2;

    /* 页大小 */
    uint16_t page_size = (uint16_t)dev->page_size;

    /* 计算页剩余字节数 */
    uint16_t page_remain = (uint8_t)(page_size - mem_addr % page_size);
    if (page_remain > len)
        page_remain = (uint16_t)len;

    while (1)
    {
        /* 读取数据 */
        if (at24cxx_i2c_read(dev, mem_addr, data, page_remain) != 0)
            return 4;

        /* 页读写延时 */
        at24cxx_delay_ms(7);
        /* 数据读取完成 */
        if (page_remain == len)
            break;

        /* 页地址递增 */
        mem_addr += page_remain;
        data += page_remain;
        len -= page_remain;
        if (len < page_size)
        {
            page_remain = (uint16_t)len;
        }
        else
        {
            page_remain = (uint16_t)page_size;
        }
    }
    return 0;
}
