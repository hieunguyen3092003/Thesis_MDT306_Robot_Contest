#include "motor.h"
#include "tim.h"
#include "gpio.h"
#include "button.h"

#define MIN_SPEED 19.5
#define MAX_SPEED 30

#define UP 1
#define DOWN 0

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	const uint32_t motor_channel[] = {TIM_CHANNEL_4, TIM_CHANNEL_3, TIM_CHANNEL_1, TIM_CHANNEL_2};

	void initMotor(const enum Motor motor_id)
	{
		HAL_TIM_PWM_Start(&htim8, motor_channel[motor_id]);
	}

	void setSpeed(const enum Motor motor_id, uint8_t duty_cycle)
	{
		if (duty_cycle > 100)
		{
			duty_cycle = 100;
		}
		else if (duty_cycle < 0)
		{
			duty_cycle = 0;
		}

		__HAL_TIM_SET_COMPARE(&htim8, motor_channel[motor_id], duty_cycle);
	}

	/**
	 * @brief	move dc motor
	 * @param	speed: -100 to 100
	 * @note	positive duty_cycle: move forward
	 * 			negative duty_cycle: move backward
	 */
	void motor1Rotates(const int speed)
	{
		if (speed >= 0)
		{
			HAL_GPIO_WritePin(M1_DIR_GPIO_Port, M1_DIR_Pin, UP);
			setSpeed(MOTOR_1, speed);
		}
		if (speed < 0)
		{
			HAL_GPIO_WritePin(M1_DIR_GPIO_Port, M1_DIR_Pin, DOWN);
			setSpeed(MOTOR_1, -speed);
		}
	}

	void motor2Rotates(const int speed)
	{
		if (speed >= 0)
		{
			HAL_GPIO_WritePin(M2_DIR_GPIO_Port, M2_DIR_Pin, UP);
			setSpeed(MOTOR_2, speed);
		}
		if (speed < 0)
		{
			HAL_GPIO_WritePin(M2_DIR_GPIO_Port, M2_DIR_Pin, DOWN);
			setSpeed(MOTOR_2, -speed);
		}
	}

	void motor3Rotates(const int speed)
	{
		if (speed >= 0)
		{
			HAL_GPIO_WritePin(M3_DIR_GPIO_Port, M3_DIR_Pin, UP);
			setSpeed(MOTOR_3, speed);
		}
		if (speed < 0)
		{
			HAL_GPIO_WritePin(M3_DIR_GPIO_Port, M3_DIR_Pin, DOWN);
			setSpeed(MOTOR_3, -speed);
		}
	}

	void motor4Rotates(const int speed)
	{
		if (speed >= 0)
		{
			HAL_GPIO_WritePin(M4_DIR_GPIO_Port, M4_DIR_Pin, UP);
			setSpeed(MOTOR_4, speed);
		}
		if (speed < 0)
		{
			HAL_GPIO_WritePin(M4_DIR_GPIO_Port, M4_DIR_Pin, DOWN);
			setSpeed(MOTOR_4, -speed);
		}
	}

	void motorStop()
	{
		motor1Rotates(0);
		motor2Rotates(0);
		motor3Rotates(0);
		motor4Rotates(0);
	}

	//                   forward
	//           frontLeft   |  frontRight          ↺: rotateLeft
	//         left		  ---+----     right		↻: rotateRight
	//           backLeft    |  backRight
	//                  backwards
	//

	void moveForward(const int speed)
	{
		motor1Rotates(speed);
		motor2Rotates(speed);
		motor3Rotates(speed);
		motor4Rotates(speed);
	}
	void moveBackward(const int speed)
	{
		motor1Rotates(-speed);
		motor2Rotates(-speed);
		motor3Rotates(-speed);
		motor4Rotates(-speed);
	}
	void moveLeft(const int speed)
	{
		motor1Rotates(-speed);
		motor2Rotates(speed);
		motor3Rotates(speed);
		motor4Rotates(-speed);
	}
	void moveRight(const int speed)
	{
		motor1Rotates(speed);
		motor2Rotates(-speed);
		motor3Rotates(-speed);
		motor4Rotates(speed);
	}

	void moveFrontLeft(const int speed)
	{
		motor1Rotates(0);
		motor2Rotates(speed);
		motor3Rotates(speed);
		motor4Rotates(0);
	}

	void moveFrontRight(const int speed)
	{
		motor1Rotates(speed);
		motor2Rotates(0);
		motor3Rotates(0);
		motor4Rotates(speed);
	}

	void moveBackLeft(const int speed)
	{
		motor1Rotates(-speed);
		motor2Rotates(0);
		motor3Rotates(0);
		motor4Rotates(-speed);
	}

	void moveBackRight(const int speed)
	{
		motor1Rotates(0);
		motor2Rotates(-speed);
		motor3Rotates(-speed);
		motor4Rotates(0);
	}

	void rotateLeft(const int speed)
	{
		motor1Rotates(-speed);
		motor2Rotates(-speed);
		motor3Rotates(speed);
		motor4Rotates(speed);
	}

	void rotateRight(const int speed)
	{
		motor1Rotates(speed);
		motor2Rotates(speed);
		motor3Rotates(-speed);
		motor4Rotates(-speed);
	}

	void moveDirection(const enum Direction direction, const int speed)
	{
		switch (direction)
		{
		case STOP:
		{
			motorStop();
			break;
		}
		case FORWARD:
		{
			moveForward(speed);
			break;
		}
		case BACKWARD:
		{
			moveBackward(speed);
			break;
		}
		case LEFT:
		{
			moveLeft(speed);
			break;
		}
		case RIGHT:
		{
			moveRight(speed);
			break;
		}
		case FRONT_LEFT:
		{
			moveFrontLeft(speed);
			break;
		}
		case FRONT_RIGHT:
		{
			moveFrontRight(speed);
			break;
		}
		case BACK_LEFT:
		{
			moveBackLeft(speed);
			break;
		}
		case BACK_RIGHT:
		{
			moveBackRight(speed);
			break;
		}
		case ROTATE_LEFT:
		{
			rotateLeft(speed);
			break;
		}
		case ROTATE_RIGHT:
		{
			rotateRight(speed);
			break;
		}
		}
	}

	// void followLine()
	// {
	// 	static int last_line_state = 0;
	// 	uint8_t line_state = SensorGetLine();
	// 	switch (line_state)
	// 	{
	// 	case LINE_CENTER:
	// 		if (last_line_state == LINE_CENTER)
	// 		{
	// 			forward(MAX_SPEED);
	// 		}
	// 		else
	// 		{
	// 			forward(MIN_SPEED);
	// 		}
	// 		break;
	// 	case LINE_LEFT1:
	// 		runSpeed(MIN_SPEED, MIN_SPEED * 1.25);
	// 		break;
	// 	case LINE_LEFT2:
	// 		runSpeed(0, MIN_SPEED);
	// 		break;
	// 	case LINE_LEFT3:
	// 		runSpeed(-MIN_SPEED, MIN_SPEED);
	// 		break;
	// 	case LINE_RIGHT1:
	// 		runSpeed(MIN_SPEED * 1.25, MIN_SPEED);
	// 		break;
	// 	case LINE_RIGHT2:
	// 		runSpeed(MIN_SPEED, 0);
	// 		break;
	// 	case LINE_RIGHT3:
	// 		runSpeed(MIN_SPEED, -MIN_SPEED);
	// 		break;
	// 	default:
	// 		stop();
	// 		break;
	// 	}
	// }

	// int followLineUntilCross()
	// {
	// 	//	static int status = 0;
	// 	//	uint8_t line_state = SensorGetLine();
	// 	//	if(status == 0){
	// 	//		if(line_state != LINE_CROSS) status = 1;
	// 	//	} else if(status == 1){
	// 	//		if(line_state == LINE_CROSS) {
	// 	//			stop();
	// 	////			status = 0;
	// 	//			return 1;
	// 	//		}
	// 	//	}
	// 	//	followLine();
	// 	return 0;
	// }

#ifdef __cplusplus
}
#endif /* __cplusplus */
