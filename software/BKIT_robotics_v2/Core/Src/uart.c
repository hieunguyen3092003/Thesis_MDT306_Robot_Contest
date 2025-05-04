#include "uart.h"
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	uint8_t receive_buffer_1 = 0;
	volatile uint8_t uart_1_flag = 0;

	uint8_t receive_buffer_2 = 0;
	volatile uint8_t uart_2_flag = 0;

	/**
	 * @brief UART receive function
	 * @param huart &huart1 or // &huart2
	 */
	enum StatusCode initUartReceiveIT(UART_HandleTypeDef *huart)
	{
		for (uint8_t attempt = 0; attempt < MAX_RETRY_COUNT; ++attempt)
		{
			if (huart->Instance == USART1)
			{
				if (HAL_UART_Receive_IT(&huart1, &receive_buffer_1, 1) == HAL_OK)
				{
					return STATUS_OK;
				}
			}
			else if (huart->Instance == USART2)
			{
				if (HAL_UART_Receive_IT(&huart2, &receive_buffer_2, 1) == HAL_OK)
				{
					return STATUS_OK;
				}
			}
			else
			{
				return STATUS_ERROR;
			}

			HAL_Delay(50);
		}
		return STATUS_ERROR;
	}

	/**
	 * @brief UART transmit function
	 * @param huart &huart1 or // &huart2
	 * @param str The string to be transmitted
	 * @note str sould be < 100 character
	 */
	enum StatusCode uartTransmitString(UART_HandleTypeDef *huart, const char *str)
	{
		for (uint8_t attempt = 0; attempt < MAX_RETRY_COUNT; ++attempt)
		{
			if (HAL_UART_Transmit(huart, (uint8_t *)str, strlen(str), strlen(str) * 2) == HAL_OK)
			{
				return STATUS_OK;
			}
			HAL_Delay(50);
		}
		return STATUS_ERROR;
	}

	enum StatusCode uartTransmit8b(UART_HandleTypeDef *huart, const uint8_t *array, const uint16_t size)
	{
		if (array == NULL || size == 0)
		{
			return STATUS_ERROR;
		}

		for (uint8_t attempt = 0; attempt < MAX_RETRY_COUNT; ++attempt)
		{
			if (HAL_UART_Transmit(huart, array, size, size * 2) == HAL_OK)
			{
				return STATUS_OK;
			}
			HAL_Delay(50);
		}
		return STATUS_ERROR;
	}

	uint8_t getFlagUart1()
	{
		if (uart_1_flag)
		{
			uart_1_flag = 0;
			return 1;
		}
		return 0;
	}

	uint8_t getFlagUart2()
	{

		if (uart_2_flag)
		{
			uart_2_flag = 0;
			return 1;
		}
		return 0;
	}

	uint8_t getBufferUart1()
	{
		return receive_buffer_1;
	}

	uint8_t getBufferUart2()
	{
		return receive_buffer_2;
	}

	/**
	 * @brief UART receive complete callback
	 * @brief This function is evoked automatically when the UART peripheral received data send through uart and echo its back
	 *
	 * @param huart The UART handle
	 */
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
		if (huart->Instance == USART1)
		{
			uart_1_flag = 1;
			// turn back on the receice interrupt
			HAL_UART_Receive_IT(&huart1, &receive_buffer_1, 1);
		}
		if (huart->Instance == USART2)
		{
			uart_2_flag = 1;
			// turn back on the receice interrupt
			HAL_UART_Receive_IT(&huart2, &receive_buffer_2, 1);
		}
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */