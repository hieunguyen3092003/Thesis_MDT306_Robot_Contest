/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M1_DIR_Pin GPIO_PIN_13
#define M1_DIR_GPIO_Port GPIOC
#define M2_DIR_Pin GPIO_PIN_14
#define M2_DIR_GPIO_Port GPIOC
#define LED_DEBUG_Pin GPIO_PIN_15
#define LED_DEBUG_GPIO_Port GPIOC
#define BUZZER_Pin GPIO_PIN_0
#define BUZZER_GPIO_Port GPIOA
#define M4_DIR_Pin GPIO_PIN_1
#define M4_DIR_GPIO_Port GPIOA
#define M3_DIR_Pin GPIO_PIN_2
#define M3_DIR_GPIO_Port GPIOB
#define ENCODER3_B_Pin GPIO_PIN_12
#define ENCODER3_B_GPIO_Port GPIOB
#define ENCODER3_A_Pin GPIO_PIN_13
#define ENCODER3_A_GPIO_Port GPIOB
#define ENCODER4_B_Pin GPIO_PIN_14
#define ENCODER4_B_GPIO_Port GPIOB
#define ENCODER4_A_Pin GPIO_PIN_15
#define ENCODER4_A_GPIO_Port GPIOB
#define LED_EN_Pin GPIO_PIN_8
#define LED_EN_GPIO_Port GPIOA
#define LED7_EN2_Pin GPIO_PIN_11
#define LED7_EN2_GPIO_Port GPIOA
#define LED7_EN1_Pin GPIO_PIN_12
#define LED7_EN1_GPIO_Port GPIOA
#define INPUT_LOAD_Pin GPIO_PIN_15
#define INPUT_LOAD_GPIO_Port GPIOA
#define ENCODER2_A_Pin GPIO_PIN_10
#define ENCODER2_A_GPIO_Port GPIOC
#define ENCODER2_B_Pin GPIO_PIN_11
#define ENCODER2_B_GPIO_Port GPIOC
#define LED_LATCH_Pin GPIO_PIN_12
#define LED_LATCH_GPIO_Port GPIOC
#define ENCODER1_B_Pin GPIO_PIN_2
#define ENCODER1_B_GPIO_Port GPIOD
#define SM_FAULT_Pin GPIO_PIN_3
#define SM_FAULT_GPIO_Port GPIOB
#define SM_STEP_Pin GPIO_PIN_4
#define SM_STEP_GPIO_Port GPIOB
#define SM_DIR_Pin GPIO_PIN_5
#define SM_DIR_GPIO_Port GPIOB
#define RC_SERVO_3_Pin GPIO_PIN_6
#define RC_SERVO_3_GPIO_Port GPIOB
#define RC_SERVO_2_Pin GPIO_PIN_7
#define RC_SERVO_2_GPIO_Port GPIOB
#define RC_SERVO_1_Pin GPIO_PIN_8
#define RC_SERVO_1_GPIO_Port GPIOB
#define ENCODER1_A_Pin GPIO_PIN_9
#define ENCODER1_A_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
