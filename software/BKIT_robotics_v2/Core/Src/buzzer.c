#include "buzzer.h"
#include "tim.h"

#define TIMER_CLOCK_HZ 72000000
#define MAX_TIMER_COUNT 65535

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	/**
	 *@brief Initializes the buzzer by starting the PWM signal.
	 *@return STATUS_OK if successful, STATUS_ERROR otherwise.
	 */
	enum StatusCode initBuzzer()
	{
		for (uint8_t attempt = 0; attempt < MAX_RETRY_COUNT; ++attempt)
		{
			if (HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1) == HAL_OK)
			{
				return STATUS_OK;
			}
			HAL_Delay(50);
		}

		return STATUS_ERROR;
	}

	/**
	 * @brief Sets the frequency of the buzzer.
	 *
	 */
	void setFreqBuzzer(const uint32_t frequency)
	{
		if (frequency <= 0)
		{
			// Nếu tần số bằng 0, dừng buzzer
			HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1);
			return;
		}

		uint32_t prescaler = 1;
		uint32_t period = (TIMER_CLOCK_HZ / prescaler / frequency) - 1;

		while (period > MAX_TIMER_COUNT && prescaler < MAX_TIMER_COUNT)
		{
			++prescaler;
			period = (TIMER_CLOCK_HZ / prescaler / frequency) - 1;
		}

		if (period > MAX_TIMER_COUNT)
		{
			// If timer capacity is still exceeded, do nothing
			return;
		}

		__HAL_TIM_SET_PRESCALER(&htim5, prescaler);
		__HAL_TIM_SET_AUTORELOAD(&htim5, period);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, period / 2);

		HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
	}

	void stopBuzzer()
	{
		HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1);
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */