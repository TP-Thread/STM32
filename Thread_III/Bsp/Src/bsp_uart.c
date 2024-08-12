/**
 ******************************************************************************
 * @作  者  两点一线
 * @版  本  V1.0
 * @日  期  2023-1-18
 * @内  容  串口通信
 ******************************************************************************
 */

#include "bsp_uart.h"

/**
 * @简  述  重定义putc函数（USART1）
 * 重定向 c 库函数 printf 到串口，重定向后可使用 printf 函数
 */
int fputc(int ch, FILE *f)
{
    // 发送一个字节数据到串口
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return (ch);
}

/**
 * @简  述  重定义getc函数（USART6）
 * 重定向 c 库函数 scanf 到串口，重写向后可使用 scanf、getchar 等函数
 */
int fgetc(FILE *f)
{
    int ch;
    /* 等待串口输入数据 */
    while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == RESET)
        ;
    HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return (ch);
}
