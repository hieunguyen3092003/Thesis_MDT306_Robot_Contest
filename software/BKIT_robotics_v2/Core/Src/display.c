#include "display.h"
#include "gpio.h"
#include "spi.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    uint8_t display_buffer[3] = {0, 0, 0};
    uint8_t display_7seg_map[10] = {0x03, 0x9f, 0x25, 0x0d, 0x99, 0x49, 0x41,
                                    0x1f, 0x01, 0x09}; // 0->9
    uint16_t display_index = 0;
    uint8_t spi_buffer = 0xff;

    enum StatusCode initDisplay()
    {
        HAL_GPIO_WritePin(LED_LATCH_GPIO_Port, LED_LATCH_Pin, 1);

        HAL_GPIO_WritePin(LED_LATCH_GPIO_Port, LED_LATCH_Pin, 0);
        if (HAL_SPI_Transmit(&hspi1, (void *)&spi_buffer, 1, 1) != HAL_OK)
        {
            HAL_GPIO_WritePin(LED_LATCH_GPIO_Port, LED_LATCH_Pin, 1);
            return STATUS_ERROR;
        }
        HAL_GPIO_WritePin(LED_LATCH_GPIO_Port, LED_LATCH_Pin, 1);
        return STATUS_OK;
    }

    /**
     * @brief Display scan function
     * @note This function should be called in a timer interrupt
     */
    void displayScan()
    {
        spi_buffer = display_buffer[display_index];
        switch (display_index)
        {
        case 0:
            HAL_GPIO_WritePin(LED7_EN1_GPIO_Port, LED7_EN1_Pin, 1);
            HAL_GPIO_WritePin(LED7_EN2_GPIO_Port, LED7_EN2_Pin, 0);
            HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, 1);
            break;
        case 1:
            HAL_GPIO_WritePin(LED7_EN1_GPIO_Port, LED7_EN1_Pin, 0);
            HAL_GPIO_WritePin(LED7_EN2_GPIO_Port, LED7_EN2_Pin, 1);
            HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, 1);
            break;
        case 2:
            HAL_GPIO_WritePin(LED7_EN1_GPIO_Port, LED7_EN1_Pin, 1);
            HAL_GPIO_WritePin(LED7_EN2_GPIO_Port, LED7_EN2_Pin, 1);
            HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, 0);
            break;
        default:
            break;
        }

        display_index = (display_index + 1) % 3;

        HAL_GPIO_WritePin(LED_LATCH_GPIO_Port, LED_LATCH_Pin, 0);
        HAL_SPI_Transmit(&hspi1, (void *)&spi_buffer, 1, 1);
        HAL_GPIO_WritePin(LED_LATCH_GPIO_Port, LED_LATCH_Pin, 1);
    }

    /**
     * @brief Display a number on 7-segment display
     * @param number Number to display
     * @return None
     * @note display_buffer[1] is the left digit, display_buffer[0] is the right digit
     */
    void displayLed7Seg(const uint8_t number)
    {
        display_buffer[1] = display_7seg_map[number / 10];
        display_buffer[0] = display_7seg_map[number % 10];
    }

    uint8_t mirrorByte(uint8_t data_byte)
    {
        data_byte = (data_byte & 0xF0) >> 4 | (data_byte & 0x0F) << 4;
        data_byte = (data_byte & 0xCC) >> 2 | (data_byte & 0x33) << 2;
        data_byte = (data_byte & 0xAA) >> 1 | (data_byte & 0x55) << 1;
        return data_byte;
    }

    /**
     * @brief Display a byte on 8 LEDs
     * @param data_byte Data byte to display
     * @note because the LEDs are connected in reverse order,
     * we need to mirror the byte and then reverse the bits of the byte
     */
    void displayLeds(const uint8_t data_byte)
    {
        display_buffer[2] = ~mirrorByte(data_byte);
    }

    void toggleLedDebug()
    {
        HAL_GPIO_TogglePin(LED_DEBUG_GPIO_Port, LED_DEBUG_Pin);
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */