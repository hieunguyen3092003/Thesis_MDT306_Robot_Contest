#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdint.h>

void initDisplay(void);
void displayScan(void);
void displayLed7Seg(const uint16_t number);
void displayLeds(const uint8_t data_byte);

#endif /* INC_DISPLAY_H_ */
