//#include "button.h"
//
//uint32_t button_count[8];
//uint8_t button_buffer = 0x00;
//
//void button_init()
//{
//    HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 1);
//}
//
//void button_scan()
//{
//    HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 0);
//    HAL_GPIO_WritePin(INPUT_LOAD_GPIO_Port, INPUT_LOAD_Pin, 1);
//    HAL_SPI_Receive(&hspi1, (void *)&button_buffer, 1, 10);
//
//    uint8_t mask = 0x01;
//    for (int i = 0; i < 8; i++)
//    {
//        if (button_buffer & mask)
//            button_count[i] = 0;
//        else
//            button_count[i]++;
//        mask = mask << 1;
//    }
//}
//
//uint8_t isButtonPresses(uint8_t index)
//{
//    if (index > 7)
//        return 0;
//    return button_count[index] == 1;
//}
