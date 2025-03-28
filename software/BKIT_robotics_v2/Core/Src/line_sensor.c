#include "line_sensor.h"
#include "display.h"
#include "dma.h"
#include "adc.h"

#define SENSOR_ERROR_RANGE 200

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    uint16_t sensor_calib[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint16_t sensor_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    enum Line_Status line_status = 0;
    enum Obstacle_Status obstacle_status = 0;

    // sensor_map is used to map the sensor index to the corresponding bit in the temp variable
    const uint16_t sensor_map[8] = {0, 3, 5, 6, 1, 2, 4, 7};

    /**
     *
     * @brief Sensor calibration function
     * @note This function should be called once to calibrate the sensors
     * @note This function should be called when the robot is out of the line
     */
    void SensorCalib()
    {
        HAL_ADC_Start_DMA(&hadc1, (void *)sensor_calib, 8);
    }

    void SensorScan()
    {
        HAL_ADC_Start_DMA(&hadc1, (void *)sensor_buffer, 8); // ADC conversion to sensor_buffer

        uint8_t sensor_temp = 0;
        for (int i = 0; i < 8; i++)
        {
            if ((sensor_buffer[i] > (sensor_calib[i] - SENSOR_ERROR_RANGE)) && (sensor_buffer[i] < (sensor_calib[i] + SENSOR_ERROR_RANGE)))
            {
                sensor_temp |= sensor_temp + (0x80 >> sensor_map[i]);
            }
        }

        switch (sensor_temp & 0b10000001)
        {
        case 0b00000000:
        {
            obstacle_status = OBSTACLE_NONE;
            break;
        }
        case 0b10000000:
        {
            obstacle_status = OBSTACLE_LEFT;
            break;
        }
        case 0b00000001:
        {
            obstacle_status = OBSTACLE_RIGHT;
            break;
        }
        case 0b10000001:
        {
            obstacle_status = OBSTACLE_FRONT;
            break;
        }
        default:
        {
            obstacle_status = OBSTACLE_NONE;
            break;
        }
        }

        switch (sensor_temp & 0b01111110)
        {
        case 0b00000000:
        {
            line_status = LINE_END;
            break;
        }
        case 0b01111110:
        {
            line_status = LINE_CROSS;
            break;
        }
        case 0b00011000:
        {
            line_status = LINE_CENTER;
            break;
        }
        case 0b00001100:
        case 0b00001000:
        {
            line_status = LINE_RIGHT1;
            break;
        }
        case 0b00000110:
        case 0b00000100:
        {
            line_status = LINE_RIGHT2;
            break;
        }
        case 0b00000010:
        {
            line_status = LINE_RIGHT3;
            break;
        }
        case 0b00110000:
        case 0b00010000:
        {
            line_status = LINE_LEFT1;
            break;
        }
        case 0b01100000:
        case 0b00100000:
        {
            line_status = LINE_LEFT2;
            break;
        }
        case 0b01000000:
        {
            line_status = LINE_LEFT3;
            break;
        }
        default:
        {
            line_status = LINE_ERROR;
            break;
        }
        }
    }

    /**
     * @brief Get the line status
     * @return line status
     * @note This function should be called after SensorScan()
     */
    enum Line_Status SensorGetLineStatus()
    {
        return line_status;
    }

    /**
     * @brief Get the obstacle status
     * @return obstacle status
     * @note This function should be called after SensorScan()
     */
    enum Obstacle_Status sensorGetObstacleStatus()
    {
        return obstacle_status;
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */
