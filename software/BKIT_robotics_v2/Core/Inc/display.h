#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdint.h>
#include "global.h"

enum StatusCode initDisplay(void);
void displayScan(void);
void displayLed7Seg(const uint8_t number);
void displayLeds(const uint8_t data_byte);
uint8_t mirrorByte(uint8_t data_byte);
void toggleLedDebug(void);

#endif /* INC_DISPLAY_H_ */
