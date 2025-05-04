#include "module_mke_m15.h"

#define SW_GAMEPAD_DATA_LEN 8

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    volatile uint8_t sw_gamepad_data[SW_GAMEPAD_DATA_LEN] = {0};
    UART_HandleTypeDef *module_mke_huart = NULL;

    enum StatusCode initModuleMKE(UART_HandleTypeDef *huart)
    {
        module_mke_huart = huart;

        return initUartReceiveIT(module_mke_huart);
    }

    /**
     * @note This function is intergrated into get info function, you dont have to use it
     */
    enum StatusCode readSWGamepadData()
    {
        static volatile uint8_t data_index = 0;

        if (module_mke_huart == &huart1)
        {
            if (getBufferUart1() == 0xFF || data_index >= SW_GAMEPAD_DATA_LEN)
            {
                data_index = 0;
            }

            sw_gamepad_data[data_index++] = getBufferUart1();
        }
        else if (module_mke_huart == &huart2 || data_index >= SW_GAMEPAD_DATA_LEN)
        {
            if (getBufferUart1() == 0xFF)
            {
                data_index = 0;
            }

            sw_gamepad_data[data_index++] = getBufferUart2();
        }
        else
        {
            return STATUS_ERROR;
        }
        return STATUS_OK;
    }

    /**
     * @note This function should be called in if(getFlagUart_()){isSWGamepadButtonPressed(_)}
     * @note Uart flag should be corresponding to Uart you initialze.
     * @retval 0 if it's NOT pressed
     * @retval 1 if it IS pressed
     */
    uint8_t isSWGamepadButtonPressed(enum SoftwareGamepadButtons sw_gamepad_button_id)
    {
        switch (sw_gamepad_button_id)
        {
        case SW_BUTTON_UP:
        {
            return (sw_gamepad_data[6] == 0x01);
            break;
        }
        case SW_BUTTON_DOWN:
        {
            return (sw_gamepad_data[6] == 0x02);
            break;
        }
        case SW_BUTTON_LEFT:
        {
            return (sw_gamepad_data[6] == 0x04);
            break;
        }
        case SW_BUTTON_RIGHT:
        {
            return (sw_gamepad_data[6] == 0x08);
            break;
        }

        case SW_BUTTON_TRIANGLE:
        {
            return (sw_gamepad_data[5] == 0x04);
            break;
        }
        case SW_BUTTON_CIRCLE:
        {
            return (sw_gamepad_data[5] == 0x08);
            break;
        }
        case SW_BUTTON_CROSS:
        {
            return (sw_gamepad_data[5] == 0x10);
            break;
        }
        case SW_BUTTON_SQUARE:
        {
            return (sw_gamepad_data[5] == 0x20);
            break;
        }

        case SW_BUTTON_START:
        {
            return (sw_gamepad_data[5] == 0x01);
            break;
        }
        case SW_BUTTON_SELECT:
        {
            return (sw_gamepad_data[5] == 0x02);
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
     * @return An 8 bits array signal from reciver module
     * @note This function should be used for debug only
     * @note This function should be called in if(getFlagUart_()){isSWGamepadButtonPressed(_)}
     * @note    Uart flag should be corresponding to Uart you initialze.
     */
    const volatile uint8_t *getSWGamepadData()
    {
        return sw_gamepad_data;
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */