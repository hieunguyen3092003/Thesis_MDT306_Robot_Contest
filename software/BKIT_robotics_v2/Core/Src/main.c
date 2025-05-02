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
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdint.h>

#include "global.h"
#include "software_timer.h"

#include "servo.h"
#include "motor.h"
#include "encoder.h"
#include "step_motor.h"
#include "line_sensor.h"
#include "gamepad.h"
#include "module_mke_m15.h"

#include "button.h"
#include "switch.h"

#include "display.h"
#include "buzzer.h"

#include "uart.h"
#include "utils.h"

#include "robot_firmware.h"

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
  MX_DMA_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM5_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */

  displayLed7Seg((uint8_t)getModeId());
  (void)setupRobot();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    (void)processRobot();

    // if (getFlagUart1())
    // {
    // }
    // if (getFlagUart2())
    // {
    // }
    // if (sTimer2GetFlag())
    // {
    // SensorScan();
    // displayLeds(getSensorState());
    // displayLed7Seg(SensorGetLineStatus());

    // if (readGamepadData() == STATUS_OK)
    // {
    //   if (isGamepadButtonPressed(BUTTON_UP))
    //   {
    //     displayLeds(getGamepadData()[1]);
    //     moveDirection(FORWARD, 50);
    //   }
    //   else if (isGamepadButtonPressed(BUTTON_DOWN))
    //   {
    //     displayLeds(getGamepadData()[1]);
    //     moveDirection(BACKWARD, 50);
    //   }
    //   else if (isGamepadButtonPressed(BUTTON_LEFT))
    //   {
    //     displayLeds(getGamepadData()[1]);
    //     moveDirection(LEFT, 50);
    //   }
    //   else if (isGamepadButtonPressed(BUTTON_RIGHT))
    //   {
    //     displayLeds(getGamepadData()[1]);
    //     moveDirection(RIGHT, 50);
    //   }

    //   else if (isGamepadButtonPressed(BUTTON_SQUARE))
    //   {
    //     displayLeds(getGamepadData()[27]);
    //     moveDirection(ROTATE_LEFT, 50);
    //   }
    //   else if (isGamepadButtonPressed(BUTTON_CIRCLE))
    //   {
    //     displayLeds(getGamepadData()[27]);
    //     moveDirection(ROTATE_RIGHT, 50);
    //   }
    //   else
    //   {
    //     scanButton();
    //     if (isButtonPressed(BUTTON_1))
    //     {
    //       moveForward(50);
    //     }
    //     else if (isButtonPressed(BUTTON_2))
    //     {
    //       moveBackward(50);
    //     }
    //     else if (isButtonPressed(BUTTON_3))
    //     {
    //       moveLeft(50);
    //     }
    //     else if (isButtonPressed(BUTTON_4))
    //     {
    //       moveRight(50);
    //     }
    //     else
    //     {
    //       motorStop();
    //     }
    //   }
    // }

    // HAL_GPIO_TogglePin(LED_DEBUG_GPIO_Port, LED_DEBUG_Pin);
    // scanButton();
    // displayLed7Seg(state);
    // if (state == 0)
    // {
    //   if (isButtonPressed(1))
    //   {
    //     state = 1;
    //   }
    // }
    // else if (state == 1)
    // {
    //   autoProcess();
    //   motorStop();
    //   state = 0;
    // }
    // else if (state == 2)
    // {
    //   followLineForward();
    //   if (isButtonPressed(1))
    //   {
    //     state = 2;
    //     motorStop();
    //   }
    // }
    // else if (state == 3)
    // {
    //   goLeftUntilMeetLine();
    //   if (isButtonPressed(1))
    //   {
    //     state = 0;
    //     motorStop();
    //   }
    // }
    // else if (state == 4)
    // {
    //   goRightUntilMeetLine();
    //   if (isButtonPressed(1))
    //   {
    //     state = 0;
    //     motorStop();
    //   }
    // }

    // if (isButtonPressed(0))
    // {
    //   stepMotorMove(UP, 5);
    //   HAL_Delay(5000);
    //   motorStop();
    // }

    // if (isButtonPressed(2))
    // {
    //   state = 3;
    // }

    // if (isButtonPressed(3))
    // {
    //   state = 4;
    // }
    //      followLine();
    // }

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void autoProcess()
{
  servoSetAngle(3, 1);
  stepMotorMove(UP, 10);
  HAL_Delay(3000);
  goToTheNthCross(4);
  rotateRight(35);
  HAL_Delay(1100);
  motorStop();
  goLeftUntilMeetLine();
  goToTheNthCross(2);
  moveForward(35);
  HAL_Delay(350);
  motorStop();
  HAL_Delay(2000);
  stepMotorMove(DOWN, 10);
  HAL_Delay(3000);
  servoSetAngle(3, 40);
  HAL_Delay(2000);
  stepMotorMove(UP, 10);
  HAL_Delay(3000);
  rotateLeft(35);
  HAL_Delay(1100);
  motorStop();
  goLeftUntilMeetLine();
  goToTheNthCross(2);
  moveForward(40);
  HAL_Delay(350);
  motorStop();
  stepMotorMove(DOWN, 10);
  HAL_Delay(3000);
  servoSetAngle(3, 1);
  HAL_Delay(2000);
  stepMotorMove(UP, 10);
  HAL_Delay(3000);
  goBackwardUntilMeetLine();
  rotateLeft(35);
  HAL_Delay(1000);
  motorStop();
  moveForward(40);
  HAL_Delay(150);
  motorStop();
  goRightUntilMeetLine();
  goToTheNthCross(2);
  rotateRight(35);
  HAL_Delay(1000);
  motorStop();
  goLeftUntilMeetLine();
  goToTheNthCross(2);
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
