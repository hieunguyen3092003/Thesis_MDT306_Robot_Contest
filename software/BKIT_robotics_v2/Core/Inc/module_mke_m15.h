#ifndef INC_MODULE_MKE_M15_H_
#define INC_MODULE_MKE_M15_H_

#include <stdint.h>
#include "global.h"
#include "usart.h"
#include "uart.h"

enum SoftwareGamepadButtons
{
    SW_BUTTON_UP,
    SW_BUTTON_DOWN,
    SW_BUTTON_LEFT,
    SW_BUTTON_RIGHT,

    SW_BUTTON_CROSS,
    SW_BUTTON_CIRCLE,
    SW_BUTTON_SQUARE,
    SW_BUTTON_TRIANGLE,

    SW_BUTTON_START,
    SW_BUTTON_SELECT
};

enum StatusCode initModuleMKE(UART_HandleTypeDef *huart);
enum StatusCode readSWGamepadData(void);
uint8_t isSWGamepadButtonPressed(enum SoftwareGamepadButtons sw_gamepad_button_id);
const volatile uint8_t *getSWGamepadData();

#endif /* INC_MODULE_MKE_M15_H_ */
