#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include <stdint.h>
#include "global.h"

#define NUMBER_OF_ENCODER 4
#define PULSE_PER_REVOLUTION 234 // Currently unused

enum Encoder
{
    ENCODER_1,
    ENCODER_2,
    ENCODER_3,
    ENCODER_4
};

void scanEncoder(void);
uint32_t getPulseCount(const enum Encoder encoder_id);
uint32_t getDeltaEncoder(const enum Encoder encoder_id);

#endif /* INC_ENCODER_H_ */
