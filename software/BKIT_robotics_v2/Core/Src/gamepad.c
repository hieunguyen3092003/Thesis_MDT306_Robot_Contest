#include "gamepad.h"

#include <string.h>
#include <stdio.h>
#include "i2c.h"
#include "usart.h"

#define GAMEPAD_I2C_ADDRESS (0x55 << 1)
#define GAMEPAD_DATA_LEN 30

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    uint8_t gamepad_data[GAMEPAD_DATA_LEN] = {0};

    /**
     * @brief check if module bluetooth receiver is working
     * @retval STATUS_ERROR if initializing connection fail
     * @retval STATUS_OK if connecting successfully
     */
    enum StatusCode initGamepad()
    {
        for (uint8_t attempt = 0; attempt < MAX_RETRY_COUNT; ++attempt)
        {
            if (HAL_I2C_IsDeviceReady(&hi2c2, GAMEPAD_I2C_ADDRESS, 3, 50) == HAL_OK)
            {
                return STATUS_OK;
            }

            HAL_Delay(50);
        }
        return STATUS_ERROR;
    }

    /**
     * @brief Read gamepad data
     * @retval STATUS_OK or STATUS_ERROR
     * @note This function is intergrated into get info function, you dont have to use it
     */
    enum StatusCode readGamepadData()
    {
        if (HAL_I2C_Master_Receive(&hi2c2, GAMEPAD_I2C_ADDRESS, gamepad_data, GAMEPAD_DATA_LEN, HAL_MAX_DELAY) == HAL_OK)
        {
            return STATUS_OK;
        }
        else
        {
            return STATUS_ERROR;
        }
    }

    /**
     * @param gamepad_button_id type GamepadButtons. indicate button you want to know whether it's pressed or not
     * @retval 0 if it's NOT pressed
     * @retval 1 if it IS pressed
     */
    uint8_t isGamepadButtonPressed(enum GamepadButtons gamepad_button_id)
    {
        switch (gamepad_button_id)
        {
        case BUTTON_UP:
        {
            return (gamepad_data[1] == 0x01);
            break;
        }
        case BUTTON_DOWN:
        {
            return (gamepad_data[1] == 0x02);
            break;
        }
        case BUTTON_RIGHT:
        {
            return (gamepad_data[1] == 0x04);
            break;
        }
        case BUTTON_LEFT:
        {
            return (gamepad_data[1] == 0x08);
            break;
        }

        case BUTTON_CROSS:
        {
            return (gamepad_data[27] == 0x01);
            break;
        }
        case BUTTON_CIRCLE:
        {
            return (gamepad_data[27] == 0x02);
            break;
        }
        case BUTTON_SQUARE:
        {
            return (gamepad_data[27] == 0x04);
            break;
        }
        case BUTTON_TRIANGLE:
        {
            return (gamepad_data[27] == 0x08);
            break;
        }

        case BUTTON_L1:
        {
            return (gamepad_data[27] == 0x10);
            break;
        }
        case BUTTON_L2:
        {
            return (gamepad_data[27] == 0x40);
            break;
        }

        case BUTTON_R1:
        {
            return (gamepad_data[27] == 0x20);
            break;
        }
        case BUTTON_R2:
        {
            return (gamepad_data[27] == 0x80);
            break;
        }

        case BUTTON_MAIN:
        {
            return (gamepad_data[29] == 0x01);
            break;
        }
        case BUTTON_SHARE:
        {
            return (gamepad_data[29] == 0x02);
            break;
        }
        case BUTTON_OPTIONS:
        {
            return (gamepad_data[29] == 0x04);
            break;
        }

        default:
        {
            return 0;
            break;
        }
        }
    }

    /**
     * @note This function should be used for debugging only.
     * @return An 8 bits array signal from reciver module
     */
    const uint8_t *getGamepadData()
    {
        return gamepad_data;
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */
