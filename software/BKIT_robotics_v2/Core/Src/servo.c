#include "servo.h"
#include "tim.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	const uint32_t servo_channel[] = {TIM_CHANNEL_3, TIM_CHANNEL_2, TIM_CHANNEL_1};

	/**
	 * @brief	init servo
	 * @param	servo_id: SERVO_1, SERVO_2, SERVO_3
	 *
	 * SERVO1: TIM_CHANNEL_3
	 * SERVO2: TIM_CHANNEL_2
	 * SERVO3: TIM_CHANNEL_1
	 */
	void initServo(const enum Servo servo_id)
	{
		HAL_TIM_PWM_Start(&htim4, servo_channel[servo_id]);
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
	void servoSetAngle(const enum Servo servo_id, uint16_t angle)
	{
		if (angle < 0)
		{
			angle = 0;
		}
		else if (angle > 180)
		{
			angle = 180;
		}

		uint16_t duty_cycle = (angle * 110) / 180 + 20;
		__HAL_TIM_SET_COMPARE(&htim4, servo_channel[servo_id], duty_cycle);
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */
