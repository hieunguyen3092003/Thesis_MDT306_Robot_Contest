/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>

#include "software_timer.h"
#include "servo.h"
#include "step_motor.h"
#include "move.h"
#include "uart.h"
#include "buzzer.h"
#include "encoder.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
void initSystem();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM5_Init();

  /* USER CODE BEGIN 2 */
  initSystem();
  sTimer2Set(0, 1000);
  sTimer4Set(0, 1000);
  stop();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /*
   *
   * TEST DATA ENCODER
   *
   */
  uint8_t count = 0;
  int32_t a = 0;
  int32_t b = 0;
  int32_t c = 0;
  int32_t d = 0;
  //  uint8_t data_encoder[8];
  //  uint8_t pid_debug = 0;

  //  uint8_t servo_debug = 2;
  char wheel1[100];
  char wheel2[100];
  char wheel3[100];
  char wheel4[100];

  char x = 255;
  char y = ':';

  uint8_t bytes[4];

  servo_set_angle(3, 90);
  while (1)
  {
    if (flag_timer2 == 1)
    {
      flag_timer2 = 0;
      count = (count + 1) % 20;
      if (count == 0)
      {
        HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
        HAL_UART_Transmit(&huart2, (void *)wheel1, sprintf((void *)wheel1, "%ld", abs(encoder_pulse[0])), 10);
        HAL_UART_Transmit(&huart2, y, 1, 10);
        HAL_UART_Transmit(&huart2, (void *)wheel2, sprintf((void *)wheel2, "%ld", abs(encoder_pulse[1])), 10);
        HAL_UART_Transmit(&huart2, y, 1, 10);
        HAL_UART_Transmit(&huart2, (void *)wheel3, sprintf((void *)wheel3, "%ld", abs(encoder_pulse[2])), 10);
        HAL_UART_Transmit(&huart2, y, 1, 10);
        HAL_UART_Transmit(&huart2, (void *)wheel4, sprintf((void *)wheel4, "%ld", abs(encoder_pulse[3])), 10);
        HAL_UART_Transmit(&huart2, &x, 1, 10);

        encoder_pulse[0] = 0;
        encoder_pulse[1] = 0;
        encoder_pulse[2] = 0;
        encoder_pulse[3] = 0;
      }
      move_process();
      servo_process();
      sm_process();
    }

    //    data_encoder[0] = HAL_GPIO_ReadPin(ENCODER1_A_GPIO_Port, ENCODER1_A_Pin);
    //    data_encoder[1] = HAL_GPIO_ReadPin(ENCODER2_A_GPIO_Port, ENCODER2_A_Pin);
    //    data_encoder[2] = HAL_GPIO_ReadPin(ENCODER3_A_GPIO_Port, ENCODER3_A_Pin);
    //    data_encoder[3] = HAL_GPIO_ReadPin(ENCODER4_A_GPIO_Port, ENCODER4_A_Pin);
    //    data_encoder[4] = HAL_GPIO_ReadPin(ENCODER1_B_GPIO_Port, ENCODER1_B_Pin);
    //    data_encoder[5] = HAL_GPIO_ReadPin(ENCODER2_B_GPIO_Port, ENCODER2_B_Pin);
    //    data_encoder[6] = HAL_GPIO_ReadPin(ENCODER3_B_GPIO_Port, ENCODER3_B_Pin);
    //    data_encoder[7] = HAL_GPIO_ReadPin(ENCODER4_B_GPIO_Port, ENCODER4_B_Pin);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void initSystem()
{
  initTimer2();
  initTimer4();

  servo_init(3);
  buzzer_init();
  dc_init();
  uart_init();
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
