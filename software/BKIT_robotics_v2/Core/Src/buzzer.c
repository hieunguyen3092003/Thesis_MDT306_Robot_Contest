#include "tim.h"
#include "buzzer.h"

uint8_t buzzer_duty_cycle = 0;

void buzzer_init() {
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
}

void buzzer_set_duty_cycle(uint8_t duty_cycle) {
	buzzer_duty_cycle = duty_cycle;
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, buzzer_duty_cycle);
}
