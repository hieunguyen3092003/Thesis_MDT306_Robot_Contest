#include "uart.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    uint8_t receive_buffer_1 = 0;
    uint8_t receive_buffer_2 = 0;
    uint8_t uart_1_flag = 0;
    uint8_t uart_2_flag = 0;

    void initUartIt()
    {
        HAL_UART_Receive_IT(&huart1, &receive_buffer_1, 1);
        HAL_UART_Receive_IT(&huart2, &receive_buffer_2, 1);
    }

    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
    {
        if (huart->Instance == USART1)
        {
            uart_1_flag = 1;
            HAL_UART_Receive_IT(&huart1, &receive_buffer_1, 1);
        }
        if (huart->Instance == USART2)
        {
            uart_1_flag = 1;
            HAL_UART_Receive_IT(&huart2, &receive_buffer_2, 1);
        }
    }

    uint8_t uart1GetFlag()
    {
        if (uart_1_flag)
        {
            uart_1_flag = 0;
            return 1;
        }
        return 0;
    }

    uint8_t uart2GetFlag()
    {
        if (uart_2_flag)
        {
            uart_2_flag = 0;
            return 1;
        }
        return 0;
    }

    uint8_t uart1GetData()
    {
        return receive_buffer_1;
    }

    uint8_t uart2GetData()
    {
        return receive_buffer_2;
    }

    HAL_StatusTypeDef uart1Send(uint8_t *data, uint16_t length)
    {
        if (data == NULL || length == 0)
        {
            return HAL_ERROR;
        }

        return HAL_UART_Transmit(&huart1, data, length, 100);
    }

    HAL_StatusTypeDef uart2Send(uint8_t *data, uint16_t length)
    {
        if (data == NULL || length == 0)
        {
            return HAL_ERROR;
        }

        return HAL_UART_Transmit(&huart2, data, length, 100);
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */