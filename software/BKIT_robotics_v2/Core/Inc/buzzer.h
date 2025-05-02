#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <stdint.h>
#include "global.h"

enum StatusCode initBuzzer(void);
void setFreqBuzzer(const uint32_t frequency);
void stopBuzzer(void);

#endif /* INC_BUZZER_H_ */
