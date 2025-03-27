#include "encoder.h"

GPIO_TypeDef* ENCODER_A_GPIO[4] = {ENCODER1_A_GPIO_Port, ENCODER2_A_GPIO_Port, ENCODER3_A_GPIO_Port, ENCODER4_A_GPIO_Port};
uint16_t ENCODER_A_PIN[4] = {ENCODER1_A_Pin, ENCODER2_A_Pin, ENCODER3_A_Pin, ENCODER4_A_Pin};

GPIO_TypeDef* ENCODER_B_GPIO[4] = {ENCODER1_B_GPIO_Port, ENCODER2_B_GPIO_Port, ENCODER3_B_GPIO_Port, ENCODER4_B_GPIO_Port};
uint16_t ENCODER_B_PIN[4] = {ENCODER1_B_Pin, ENCODER2_B_Pin, ENCODER3_B_Pin, ENCODER4_B_Pin};

int32_t encoder_pulse[4] = {0,0,0,0};
uint8_t state[4] = {0,0,0,0};

void read_encoder_data(){
	for (uint8_t i = 0; i < 4; i++){
		switch (state[i]) {
//			case STATE_00:
//				if(!HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					encoder_pulse[i] += 1;
//					state[i] = STATE_01;
//				}else if(HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && !HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					encoder_pulse[i] -= 1;
//					state[i] = STATE_10;
//				}else if(HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					state[i] = STATE_11;
//				}else if(!HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && !HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					state[i] = STATE_00;
//				}
//				break;
//			case STATE_01:
//				if(HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					encoder_pulse[i] += 1;
//					state[i] = STATE_11;
//				}else if(!HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && !HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					encoder_pulse[i] -= 1;
//					state[i] = STATE_00;
//				}else if(HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && !HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					state[i] = STATE_10;
//				}else if(!HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					state[i] = STATE_01;
//				}
//				break;
//			case STATE_11:
//				if(HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && !HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					encoder_pulse[i] += 1;
//					state[i] = STATE_10;
//				}else if(!HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					encoder_pulse[i] -= 1;
//					state[i] = STATE_01;
//				}else if(HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					state[i] = STATE_11;
//				}else if(!HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && !HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					state[i] = STATE_00;
//				}
//				break;
//			case STATE_10:
//				if(!HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && !HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					encoder_pulse[i] += 1;
//					state[i] = STATE_00;
//				}else if(HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					encoder_pulse[i] -= 1;
//					state[i] = STATE_11;
//				}else if(HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && !HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					state[i] = STATE_10;
//				}else if(!HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i]) && HAL_GPIO_ReadPin(ENCODER_B_GPIO[i], ENCODER_B_PIN[i])){
//					state[i] = STATE_01;
//				}
//				break;
//			default:
//				state[i]=STATE_00;
//				break;
			case 0:
				if(HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i])) {
					state[i] = 1;
					encoder_pulse[i]++;
				}
				else {
					state[i] = 0;
				}
			case 1:
				if(!HAL_GPIO_ReadPin(ENCODER_A_GPIO[i], ENCODER_A_PIN[i])) {
					state[i] = 0;
				}
				else {
					state[i] = 1;
				}
		}
	}
}
