#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdio.h>
#include <stdint.h>

#include "usart.h"
#include "global.h"

enum StatusCode initUartReceiveIT(UART_HandleTypeDef *huart);
enum StatusCode uartTransmitString(UART_HandleTypeDef *huart, const char *str);
enum StatusCode uartTransmit8b(UART_HandleTypeDef *huart, const uint8_t *array, const uint16_t size);

uint8_t getBufferUart1(void);
uint8_t getBufferUart2(void);

uint8_t getFlagUart1(void);
uint8_t getFlagUart2(void);

#endif /* INC_UART_H_ */