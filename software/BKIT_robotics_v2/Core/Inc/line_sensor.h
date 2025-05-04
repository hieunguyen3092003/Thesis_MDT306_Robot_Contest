#ifndef INC_LINE_SENSOR_H_
#define INC_LINE_SENSOR_H_

#include <stdint.h>
#include "global.h"

enum Line_Status
{
    LINE_END,
    LINE_CROSS,
    LINE_CENTER,
    LINE_RIGHT1,
    LINE_RIGHT2,
    LINE_RIGHT3,
    LINE_LEFT1,
    LINE_LEFT2,
    LINE_LEFT3,
    LINE_ERROR
};

enum Obstacle_Status
{
    OBSTACLE_NONE,
    OBSTACLE_LEFT,
    OBSTACLE_RIGHT,
    OBSTACLE_FRONT,
};

enum StatusCode calibSensor(void);
void sensorScan(void);
enum Line_Status SensorGetLineStatus(void);
enum Obstacle_Status sensorGetObstacleStatus(void);

uint8_t getSensorState(void);
const uint16_t *getSensorCalibValue(void);
const uint16_t *getSensorValue(void);

#endif /* INC_LINE_SENSOR_H_ */
