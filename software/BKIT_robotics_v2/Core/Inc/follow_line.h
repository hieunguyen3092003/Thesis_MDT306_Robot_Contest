#ifndef INC_FOLLOW_LINE_H_
#define INC_FOLLOW_LINE_H_

#include <stdint.h>

#include "global.h"

// for follow line
void followLineForward(void);
void followLineBackward(void);
void goLeftUntilMeetLine(void);
void goRightUntilMeetLine(void);
uint8_t followLineForwardUntilCross(void);
void goToTheNthCross(uint8_t n);
void goBackwardUntilMeetLine(void);
void followLineWithWeightError(void);
// int followLineUntilCross();

#endif /* INC_FOLLOW_LINE_H_ */
