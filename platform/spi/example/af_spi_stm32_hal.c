#include "af_spi.h"

uint8_t af_spi_init(af_spi_t *spi)
{
    spi->init = 1;
    //
    return 0;
}
uint8_t af_spi_deinit(af_spi_t *spi)
{
    spi->init = 0;
    //
    return 0;
}
uint8_t af_spi_write(af_spi_t *spi, uint8_t *data, uint16_t len)
{
    return HAL_SPI_Transmit(spi->hspi, data, len, HAL_MAX_DELAY);
}
uint8_t af_spi_read(af_spi_t *spi, uint8_t *data, uint16_t len)
{
    return HAL_SPI_Receive(spi->hspi, data, len, HAL_MAX_DELAY);
}
uint8_t af_spi_write_read(af_spi_t *spi, uint8_t *tx_data, uint16_t tx_len, uint8_t *rx_data, uint16_t rx_len)
{
    return HAL_SPI_TransmitReceive(spi->hspi, tx_data, rx_data, tx_len, HAL_MAX_DELAY);
}
