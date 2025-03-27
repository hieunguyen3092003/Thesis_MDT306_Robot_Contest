#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "gpio.h"
#include "stm32f1xx.h"

#define STATE_00	0
#define STATE_01	1
#define STATE_11	2
#define STATE_10	3

extern int32_t encoder_pulse[4];

void read_encoder_data(void);

#endif /* INC_ENCODER_H_ */
