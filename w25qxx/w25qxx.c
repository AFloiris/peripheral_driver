#include "w25qxx.h"

static void w25qxx_CS(w25qxx_dev_t *dev, uint8_t value) { af_gpio_write(&dev->cs, value); }

static uint8_t w25qxx_spi_read(w25qxx_dev_t *dev, uint8_t *data, uint16_t len)
{
    return af_spi_read(&dev->spi, data, len);
}

static uint8_t w25qxx_spi_write(w25qxx_dev_t *dev, uint8_t *data, uint16_t len)
{
    return af_spi_write(&dev->spi, data, len);
}

static void w25qxx_write_enable(w25qxx_dev_t *dev)
{
    w25qxx_CS(dev, 0);
    w25qxx_spi_write(dev, &W25QXX_CMD_WRITE_ENABLE, 1);
    w25qxx_CS(dev, 1);
}

static uint8_t w25qxx_read_sr1(w25qxx_dev_t *dev)
{
    uint8_t data = 0;
    w25qxx_CS(dev, 0);
    w25qxx_spi_write(dev, &W25QXX_CMD_READ_SR1, 1);
    w25qxx_spi_read(dev, &data, 1);
    w25qxx_CS(dev, 1);
    return data;
}

static void w25qxx_wait_busy(w25qxx_dev_t *dev)
{
    while ((w25qxx_read_sr1(dev) & 0x01) == 0x01)
        ;
}

w25qxx_dev_t *w25qxx_open(af_spi_t spi, w25qxx_type_t type, af_gpio_t cs)
{
    w25qxx_dev_t *dev = (w25qxx_dev_t *)malloc(sizeof(w25qxx_dev_t));
    if (dev == NULL)
        return NULL;

    memset(dev, 0, sizeof(w25qxx_dev_t));
    dev->spi  = spi;
    dev->type = type;
    dev->cs   = cs;

    if (dev->spi.init == 0 && (af_spi_init(&dev->spi) != 0))
    {
        free(dev);
        return NULL;
    }

    if (dev->cs.init == 0 && (af_gpio_init(&dev->cs) != 0))
    {
        free(dev);
        return NULL;
    }
    return dev;
}

uint8_t w25qxx_close(w25qxx_dev_t *dev)
{
    if (dev == NULL)
        return 1;

    uint8_t ret = af_gpio_deinit(&dev->cs);
    if (ret != 0)
        ret = 2;

    ret = af_spi_deinit(&dev->spi);
    if (ret != 0)
        ret = 3;

    memset(dev, 0, sizeof(w25qxx_dev_t));
    free(dev);
    return ret;
}

uint8_t w25qxx_read(w25qxx_dev_t *dev, uint32_t mem_addr, uint8_t *data, uint32_t len)
{
    if (dev == NULL)
        return 1;

    uint8_t cmdAndAddr[4] = {W25QXX_CMD_READ_DATA, (mem_addr >> 16) & 0xFF, (mem_addr >> 8) & 0xFF, mem_addr & 0xFF};
    w25qxx_CS(dev, 0);
    w25qxx_spi_write(dev, cmdAndAddr, 4);
    w25qxx_spi_read(dev, data, len);
    w25qxx_CS(dev, 1);

    return 0;
}

uint8_t w25qxx_write(w25qxx_dev_t *dev, uint32_t mem_addr, uint8_t *data, uint32_t len)
{
    if (dev == NULL)
        return 1;

    uint8_t cmdAbdAddr[4] = {W25QXX_CMD_WRITE_PAGE, (mem_addr >> 16) & 0xFF, (mem_addr >> 8) & 0xFF, mem_addr & 0xFF};
    w25qxx_write_enable(dev);

    w25qxx_CS(dev, 0);
    w25qxx_spi_write(dev, cmdAbdAddr, 4);
    w25qxx_spi_write(dev, data, len);
    w25qxx_CS(dev, 1);
    w25qxx_wait_busy(dev);

    return 0;
}

uint8_t w25qxx_erase_sector(w25qxx_dev_t *dev, uint32_t mem_addr)
{
    if (dev == NULL)
        return 1;

    uint8_t cmdAbdAddr[4] = {W25QXX_CMD_ERASE_SECTOR, (mem_addr >> 16) & 0xFF, (mem_addr >> 8) & 0xFF, mem_addr & 0xFF};

    w25qxx_write_enable(dev);
    w25qxx_wait_busy(dev);

    w25qxx_CS(dev, 0);
    w25qxx_spi_write(dev, cmdAbdAddr, 4);
    w25qxx_CS(dev, 1);
    w25qxx_wait_busy(dev);

    return 0;
}