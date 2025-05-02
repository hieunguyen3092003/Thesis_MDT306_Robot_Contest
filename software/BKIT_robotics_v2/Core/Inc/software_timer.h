#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include <stdint.h>
#include "global.h"

enum StatusCode initTimer2(void);
void sTimer2Set(uint16_t delay, uint16_t period);
uint8_t sTimer2GetFlag(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
