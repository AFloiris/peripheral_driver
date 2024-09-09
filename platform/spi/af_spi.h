#ifndef __AF_SPI_H__
#define __AF_SPI_H__

#include "main.h"

typedef struct af_spi af_spi_t;

struct af_spi {
    uint8_t init; /* 初始化 */
#if defined(USE_HAL_DRIVER)
    SPI_HandleTypeDef *hspi;
    SPI_InitTypeDef    spi_init;
#endif
};

uint8_t af_spi_init(af_spi_t *spi);
uint8_t af_spi_deinit(af_spi_t *spi);
uint8_t af_spi_write(af_spi_t *spi, uint8_t *data, uint16_t len);
uint8_t af_spi_read(af_spi_t *spi, uint8_t *data, uint16_t len);
uint8_t af_spi_write_read(af_spi_t *spi, uint8_t *tx_data, uint16_t tx_len, uint8_t *rx_data, uint16_t rx_len);

#endif /* __AF_SPI_H__ */
