#ifndef __AF_SPI_H__
#define __AF_SPI_H__

#include <stdint.h>

#include "stm32f4xx_hal.h" /* STM32F4xx HAL */

typedef struct af_spi af_spi_t;

struct af_spi {
    uint8_t init; /* 初始化 */
#if defined(USE_HAL_DRIVER)
    SPI_HandleTypeDef *hspi;
    SPI_InitTypeDef    spi_init;
#endif
};

/**
 * @brief spi 初始化
 *
 * @param spi spi 设备
 * @return uint8_t 0:成功 其他:失败
 */
uint8_t af_spi_init(af_spi_t *spi);

/**
 * @brief spi 反初始化
 *
 * @param spi spi 设备
 */
void af_spi_deinit(af_spi_t *spi);

/**
 * @brief spi 写数据
 *
 * @param spi   spi 设备
 * @param data  写入数据
 * @param len   写入数据
 * @return uint8_t  0:成功 其他:失败
 */
uint8_t af_spi_write(af_spi_t *spi, uint8_t *data, uint16_t len);

/**
 * @brief spi 读数据
 *
 * @param spi   spi 设备
 * @param data  读取数据
 * @param len   读取数据
 * @return uint8_t  0:成功 其他:失败
 */
uint8_t af_spi_read(af_spi_t *spi, uint8_t *data, uint16_t len);

/**
 * @brief spi 写读数据
 *
 * @param spi       spi 设备
 * @param tx_data   写入数据
 * @param tx_len    写入数据长度
 * @param rx_data   读取数据
 * @param rx_len    读取数据长度
 * @return uint8_t  0:成功 其他:失败
 */
uint8_t af_spi_write_read(af_spi_t *spi, uint8_t *tx_data, uint16_t tx_len, uint8_t *rx_data, uint16_t rx_len);

#endif /* __AF_SPI_H__ */
