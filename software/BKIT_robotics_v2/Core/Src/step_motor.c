#include "step_motor.h"
#include "tim.h"
#include "gpio.h"

#define DUTY_CYCLE 50
#define SPR 200 // step per revolution

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	uint32_t spr_counter = 0;

	/*
	 * @brief	: move step motor
	 * @param	: direction: DOWN or UP
	 * @param	: cycle: number of revolution
	 */

	void stepMotorMove(enum Step_Direction direction, uint16_t cycle)
	{
		HAL_GPIO_WritePin(SM_DIR_GPIO_Port, SM_DIR_Pin, direction);
		spr_counter = SPR * cycle;

		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, DUTY_CYCLE);
		HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	}

	void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
	{
		if (htim->Instance == TIM3)
		{
			spr_counter--;
			if (spr_counter <= 0)
				HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
		}
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */