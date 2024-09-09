#include "af_uart.h"

#include <string.h>

/* 全局变量存储串口句柄,用于中断处理 */
static uint8_t    af_uarts_cnt = 0;
static af_uart_t *af_uarts[4]  = {0};

/**
 * @brief 串口读取中断回调函数
 *
 * @param huart HAL库 串口句柄
 */
void af_uart_rx_irq_handler(UART_HandleTypeDef *huart)
{
    for (int i = 0; i < af_uarts_cnt; i++)
    {
        if (af_uarts[i]->huart == huart)
        {
            af_uart_t *uart = af_uarts[i];
            if (uart->rx_index < uart->rx_data_size)
            {
                uart->rx_data[uart->rx_index] = uart->rx_ch;
                uart->rx_index++;
                uart->rx_ch = 0;
                HAL_UART_Receive_IT(uart->huart, (uint8_t *)&uart->rx_ch, 1);
            }
        }
    }
}

/**
 * @brief hal 库中断处理函数
 *
 * @param huart HAL库 串口句柄
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) { af_uart_rx_irq_handler(huart); }

uint8_t af_uart_init(af_uart_t *uart)
{
    if (uart->huart == NULL || (uart->rx_mode == AF_UART_RX_MODE_IT && uart->rx_data_size == 0))
        return 1;
    uart->init = 1;
    if (uart->rx_mode == AF_UART_RX_MODE_IT)
    {
        /* 初始化串口接收中断 */
        uart->rx_ch    = 0;
        uart->rx_index = 0;
        memset(uart->rx_data, 0, sizeof(uart->rx_data_size));
        HAL_UART_Receive_IT(uart->huart, (uint8_t *)&uart->rx_ch, 1);
    }
    /* 将uart句柄存储到全局数组中 */
    af_uarts[af_uarts_cnt++] = uart;
    return 0;
}

uint8_t af_uart_deinit(af_uart_t *uart)
{
    if (uart->huart == NULL)
        return 1;

    uart->init = 0;
    /* 从全局数组中移除uart句柄 */
    for (int i = 0; i < af_uarts_cnt; i++)
    {
        if (af_uarts[i] == uart)
        {
            af_uarts[i] = 0;
            af_uarts_cnt--;
            break;
        }
    }
    return 0;
}

uint8_t af_uart_write(af_uart_t *uart, const uint8_t *data, size_t size)
{
    return HAL_UART_Transmit(uart->huart, (uint8_t *)data, size, HAL_MAX_DELAY);
}

uint8_t af_uart_read(af_uart_t *uart, uint8_t *data, size_t size)
{
    uint8_t ret = 0;
    if (uart->rx_mode == AF_UART_RX_MODE_BLOCKING)
    {
        ret = HAL_UART_Receive(uart->huart, data, size, HAL_MAX_DELAY);
    }
    else if (uart->rx_mode == AF_UART_RX_MODE_IT)
    {
        memcpy(data, uart->rx_data, uart->rx_data_size);
    }
    return ret;
}

uint8_t af_uart_clear_rx(af_uart_t *uart)
{
    if (uart->rx_mode == AF_UART_RX_MODE_IT)
    {
        memset(uart->rx_data, 0, uart->rx_data_size);
        uart->rx_data_size = 0;
        uart->rx_index     = 0;
    }
    return 0;
}

/*
//接下来三个函数实现 printf 到串口1
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}
 */
