#include "line_sensor.h"
#include "dma.h"
#include "adc.h"

#define NUMBER_OF_SENSORS 8
#define BW_THRESHOLD 200

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	uint16_t sensor_calib[NUMBER_OF_SENSORS] = {0};
	uint16_t sensor_buffer[NUMBER_OF_SENSORS] = {0};
	uint8_t sensor_states = 0b00000000; // used to store the sensor states 1 means line, 0 means no line

	enum Line_Status line_status = LINE_END;
	enum Obstacle_Status obstacle_status = OBSTACLE_NONE;

	// sensor_map is used to map the sensor index to the corresponding bit in the temp variable
	const uint16_t sensor_map[8] = {7, 4, 2, 1, 6, 5, 3, 0};

	/**
	 * @brief Sensor calibration function
	 * @note This function should be called once to calibrate the sensors
	 * @note This function should be called when the sensors are in black square
	 */
	enum StatusCode calibSensor()
	{
		for (uint8_t attempt = 0; attempt < MAX_RETRY_COUNT; ++attempt)
		{
			if (HAL_ADC_Start_DMA(&hadc1, (void *)sensor_calib, 8) == HAL_OK)
			{
				return STATUS_OK;
			}
			HAL_Delay(50);
		}
		return STATUS_ERROR;
	}

	void sensorScan()
	{
		HAL_ADC_Start_DMA(&hadc1, (void *)sensor_buffer, 8); // ADC conversion to sensor_buffer

		sensor_states = 0b00000000; // clear the sensor_states variable

		for (int i = 0; i < 8; i++)
		{
			// Check if the sensor value is out of threshold
			if ((sensor_buffer[i] < (sensor_calib[i] - BW_THRESHOLD)) || (sensor_buffer[i] > (sensor_calib[i] + BW_THRESHOLD)))
			{
				sensor_states |= (0b10000000 >> sensor_map[i]);
			}
		}

		// Infrared obstacle sensors processing
		switch (sensor_states & 0b10000001)
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

		// Line sensors processing
		switch (sensor_states & 0b01111110)
		{
		case 0b01111110:
		{
			line_status = LINE_CROSS;
			break;
		}
		case 0b00000000:
		{
			line_status = LINE_END;
			break;
		}
		case 0b00011000:
		{
			line_status = LINE_CENTER;
			break;
		}

		case 0b00001100:
		{
			line_status = LINE_RIGHT1;
			break;
		}
		case 0b00011100:
		{
			line_status = LINE_RIGHT1;
		}

		case 0b00000110:
		{
			line_status = LINE_RIGHT2;
			break;
		}
		case 0b00001110:
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
		{
			line_status = LINE_LEFT1;
			break;
		}
		case 0b00111000:
		{
			line_status = LINE_LEFT1;
			break;
		}

		case 0b01100000:
		{
			line_status = LINE_LEFT2;
			break;
		}
		case 0b01110000:
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

	/**
	 * @brief These function should be used to debug line sensor
	 */
	uint8_t getSensorState()
	{
		return sensor_states;
	}
	const uint16_t *getSensorCalibValue()
	{
		return sensor_calib;
	}
	const uint16_t *getSensorValue()
	{
		return sensor_buffer;
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */
