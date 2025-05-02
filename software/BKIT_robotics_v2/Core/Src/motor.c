#include "motor.h"

#include "tim.h"
#include "gpio.h"

#define NUMBER_OF_MOTORS 4

#define UP 1
#define DOWN 0

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	const uint32_t motor_channel[NUMBER_OF_MOTORS] = {TIM_CHANNEL_4, TIM_CHANNEL_3, TIM_CHANNEL_1, TIM_CHANNEL_2};

	enum StatusCode initMotor(const enum Motor motor_id)
	{
		for (uint8_t attempt = 0; attempt < MAX_RETRY_COUNT; ++attempt)
		{
			if (HAL_TIM_PWM_Start(&htim8, motor_channel[motor_id]) == HAL_OK)
			{
				return STATUS_OK;
			}
			HAL_Delay(50);
		}
		return STATUS_ERROR;
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

#ifdef __cplusplus
}
#endif /* __cplusplus */
