#include "software_timer.h"

#include "tim.h"

#include "display.h"
#include "encoder.h"

#define TIMER_2_CYCLES 1

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	uint8_t timer_2_flag = 0;
	uint16_t timer_2_counter = 0;
	uint16_t timer_2_mul = 0;

	/**
	 * @brief	init timer function
	 */
	enum StatusCode initTimer2()
	{
		for (uint8_t attempt = 0; attempt < MAX_RETRY_COUNT; ++attempt)
		{
			if (HAL_TIM_Base_Start_IT(&htim2) == HAL_OK)
			{
				return STATUS_OK;
			}

			HAL_Delay(50);
		}
		return STATUS_ERROR;
	}

	/**
	 * @brief	set timer duration(ms)
	 * @param	delay(ms)
	 * @param	period(ms)
	 */
	void sTimer2Set(uint16_t delay, uint16_t period)
	{
		timer_2_mul = period / TIMER_2_CYCLES;
		timer_2_counter = delay / TIMER_2_CYCLES;
		timer_2_flag = 0;
	}

	/**
	 * @brief	get flag timer fuction and auto reset flags and timer counter
	 * @return	timer flag
	 */
	uint8_t sTimer2GetFlag()
	{
		if (timer_2_flag)
		{
			timer_2_flag = 0;
			timer_2_counter = timer_2_mul;
			return 1;
		}
		return 0;
	}

	/**
	 * @brief	callback function call every 1ms
	 */
	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
		if (htim->Instance == TIM2)
		{
			if (timer_2_counter > 0)
			{
				--timer_2_counter;
			}
			if (timer_2_counter <= 0)
			{
				timer_2_flag = 1;
			}

			displayScan();
			scanEncoder();
		}
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */
