#include "robot_firmware.h"

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "global.h"
#include "software_timer.h"

#include "servo.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "step_motor.h"
#include "line_sensor.h"
#include "gamepad.h"
#include "module_mke_m15.h"

#include "button.h"
#include "switch.h"

#include "display.h"
#include "buzzer.h"

#include "uart.h"
#include "utils.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    enum Mode mode_id = MODE_IDLE;

    enum Mode getModeId()
    {
        mode_id = (enum Mode)((getSwitchStatus(SWITCH_4) << 3) | (getSwitchStatus(SWITCH_3) << 2) | (getSwitchStatus(SWITCH_2) << 1) | getSwitchStatus(SWITCH_1));

        return mode_id;
    }

    void initSystem()
    {
        (void)initServo(SERVO_1);
        (void)initServo(SERVO_2);
        (void)initServo(SERVO_3);

        (void)initMotor(MOTOR_1);
        (void)initMotor(MOTOR_2);
        (void)initMotor(MOTOR_3);
        (void)initMotor(MOTOR_4);

        (void)initGamepad();
        (void)initModuleMKE(&huart1);
        // Module MKE m15 is connected to UART 1

        (void)initTimer2();

        (void)initButton();
        (void)initSwitch();
        (void)initBuzzer();
        (void)initDisplay();
    }

    enum StatusCode setupRobot()
    {
        switch (mode_id)
        {
        case MODE_IDLE:
        case MODE_TEST_DEBUG_INDICATORS:
        case MODE_TEST_COMM:
        case MODE_TEST_MOTORS:
        case MODE_TEST_ENCODERS:
        case MODE_TEST_PID:
        case MODE_TEST_SERVO_MOTORS:
        case MODE_TEST_STEP_MOTORS:
        case MODE_TEST_SENSORS:
        case MODE_TEST_GAMEPAD:
        case MODE_TEST_MODULE_MKE:
        case MODE_TEST_FULL:
        {
            // Uart 2 COM will attached to USB ttl for debugging and connected with serial monitor for debugging.
            // Uart 1 COM will attached module bluetooth reciver MKE m15.
            uartTransmitString(&huart2, "Begin initialize process\r\n");

            if ((initServo(SERVO_1) != STATUS_OK) || (initServo(SERVO_2) != STATUS_OK) || (initServo(SERVO_3) != STATUS_OK))
            {
                uartTransmitString(&huart2, "[ERR] Servo initialized fail\r\n");
            }

            if ((initMotor(MOTOR_1) != STATUS_OK) || (initMotor(MOTOR_2) != STATUS_OK) || (initMotor(MOTOR_3) != STATUS_OK) || (initMotor(MOTOR_4) != STATUS_OK))
            {
                uartTransmitString(&huart2, "[ERR] Motor initialized fail\r\n");
            }

            if (initGamepad() != STATUS_OK)
            {
                uartTransmitString(&huart2, "[ERR] Gamepad initialized fail\r\n");
            }
            if (initModuleMKE(&huart1) != STATUS_OK)
            {
                uartTransmitString(&huart2, "[ERR] Module MKE m15 initialized fail\r\n");
            }

            if (initTimer2() != STATUS_OK)
            {
                uartTransmitString(&huart2, "[ERR] Timer initialized fail\r\n");
            }

            if ((initButton() != STATUS_OK) || (initSwitch() != STATUS_OK))
            {
                uartTransmitString(&huart2, "[ERR] Buttons & Switches initialized fail\r\n");
            }

            if ((initBuzzer() != STATUS_OK) || (initDisplay() != STATUS_OK))
            {
                uartTransmitString(&huart2, "[ERR] Buzzer & Display initialized fail\r\n");
            }

            initPIDMotor(ENCODER_1, 0.1, 0.1, 0.01, 50);
            initPIDMotor(ENCODER_2, 0.1, 0.1, 0.01, 50);
            initPIDMotor(ENCODER_3, 0.1, 0.1, 0.01, 50);
            initPIDMotor(ENCODER_4, 0.1, 0.1, 0.01, 50);

            uartTransmitString(&huart2, "\r\nFinished initialize process\r\n");

            sTimer2Set(500, 50);
            displayLeds(0b00000000);

            break;
        }
        default:
        {
            return STATUS_ERROR;
            break;
        }
        }
        return STATUS_OK;
    }

    enum StatusCode processRobot()
    {
        switch (mode_id)
        {
        case MODE_IDLE:
        {
            if (sTimer2GetFlag())
            {
                toggleLedDebug();
            }

            break;
        }

        case MODE_TEST_DEBUG_INDICATORS:
        {
            if (sTimer2GetFlag())
            {
                (void)scanButton();

                static uint8_t byte_displayed = 0b00000000;

                if (isButtonPressed(BUTTON_1))
                {
                    byte_displayed = (byte_displayed << 1) | 0b00000001;
                    displayLeds(byte_displayed);

                    (void)uartTransmitString(&huart2, "Button 1 Pressed\r\n");
                }
                else if (isButtonPressed(BUTTON_2))
                {
                    byte_displayed = byte_displayed >> 1;
                    displayLeds(byte_displayed);

                    (void)uartTransmitString(&huart2, "Button 2 Pressed\r\n");
                }
                else if (isButtonPressed(BUTTON_3))
                {
                    setFreqBuzzer(byte_displayed);

                    (void)uartTransmitString(&huart2, "Button 3 Pressed\r\n");
                }
                else if (isButtonPressed(BUTTON_4))
                {
                    stopBuzzer();

                    (void)uartTransmitString(&huart2, "Button 4 Pressed\r\n");
                }

                uint8_t period = ((getSwitchStatus(SWITCH_4) << 3) | (getSwitchStatus(SWITCH_3) << 2) | (getSwitchStatus(SWITCH_2) << 1) | getSwitchStatus(SWITCH_1));
                if (period == 0)
                {
                    HAL_GPIO_WritePin(LED_DEBUG_GPIO_Port, LED7_EN1_Pin, GPIO_PIN_SET);
                }
                else
                {
                    static uint8_t counter = 0;
                    counter = (counter + 1) % (period * (20 / 2));
                    if (counter == 0)
                    {
                        toggleLedDebug();
                    }
                }
            }
            break;
        }

        case MODE_TEST_COMM:
        {
            if (getFlagUart1())
            {
                toggleLedDebug();

                uint8_t transmit_data_buffer = getBufferUart1();
                (void)uartTransmit8b(&huart2, &transmit_data_buffer, 1);
            }
            if (sTimer2GetFlag())
            {
                toggleLedDebug();

                (void)scanButton();

                if (isButtonPressed(BUTTON_1))
                {
                    if (readGamepadData() == STATUS_OK)
                    {
                        (void)uartTransmit8b(&huart2, getGamepadData(), 30);
                    }

                    (void)uartTransmitString(&huart2, "Button 1 Pressed\r\n");
                }
            }
            break;
        }

        case MODE_TEST_MOTORS:
        {
            if (sTimer2GetFlag())
            {
                toggleLedDebug();

                (void)scanButton();

                if (isButtonPressed(BUTTON_1))
                {
                    moveDirection(FORWARD, 50);
                }
                else if (isButtonPressed(BUTTON_2))
                {
                    moveDirection(BACKWARD, 50);
                }
                else if (isButtonPressed(BUTTON_3))
                {
                    moveDirection(LEFT, 50);
                }
                else if (isButtonPressed(BUTTON_4))
                {
                    moveDirection(RIGHT, 50);
                }
            }
            break;
        }

        case MODE_TEST_ENCODERS:
        {
            if (sTimer2GetFlag())
            {
                toggleLedDebug();

                (void)scanButton();

                if (isButtonPressed(BUTTON_1))
                {
                    uint32_t encoder_1_pulse = getPulseCount(ENCODER_1);
                    uint8_t transmit_buffer[4] = {0};
                    uint32_to_bytes(&encoder_1_pulse, transmit_buffer, 1);
                    uartTransmit8b(&huart2, transmit_buffer, 4);
                }
                else if (isButtonPressed(BUTTON_2))
                {
                    uint32_t encoder_2_pulse = getPulseCount(ENCODER_2);
                    uint8_t transmit_buffer[4] = {0};
                    uint32_to_bytes(&encoder_2_pulse, transmit_buffer, 1);
                    uartTransmit8b(&huart2, transmit_buffer, 4);
                }
                else if (isButtonPressed(BUTTON_3))
                {
                    uint32_t encoder_3_pulse = getPulseCount(ENCODER_3);
                    uint8_t transmit_buffer[4] = {0};
                    uint32_to_bytes(&encoder_3_pulse, transmit_buffer, 1);
                    uartTransmit8b(&huart2, transmit_buffer, 4);
                }
                else if (isButtonPressed(BUTTON_4))
                {
                    uint32_t encoder_4_pulse = getPulseCount(ENCODER_4);
                    uint8_t transmit_buffer[4] = {0};
                    uint32_to_bytes(&encoder_4_pulse, transmit_buffer, 1);
                    uartTransmit8b(&huart2, transmit_buffer, 4);
                }
            }
            break;
        }

        case MODE_TEST_PID:
        {
            if (sTimer2GetFlag())
            {
                toggleLedDebug();

                (void)scanButton();

                if (isButtonPressed(BUTTON_1))
                {
                    setSpeedPIDMotor(ENCODER_1, 234);
                    setSpeedPIDMotor(ENCODER_2, 234);
                    setSpeedPIDMotor(ENCODER_3, 234);
                    setSpeedPIDMotor(ENCODER_4, 234);
                }
                else if (isButtonPressed(BUTTON_2))
                {
                    setSpeedPIDMotor(ENCODER_1, 468);
                    setSpeedPIDMotor(ENCODER_2, 468);
                    setSpeedPIDMotor(ENCODER_3, 468);
                    setSpeedPIDMotor(ENCODER_4, 468);
                }
                else if (isButtonPressed(BUTTON_3))
                {
                    setSpeedPIDMotor(ENCODER_1, -234);
                    setSpeedPIDMotor(ENCODER_2, -234);
                    setSpeedPIDMotor(ENCODER_3, -234);
                    setSpeedPIDMotor(ENCODER_4, -234);
                }

                motor1Rotates(round(computePIDMotor(ENCODER_1)));
                motor2Rotates(round(computePIDMotor(ENCODER_2)));
                motor3Rotates(round(computePIDMotor(ENCODER_3)));
                motor4Rotates(round(computePIDMotor(ENCODER_4)));
                break;
            }
        }

        case MODE_TEST_SERVO_MOTORS:
        {
            if (sTimer2GetFlag())
            {
                toggleLedDebug();

                (void)scanButton();

                if (isButtonPressed(BUTTON_1))
                {
                    servoSetAngle(SERVO_1, 0);
                    servoSetAngle(SERVO_2, 0);
                    servoSetAngle(SERVO_3, 0);

                    (void)uartTransmitString(&huart2, "Button 1 Pressed\r\n");
                }
                else if (isButtonPressed(BUTTON_2))
                {
                    servoSetAngle(SERVO_1, 14);
                    servoSetAngle(SERVO_2, 14);
                    servoSetAngle(SERVO_3, 14);

                    (void)uartTransmitString(&huart2, "Button 2 Pressed\r\n");
                }
                else if (isButtonPressed(BUTTON_3))
                {
                    servoSetAngle(SERVO_1, 28);
                    servoSetAngle(SERVO_2, 28);
                    servoSetAngle(SERVO_3, 28);

                    (void)uartTransmitString(&huart2, "Button 3 Pressed\r\n");
                }
                else if (isButtonPressed(BUTTON_4))
                {
                    servoSetAngle(SERVO_1, 55);
                    servoSetAngle(SERVO_2, 55);
                    servoSetAngle(SERVO_3, 55);

                    (void)uartTransmitString(&huart2, "Button 4 Pressed\r\n");
                }
            }
            break;
        }

        case MODE_TEST_STEP_MOTORS:
        {
            if (sTimer2GetFlag())
            {
                toggleLedDebug();

                (void)scanButton();

                if (isButtonPressed(BUTTON_1))
                {
                    stepMotorMove(UP, 1);
                }
                else if (isButtonPressed(BUTTON_2))
                {
                    stepMotorMove(DOWN, 1);
                }
                else if (isButtonPressed(BUTTON_3))
                {
                    stepMotorMove(UP, 0);
                }
                else if (isButtonPressed(BUTTON_4))
                {
                    stepMotorMove(UP, 3);
                }
            }
            break;
        }

        case MODE_TEST_SENSORS:
        {
            if (sTimer2GetFlag())
            {
                toggleLedDebug();

                (void)scanButton();

                if (isButtonPressed(BUTTON_1))
                {
                    (void)calibSensor();
                }
                else if (isButtonPressed(BUTTON_2))
                {
                    sensorScan();

                    displayLeds(getSensorState());
                }
                else if (isButtonPressed(BUTTON_3))
                {
                    uint8_t transmit_buffer[16] = {0};
                    uint16_to_bytes(getSensorCalibValue(), transmit_buffer, 8);
                    (void)uartTransmit8b(&huart2, transmit_buffer, 16);
                }
                else if (isButtonPressed(BUTTON_4))
                {
                    uint8_t transmit_buffer[16] = {0};
                    uint16_to_bytes(getSensorValue(), transmit_buffer, 8);
                    (void)uartTransmit8b(&huart2, transmit_buffer, 16);
                }
            }
            break;
        }
        case MODE_TEST_GAMEPAD:
        {
            if (sTimer2GetFlag())
            {
                if (readGamepadData() == STATUS_OK)
                {
                    uint8_t speed = 50;

                    if (isGamepadButtonPressed(BUTTON_TRIANGLE))
                    {
                        speed *= 2;
                    }

                    if (isGamepadButtonPressed(BUTTON_CROSS))
                    {
                        speed /= 2;
                    }

                    if (isGamepadButtonPressed(BUTTON_UP))
                    {
                        moveDirection(FORWARD, speed);
                    }
                    else if (isGamepadButtonPressed(BUTTON_DOWN))
                    {
                        moveDirection(BACKWARD, speed);
                    }
                    else if (isGamepadButtonPressed(BUTTON_LEFT))
                    {
                        moveDirection(LEFT, speed);
                    }
                    else if (isGamepadButtonPressed(BUTTON_RIGHT))
                    {
                        moveDirection(RIGHT, speed);
                    }
                    else if (isGamepadButtonPressed(BUTTON_SQUARE))
                    {
                        moveDirection(ROTATE_LEFT, speed);
                    }
                    else if (isGamepadButtonPressed(BUTTON_CIRCLE))
                    {
                        moveDirection(ROTATE_RIGHT, speed);
                    }
                    else
                    {
                        motorStop();
                    }

                    if (isGamepadButtonPressed(BUTTON_L1))
                    {
                        stepMotorMove(UP, 1);
                    }
                    else if (isGamepadButtonPressed(BUTTON_R1))
                    {
                        stepMotorMove(DOWN, 1);
                    }

                    static uint8_t angle = 0;
                    if (isGamepadButtonPressed(BUTTON_L2))
                    {
                        angle = (angle < 55) ? (angle + 1) : angle;

                        servoSetAngle(SERVO_3, angle);
                    }
                    else if (isGamepadButtonPressed(BUTTON_R2))
                    {
                        angle = (angle > 0) ? (angle - 1) : angle;

                        servoSetAngle(SERVO_3, angle);
                    }
                }
            }
            break;
        }
        case MODE_TEST_MODULE_MKE:
        {
            if (getFlagUart1())
            {
                (void)readSWGamepadData();
            }
            if (sTimer2GetFlag())
            {
                uint8_t speed = 50;

                if (isSWGamepadButtonPressed(SW_BUTTON_START))
                {
                    speed *= 2;
                }
                else if (isSWGamepadButtonPressed(SW_BUTTON_SELECT))
                {
                    speed /= 2;
                }

                if (isSWGamepadButtonPressed(SW_BUTTON_UP))
                {
                    moveDirection(FORWARD, speed);
                }
                else if (isSWGamepadButtonPressed(SW_BUTTON_DOWN))
                {
                    moveDirection(BACKWARD, speed);
                }
                else if (isSWGamepadButtonPressed(SW_BUTTON_LEFT))
                {
                    moveDirection(LEFT, speed);
                }
                else if (isSWGamepadButtonPressed(SW_BUTTON_RIGHT))
                {
                    moveDirection(RIGHT, speed);
                }
                else
                {
                    motorStop();
                }

                if (isSWGamepadButtonPressed(SW_BUTTON_CROSS))
                {
                    stepMotorMove(DOWN, 1);
                }
                else if (isSWGamepadButtonPressed(SW_BUTTON_TRIANGLE))
                {
                    stepMotorMove(UP, 1);
                }

                static uint8_t angle = 0;
                if (isSWGamepadButtonPressed(SW_BUTTON_CIRCLE))
                {
                    angle = (angle < 55) ? (angle + 1) : angle;

                    servoSetAngle(SERVO_3, angle);
                }
                else if (isSWGamepadButtonPressed(SW_BUTTON_SQUARE))
                {
                    angle = (angle > 0) ? (angle - 1) : angle;

                    servoSetAngle(SERVO_3, angle);
                }
            }

            break;
        }
        case MODE_TEST_FULL:
        {
            break;
        }

        default:
        {
            return STATUS_ERROR;
            break;
        }
        }
        return STATUS_OK;
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */