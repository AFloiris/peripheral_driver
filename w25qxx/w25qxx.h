#ifndef __AF_W25QXX_H__
#define __AF_W25QXX_H__

#include "af_gpio.h"
#include "af_spi.h"

#include "main.h"

typedef enum w25qxx_cmd   w25qxx_cmd_t;
typedef enum w25qxx_type  w25qxx_type_t;
typedef struct w25qxx_dev w25qxx_dev_t;

enum w25qxx_cmd {
    W25QXX_CMD_WRITE_ENABLE = 0x06U,
    W25QXX_CMD_READ_DATA    = 0x03U,
    W25QXX_CMD_WRITE_PAGE   = 0x02U,
    W25QXX_CMD_READ_SR1     = 0x05U,
    W25QXX_CMD_ERASE_SECTOR = 0x20U,
};

enum w25qxx_type {
    W25Q80  = 0XEF13U,
    W25Q16  = 0XEF14U,
    W25Q32  = 0XEF15U,
    W25Q64  = 0XEF16U,
    W25Q128 = 0XEF17U,
    W25Q256 = 0XEF18U,
};

struct w25qxx_dev {
    af_spi_t      spi;
    w25qxx_type_t type;
    af_gpio_t     cs;
};

w25qxx_dev_t *w25qxx_open(af_spi_t spi, w25qxx_type_t type, af_gpio_t cs);

uint8_t w25qxx_close(w25qxx_dev_t *dev);

uint8_t w25qxx_read(w25qxx_dev_t *dev, uint32_t mem_addr, uint8_t *data, uint32_t len);

uint8_t w25qxx_write(w25qxx_dev_t *dev, uint32_t mem_addr, uint8_t *data, uint32_t len);

uint8_t w25qxx_erase_sector(w25qxx_dev_t *dev, uint32_t mem_addr);

#endif