#ifndef INC_PID_H_
#define INC_PID_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum{
	MANUAL,
	AUTOMATIC
}PIDMode;

/*
 * chua dung
 */
typedef enum{
	DIRECT,
	REVERSE
}PIDDirection;

typedef struct{

}PIDControl;

#endif /* INC_PID_H_ */
