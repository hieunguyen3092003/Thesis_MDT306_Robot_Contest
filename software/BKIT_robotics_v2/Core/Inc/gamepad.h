#ifndef INC_GAMEPAD_H_
#define INC_GAMEPAD_H_

#include <stdint.h>
#include "global.h"

enum GamepadButtons
{
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_RIGHT,
    BUTTON_LEFT,

    BUTTON_CROSS,
    BUTTON_CIRCLE,
    BUTTON_SQUARE,
    BUTTON_TRIANGLE,

    BUTTON_L1,
    BUTTON_L2,
    BUTTON_R1,
    BUTTON_R2,

    BUTTON_SHARE,
    BUTTON_OPTIONS,
    BUTTON_MAIN
};

enum StatusCode initGamepad(void);
enum StatusCode readGamepadData(void);
uint8_t isGamepadButtonPressed(enum GamepadButtons gamepad_button_id);
const uint8_t *getGamepadData();

#endif /* INC_GAMEPAD_H_ */