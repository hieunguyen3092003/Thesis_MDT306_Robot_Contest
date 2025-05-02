#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include <stdint.h>
#include "global.h"

enum Servo
{
    SERVO_1,
    SERVO_2,
    SERVO_3
};

enum StatusCode initServo(const enum Servo servo_id);
void servoSetAngle(const enum Servo servo_id, uint8_t angle);

#endif /* INC_SERVO_H_ */
