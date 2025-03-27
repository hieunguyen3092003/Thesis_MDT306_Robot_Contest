//#include "uart.h"
//
//uint8_t receive_buffer1 = 0;
//uint8_t buffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//uint8_t idx = 0;
//uint8_t move_state = STOP;
//uint8_t uart_state = WAITING;
//
//uint8_t servo_state = SERVO_INACTIVE;
//uint8_t sm_state = SM_INACTIVE;
//
//int servo_degree = 0;
//int sm_height = 0;
//
//void uart_init()
//{
//	HAL_UART_Receive_IT(&huart2, &receive_buffer1, 1);
//	HAL_UART_Receive_IT(&huart1, &receive_buffer1, 1);
//	move_state = STOP;
//	servo_state = SERVO_INACTIVE;
//	sm_state = SM_INACTIVE;
//	uart_state = WAITING;
//}
//
//void clear_buffer()
//{
//	for (uint8_t i = 0; i < 8; i++)
//	{
//		buffer[i] = 0x00;
//	}
//	idx = 0;
//}
//
//void check_function()
//{
//	if (buffer[1] == 0x00)
//	{
//		move_state = STOP;
//		servo_state = SERVO_INACTIVE;
//		sm_state = SM_INACTIVE;
//	}
//	else if (buffer[2] == DIGITAL_MODE)
//	{
//		check_buffer_state();
//	}
//	else if (buffer[2] == JOYSTICK_MODE || buffer[2] == ACCELE_MODE)
//	{
//		if (buffer[5] == 0x00 && buffer[6] == STOP_DATA)
//		{
//			move_state = STOP;
//			servo_state = SERVO_INACTIVE;
//			sm_state = SM_INACTIVE;
//		}
//		else if (buffer[5] == 0x04 && buffer[6] == 0x00)
//		{ // TRIANGLE
//			sm_state = UP_SM;
//		}
//		else if (buffer[5] == 0x10 && buffer[6] == 0x00)
//		{ // X
//			sm_state = DOWN_SM;
//		}
//		else if (buffer[5] == 0x08 && buffer[6] == 0x00)
//		{ // CIRCLE
//			servo_state = SERVO_CLOSE;
//		}
//		else if (buffer[5] == 0x20 && buffer[6] == 0x00)
//		{ // SQUARE
//			servo_state = SERVO_OPEN;
//		}
//		else if (buffer[5] == BZ_DATA && buffer[6] == 0x00)
//		{
//			move_state = BUZZER;
//		}
//		else
//		{
//			check_buffer_state_1();
//		}
//	}
//}
//
//void uart_process()
//{
//	switch (uart_state)
//	{
//	case WAITING:
//	{
//		if (receive_buffer1 == 0xFF)
//		{
//			idx = 0;
//			buffer[idx] = receive_buffer1;
//			idx = (idx + 1) % 8;
//			uart_state = RECEIVE;
//		}
//		break;
//	}
//	case RECEIVE:
//	{
//		buffer[idx] = receive_buffer1;
//		idx = (idx + 1) % 8;
//		if (idx == 7)
//			uart_state = CHECK;
//		break;
//	}
//	case CHECK:
//	{
//		HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
//		check_function();
//		clear_buffer();
//		uart_state = WAITING;
//		break;
//	}
//	default:
//	{
//		break;
//	}
//	}
//}
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if (huart->Instance == USART1)
//	{
//		//		if(buffer[0] == 0xFF)
//		//			HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
//		uart_process();
//		//		HAL_UART_Transmit(&huart2, buffer, 8, 10);
//		HAL_UART_Receive_IT(&huart1, &receive_buffer1, 1);
//	}
//}
//
//void move_process()
//{
//	switch (move_state)
//	{
//	case STOP:
//	{
//		stop();
//		buzzer_set_duty_cycle(0);
//		move_state = IDLE;
//		break;
//	}
//	case FORWARD:
//	{
//		forward(MIN_SPEED);
//		break;
//	}
//	case BACKWARD:
//	{
//		backwards(MIN_SPEED);
//		break;
//	}
//	case LEFT:
//	{
//		rotateLeft(MIN_SPEED);
//		break;
//	}
//	case RIGHT:
//	{
//		rotateRight(MIN_SPEED);
//		break;
//	}
//	case BUZZER:
//		buzzer_set_duty_cycle(50);
//		break;
//	case IDLE:
//		// do nothing
//		break;
//	default:
//	{
//		break;
//	}
//	}
//}
//
//void servo_process()
//{
//	switch (servo_state)
//	{
//	case SERVO_OPEN:
//		servo_degree += 5;
//		if (servo_degree >= 60)
//			servo_degree = 60;
//		servo_set_angle(3, servo_degree);
//		break;
//	case SERVO_CLOSE:
//		servo_degree -= 5;
//		if (servo_degree <= 0)
//			servo_degree = 0;
//		servo_set_angle(3, servo_degree);
//		break;
//	case SERVO_INACTIVE:
//		// do nothing
//		break;
//	default:
//		break;
//	}
//}
//
//void sm_process()
//{
//	switch (sm_state)
//	{
//	case UP_SM:
//		sm_height += 1;
//		if (sm_height >= 35)
//			sm_height = 35;
//		else
//			move_step_motor(1, 1);
//		break;
//	case DOWN_SM:
//		sm_height -= 1;
//		if (sm_height <= 0)
//			sm_height = 0;
//		else
//			move_step_motor(0, 1);
//		break;
//	case SM_INACTIVE:
//		// do nothing
//		break;
//	default:
//		break;
//	}
//}
