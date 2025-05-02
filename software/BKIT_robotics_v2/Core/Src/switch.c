#include "switch.h"

#include "gpio.h"
#include "spi.h"

#define NUMBER_OF_SWITCH 4

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    uint8_t switch_status[NUMBER_OF_SWITCH] = {0};
    uint8_t switch_buffer = 0b00000000;

    enum StatusCode initSwitch()
    {
        HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 1);
        HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 0);
        HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 1);
        if (HAL_SPI_Receive(&hspi1, (void *)&switch_buffer, 1, 10) == HAL_OK)
        {
            return STATUS_OK;
        }
        return STATUS_ERROR;
    }

    /**
     * @brief this function used to get status of switch are on or off.
     * @param switch_id correspond to switch that needs to know status
     * @retval 0 if switch is OFF
     * @retval 1 if switch is OFF
     */
    uint8_t getSwitchStatus(const enum Switch switch_id)
    {
        HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 0);
        HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 1);
        HAL_SPI_Receive(&hspi1, (void *)&switch_buffer, 1, 10);

        for (uint8_t i = 0; i < NUMBER_OF_SWITCH; ++i)
        {
            if (switch_buffer & (0b00010000 << i))
            {
                switch_status[i] = 0;
            }
            else
            {
                switch_status[i] = 1;
            }
        }

        return switch_status[switch_id];
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */