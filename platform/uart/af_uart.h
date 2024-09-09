#ifndef __AF_UART_H__
#define __AF_UART_H__

#include "main.h"

typedef struct af_uart       af_uart_t;
typedef enum af_uart_rx_mode af_uart_rx_mode_t;

enum af_uart_rx_mode {
    AF_UART_RX_MODE_BLOCKING, /* 阻塞读取 */
    AF_UART_RX_MODE_IT,       /* 中断读取 */
};

struct af_uart {
    uint8_t           init;         /* 初始化 */
    af_uart_rx_mode_t rx_mode;      /* 接收模式 */
    uint32_t          baudrate;     /* 波特率 */
    uint8_t          *rx_data;      /* 接收数据缓冲 */
    uint8_t           rx_ch;        /* 接收字符 */
    uint16_t          rx_data_size; /* 接收数据大小 */
    uint16_t          rx_index;     /* 接收索引 */
#if defined(USE_HAL_DRIVER)
    UART_HandleTypeDef *huart;
#endif
};

uint8_t af_uart_init(af_uart_t *uart);
uint8_t af_uart_deinit(af_uart_t *uart);
uint8_t af_uart_write(af_uart_t *uart, const uint8_t *data, size_t size);
uint8_t af_uart_read(af_uart_t *uart, uint8_t *data, size_t size);
uint8_t af_uart_clear_rx(af_uart_t *uart);

#endif /* __AF_UART_H__ */