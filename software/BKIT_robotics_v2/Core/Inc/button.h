#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>
#include "global.h"

enum Button
{
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4
};

enum StatusCode initButton(void);
enum StatusCode scanButton(void);
uint8_t isButtonPressed(const enum Button button_id);

#endif /* INC_BUTTON_H_ */