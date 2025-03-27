#ifndef INC_MOVE_H_
#define INC_MOVE_H_

#include <stdint.h>

enum Motor
{
    MOTOR_1,
    MOTOR_2,
    MOTOR_3,
    MOTOR_4
};

enum Direction
{
    STOP,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    FRONT_LEFT,
    FRONT_RIGHT,
    BACK_LEFT,
    BACK_RIGHT,
    ROTATE_LEFT,
    ROTATE_RIGHT
};

void initMotor(const enum Motor motor_id);

void motor1Rotates(const int speed);
void motor2Rotates(const int speed);
void motor3Rotates(const int speed);
void motor4Rotates(const int speed);

//                   forward
//           frontLeft   |  frontRight          ↺: rotateLeft
//         left		 ----+----     right		↻: rotateRight
//           backLeft    |  backRight           □: stop
//                  backwards
//

void motorStop(void);

void moveForward(const int speed);
void moveBackward(const int speed);
void moveLeft(const int speed);
void moveRight(const int speed);

void moveFrontLeft(const int speed);
void moveFrontRight(const int speed);
void moveBackLeft(const int speed);
void moveBackRight(const int speed);

void rotateLeft(const int speed);
void rotateRight(const int speed);

void moveDirection(const enum Direction direction, const int speed);
// void followLine();
// int followLineUntilCross();

#endif /* INC_MOVE_H_ */
