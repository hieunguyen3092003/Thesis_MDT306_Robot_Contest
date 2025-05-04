#include "follow_line.h"
#include "motor.h"
#include "line_sensor.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    void moveFrontLeftLine()
    {
        motor1Rotates(5);
        motor2Rotates(10);
        motor3Rotates(10);
        motor4Rotates(5);
    }

    void moveFrontRightLine()
    {
        motor1Rotates(10);
        motor2Rotates(5);
        motor3Rotates(5);
        motor4Rotates(10);
    }

    void followLineForward()
    {
        enum Line_Status status_forward;
        status_forward = SensorGetLineStatus();

        switch (status_forward)
        {
        case LINE_END:
            motorStop();
            break;
        case LINE_CROSS:
            moveForward(12);
            break;
        case LINE_CENTER:
            moveForward(12);
            break;
        case LINE_LEFT1:
            //				moveFrontLeftLine();
            rotateRight(15);
            break;
        case LINE_LEFT2:
            //				moveFrontLeftLine();
            rotateRight(15);
            break;
        case LINE_LEFT3:
            //				moveFrontLeftLine();
            rotateRight(15);
            break;
        case LINE_RIGHT1:
            //				moveFrontRightLine();
            rotateLeft(15);
            break;
        case LINE_RIGHT2:
            //				moveFrontRightLine();
            rotateLeft(15);
            break;
        case LINE_RIGHT3:
            //				moveFrontRightLine();
            rotateLeft(15);
            break;
        default:
            motorStop();
            break;
        }
    }

    void followLineBackward()
    {
        enum Line_Status status_backward;
        status_backward = SensorGetLineStatus();

        switch (status_backward)
        {
        case LINE_END:
            motorStop();
            break;
        case LINE_CROSS:
            moveBackward(12);
            break;
        case LINE_CENTER:
            moveBackward(12);
            break;
        case LINE_LEFT1:
            //				moveFrontLeftLine();
            rotateLeft(15);
            break;
        case LINE_LEFT2:
            //				moveFrontLeftLine();
            rotateLeft(15);
            break;
        case LINE_LEFT3:
            //				moveFrontLeftLine();
            rotateLeft(15);
            break;
        case LINE_RIGHT1:
            //				moveFrontRightLine();
            rotateRight(15);
            break;
        case LINE_RIGHT2:
            //				moveFrontRightLine();
            rotateRight(15);
            break;
        case LINE_RIGHT3:
            //				moveFrontRightLine();
            rotateRight(15);
            break;
        default:
            motorStop();
            break;
        }
    }

    uint8_t followLineForwardUntilCross(void)
    {
        enum Line_Status status_forward;
        status_forward = SensorGetLineStatus();

        while (status_forward == LINE_CROSS)
        {
            status_forward = SensorGetLineStatus();
            moveForward(32);
            HAL_Delay(10);
        }

        motorStop();
        uint8_t state = 0;

        while (state != 1)
        {
            status_forward = SensorGetLineStatus();
            switch (status_forward)
            {
            case LINE_END:
                motorStop();
                break;
            case LINE_CROSS:
                motorStop();
                state = 1;
                return 1;
                break;
            case LINE_CENTER:
                moveForward(32);
                break;
            case LINE_LEFT1:
                rotateRight(35);
                break;
            case LINE_LEFT2:
                rotateRight(35);
                break;
            case LINE_LEFT3:
                rotateRight(35);
                break;
            case LINE_RIGHT1:
                rotateLeft(35);
                break;
            case LINE_RIGHT2:
                rotateLeft(35);
                break;
            case LINE_RIGHT3:
                rotateLeft(35);
                break;
            default:
                followLineWithWeightError();
                break;
            }
            HAL_Delay(10);
        }
    }

    void goToTheNthCross(uint8_t n)
    {
        uint8_t cross_nth = 0;
        while (cross_nth != n)
        {
            cross_nth += followLineForwardUntilCross();
        }
    }

    void goLeftUntilMeetLine(void)
    {
        enum Line_Status status;
        status = SensorGetLineStatus();
        while (status != LINE_LEFT1 && status != LINE_LEFT2 && status != LINE_CENTER && status != LINE_RIGHT1 && status != LINE_RIGHT2)
        {
            status = SensorGetLineStatus();
            moveLeft(45);
            HAL_Delay(10);
        }
        motorStop();
    }

    void goRightUntilMeetLine(void)
    {
        enum Line_Status status;
        status = SensorGetLineStatus();
        while (status != LINE_LEFT1 && status != LINE_LEFT2 && status != LINE_CENTER && status != LINE_RIGHT1 && status != LINE_RIGHT2)
        {
            status = SensorGetLineStatus();
            moveRight(45);
            HAL_Delay(10);
        }
        motorStop();
    }

    void goBackwardUntilMeetLine(void)
    {
        enum Line_Status status;
        status = SensorGetLineStatus();
        while (status == LINE_CROSS)
        {
            status = SensorGetLineStatus();
            moveBackward(35);
            HAL_Delay(10);
        }
        while (status != LINE_CROSS)
        {
            status = SensorGetLineStatus();
            moveBackward(35);
            HAL_Delay(10);
        }
        motorStop();
    }

    void followLineWithWeightError()
    {
        float weight_error = getWeightError();
        if (weight_error < 0)
        {
            rotateLeft(35);
        }
        else if (weight_error > 0)
        {
            rotateRight(35);
        }
        else
        {
            moveForward(32);
        }
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */
