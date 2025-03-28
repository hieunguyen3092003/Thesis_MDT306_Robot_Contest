#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <stdint.h>

void initBuzzer(void);
void buzzerSetFreq(uint32_t frequency);
void buzzerStop(void);

#endif /* INC_BUZZER_H_ */
