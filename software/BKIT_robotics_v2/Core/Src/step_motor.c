#include "step_motor.h"

#include "tim.h"
#include "gpio.h"
#include "line_sensor.h"

#define DUTY_CYCLE 50
#define SPR 200 // step per revolution (1 step correspond to 1.8 degrees)
#define MAX_REVOLUTIONS 10
#define THRESHOLD_SENSORS 2000

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	volatile int spr_counter = 0;
	volatile uint16_t current_step = 0;
	enum Step_Direction current_direction = 0;

	/*
	 * @brief	: move step motor
	 * @param	: direction: DOWN or UP
	 * @param	: cycle: number of revolution 10 is safe enough
	 */

	enum StatusCode stepMotorMove(enum Step_Direction direction, uint8_t cycle)
	{
		if (cycle == 0)
		{
			return STATUS_ERROR;
		}

		switch (direction)
		{
		case UP:
		{
			if (current_step >= MAX_REVOLUTIONS * SPR)
			{
				return STATUS_ERROR;
				break;
			}
			break;
		}

		case DOWN:
		{
			if (current_step <= 0)
			{
				return STATUS_ERROR;
				break;
			}
			break;
		}
		}

		HAL_GPIO_WritePin(SM_DIR_GPIO_Port, SM_DIR_Pin, direction);
		current_direction = direction;

		spr_counter = SPR * cycle;

		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, DUTY_CYCLE);

		if (HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1) != HAL_OK)
		{
			return STATUS_ERROR;
		}
		return STATUS_OK;
	}

	void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
	{
		if (htim->Instance == TIM3)
		{
			if (spr_counter > 0)
			{
				switch (current_direction)
				{
				case UP:
					if (current_step < MAX_REVOLUTIONS * SPR)
					{
						++current_step;
						--spr_counter;
					}
					else
					{
						spr_counter = 0;
					}

					break;
				case DOWN:
					if (current_step > 0)
					{
						--current_step;
						--spr_counter;
					}
					else
					{
						spr_counter = 0;
					}
					break;
				}
			}

			if (spr_counter <= 0)
			{
				HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
			}
		}
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */
