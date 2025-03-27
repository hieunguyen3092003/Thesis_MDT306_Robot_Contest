//#include "joystick.h"
//
//uint16_t cal_ang(uint8_t value){
//	return ((value >> 3)*15);
//}
//
//void check_buffer_state() {
//	if(buffer[5] == 0x00 && buffer[6] == STOP_DATA){
//		move_state = STOP;
//		servo_state = SERVO_INACTIVE;
//		sm_state = SM_INACTIVE;
//	}
//	else if(buffer[5] == 0x00 && buffer[6] == FW_DATA) {
//		move_state = FORWARD;
//	}
//	else if(buffer[5] == 0x00 && buffer[6] == BW_DATA) {
//		move_state = BACKWARD;
//	}
//	else if(buffer[5] == 0x00 && buffer[6] == LT_DATA) {
//		move_state = LEFT;
//	}
//	else if(buffer[5] == 0x00 && buffer[6] == RT_DATA) {
//		move_state = RIGHT;
//	}
//	if(buffer[5] == 0x04 && buffer[6] == 0x00){ // TRIANGLE
//		sm_state = UP_SM;
//	}
//	else if(buffer[5] == 0x10 && buffer[6] == 0x00){ // X
//		sm_state = DOWN_SM;
//	}
//	else if(buffer[5] == 0x08 && buffer[6] == 0x00){ // CIRCLE
//		servo_state = SERVO_CLOSE;
//	}
//	else if(buffer[5] == 0x20 && buffer[6] == 0x00){ // SQUARE
//		servo_state = SERVO_OPEN;
//	}else if(buffer[5] == BZ_DATA && buffer[6] == 0x00){ //BUTTON START
//		move_state = BUZZER;
//	}
//}
//
///*
// * Joystick
// *
// */
//void check_buffer_state_1() {
//	uint16_t ang = cal_ang(buffer[6]);
//	if (buffer[5] == 0x00 && buffer[6] == STOP_DATA){
//		move_state = STOP;
//	}
//	else if (ang > 45 && ang <= 135){
//		move_state = FORWARD;
//	}
//	else if (ang <= 225){
//		move_state = LEFT;
//	}
//	else if (ang <= 315){
//		move_state = BACKWARD;
//	}
//	else if (ang <= 45 || ang >315){
//		move_state = RIGHT;
//	}
//}
