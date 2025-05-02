#include "button.h"

#include "spi.h"
#include "gpio.h"

#define NUMBER_OF_BUTTON 4
#define BUTTON_HOLD_THRESHOLD 40 // 40 * 50ms = 2000ms = 2s

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	uint8_t button_counter[NUMBER_OF_BUTTON] = {0};
	uint8_t button_buffer = 0b00000000;

	/**
	 * @brief  	Init matrix button
	 * @note  	Call once at the beginning
	 */
	enum StatusCode initButton()
	{
		HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 1);
		HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 0);
		HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 1);

		if (HAL_SPI_Receive(&hspi1, (void *)&button_buffer, 1, 10) == HAL_OK)
		{
			return STATUS_OK;
		}
		return STATUS_ERROR;
	}

	/**
	 * @brief  	Scan matrix button
	 * @note  	Call every 50ms (in interrupt or timer) to update button state
	 */
	enum StatusCode scanButton()
	{
		HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 0);
		HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 1);

		if (HAL_SPI_Receive(&hspi1, (void *)&button_buffer, 1, 10) != HAL_OK)
		{
			return STATUS_ERROR;
		}

		for (uint8_t i = 0; i < NUMBER_OF_BUTTON; ++i)
		{
			if (button_buffer & (0b00000001 << i))
			{
				button_counter[i] = 0;
			}
			else
				++button_counter[i];
		}

		return STATUS_OK;
	}

	/**
	 * @brief  	Check if button is pressed and handle button hold
	 * @param  	button_id: button id
	 * @retval 	1: pressed or hold every 2s, 0: not pressed
	 */
	uint8_t isButtonPressed(const enum Button button_id)
	{
		if (button_counter[button_id] > BUTTON_HOLD_THRESHOLD)
		{
			button_counter[button_id] = 1;
		}

		if (button_counter[button_id] == 1)
		{
			return 1;
		}
		return 0;
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */