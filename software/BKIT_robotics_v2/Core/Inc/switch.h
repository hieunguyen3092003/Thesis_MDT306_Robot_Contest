#ifndef INC_SWITCH_H_
#define INC_SWITCH_H_

#include <stdint.h>
#include "global.h"

enum Switch
{
    SWITCH_1,
    SWITCH_2,
    SWITCH_3,
    SWITCH_4
};

enum StatusCode initSwitch(void);
uint8_t getSwitchStatus(const enum Switch switch_id);

#endif /* INC_SWITCH_H_ */