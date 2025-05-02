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

	uint32_t spr_counter = 0;
	uint8_t current_revolution = 0;

	/**
	 * @note This function should be called in setup and run once only!
	 */
	enum StatusCode calibStepMotor()
	{
		sensorScan();

		if (getSensorValue()[0] > THRESHOLD_SENSORS && getSensorValue()[7] > THRESHOLD_SENSORS)
		{
			while (getSensorValue()[0] > THRESHOLD_SENSORS && getSensorValue()[7] > THRESHOLD_SENSORS)
			{
				stepMotorMove(DOWN, 1);
				HAL_Delay(10000);
				sensorScan();
			}

			stepMotorMove(DOWN, 1);
		}
		else if (getSensorValue()[0] > THRESHOLD_SENSORS || getSensorValue()[7] > THRESHOLD_SENSORS)
		{
			stepMotorMove(DOWN, 1);
		}

		current_revolution = 0;

		return STATUS_OK;
	}

	/*
	 * @brief	: move step motor
	 * @param	: direction: DOWN or UP
	 * @param	: cycle: number of revolution 10 is safe enough
	 */

	enum StatusCode stepMotorMove(enum Step_Direction direction, uint16_t cycle)
	{
		if (cycle > (MAX_REVOLUTIONS - current_revolution))
		{
			cycle = MAX_REVOLUTIONS - current_revolution;
		}
		else if (current_revolution == 0)
		{
			cycle = 0;
		}

		HAL_GPIO_WritePin(SM_DIR_GPIO_Port, SM_DIR_Pin, direction);
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
			spr_counter--;
			if (spr_counter <= 0)
				HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
		}
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */
