#include "step_motor.h"

#define DUTY_CYCLE 50
#define SPR 200 // step per revolution

uint32_t spr_counter = 0;

/*
 * direction :	0	->	down
 * 			 :	1	->	up
 * cycle	 : 	10 is safe enough
 */

void move_step_motor(GPIO_PinState directtion, uint16_t cycle)
{
	HAL_GPIO_WritePin(SM_DIR_GPIO_Port, SM_DIR_Pin, directtion);
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
