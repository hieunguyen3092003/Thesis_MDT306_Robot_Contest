#include "servo.h"

#include "tim.h"

#define NUMBER_OF_SERVO 3

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	const uint32_t servo_channel[NUMBER_OF_SERVO] = {TIM_CHANNEL_3, TIM_CHANNEL_2, TIM_CHANNEL_1};

	/**
	 * @brief	init servo
	 * @param	servo_id: SERVO_1, SERVO_2, SERVO_3
	 *
	 * SERVO1: TIM_CHANNEL_3
	 * SERVO2: TIM_CHANNEL_2
	 * SERVO3: TIM_CHANNEL_1
	 */
	enum StatusCode initServo(const enum Servo servo_id)
	{
		for (uint8_t attempt = 0; attempt < MAX_RETRY_COUNT; ++attempt)
		{
			if (HAL_TIM_PWM_Start(&htim4, servo_channel[servo_id]) == HAL_OK)
			{
				return STATUS_OK;
			}

			HAL_Delay(50);
		}
		return STATUS_ERROR;
	}

	/**
	 * @brief	set servo angle range from 20 to 130 (0 to 180 degree)
	 * @param	servo_id: SERVO_1, SERVO_2, SERVO_3
	 * @param	angle: 0 to 180 degree
	 *
	 * SERVO1: TIM_CHANNEL_3
	 * SERVO2: TIM_CHANNEL_2
	 * SERVO3: TIM_CHANNEL_1
	 */
	void servoSetAngle(const enum Servo servo_id, uint8_t angle)
	{
		if (angle < 0)
		{
			angle = 0;
		}
		else if (angle > 55)
		{
			angle = 55;
		}

		uint16_t duty_cycle = (angle * 110) / 180 + 20;
		__HAL_TIM_SET_COMPARE(&htim4, servo_channel[servo_id], duty_cycle);
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */
