#ifndef __AF_SSD1306_PLATFORM_H__
#define __AF_SSD1306_PLATFORM_H__

#include "ssd1306.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t ssd1306_platform_init(ssd1306_dev_t *dev);
uint8_t ssd1306_platform_deinit(ssd1306_dev_t *dev);
uint8_t ssd1306_platform_i2c_write(ssd1306_dev_t *dev, uint8_t addr, uint8_t mem_addr, uint8_t *data, uint16_t len);
uint8_t ssd1306_platform_i2c_read(ssd1306_dev_t *dev, uint8_t addr, uint8_t mem_addr, uint8_t *data, uint16_t len);
uint8_t ssd1306_platform_spi_write(ssd1306_dev_t *dev, uint8_t *data, uint16_t len);
uint8_t ssd1306_platform_spi_read(ssd1306_dev_t *dev, uint8_t *data, uint16_t len);
uint8_t ssd1306_platform_delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* __AF_SSD1306_PLATFORM_H__ */
