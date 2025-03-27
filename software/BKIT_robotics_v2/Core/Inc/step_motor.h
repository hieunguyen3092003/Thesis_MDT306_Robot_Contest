#ifndef INC_STEP_MOTOR_H_
#define INC_STEP_MOTOR_H_

#include "tim.h"
#include "gpio.h"

enum Step_Direction
{
    DOWN,
    UP
};

void stepMotorMove(enum Step_Direction direction, uint16_t cycle);

#endif /* INC_STEP_MOTOR_H_ */
