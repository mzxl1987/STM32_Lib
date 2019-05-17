/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define WDI_Pin GPIO_PIN_2
#define WDI_GPIO_Port GPIOC
#define Lora_PowerON_Pin GPIO_PIN_3
#define Lora_PowerON_GPIO_Port GPIOC
#define LouDian_I_Pin GPIO_PIN_0
#define LouDian_I_GPIO_Port GPIOA
#define DengGan_V_Pin GPIO_PIN_1
#define DengGan_V_GPIO_Port GPIOA
#define Lora_TX_Pin GPIO_PIN_2
#define Lora_TX_GPIO_Port GPIOA
#define Lora_RX_Pin GPIO_PIN_3
#define Lora_RX_GPIO_Port GPIOA
#define EXIT_P1_Pin GPIO_PIN_4
#define EXIT_P1_GPIO_Port GPIOA
#define EXIT_P1_EXTI_IRQn EXTI4_IRQn
#define EXIT_IV1_Pin GPIO_PIN_5
#define EXIT_IV1_GPIO_Port GPIOA
#define EXIT_IV1_EXTI_IRQn EXTI9_5_IRQn
#define EXIT_P2_Pin GPIO_PIN_6
#define EXIT_P2_GPIO_Port GPIOA
#define EXIT_P2_EXTI_IRQn EXTI9_5_IRQn
#define SEL1_Pin GPIO_PIN_7
#define SEL1_GPIO_Port GPIOA
#define SEL2_Pin GPIO_PIN_4
#define SEL2_GPIO_Port GPIOC
#define SEL3_Pin GPIO_PIN_5
#define SEL3_GPIO_Port GPIOC
#define EXIT_IV2_Pin GPIO_PIN_0
#define EXIT_IV2_GPIO_Port GPIOB
#define EXIT_IV2_EXTI_IRQn EXTI0_IRQn
#define EXIT_P3_Pin GPIO_PIN_1
#define EXIT_P3_GPIO_Port GPIOB
#define EXIT_P3_EXTI_IRQn EXTI1_IRQn
#define EXIT_IV3_Pin GPIO_PIN_7
#define EXIT_IV3_GPIO_Port GPIOE
#define EXIT_IV3_EXTI_IRQn EXTI9_5_IRQn
#define Dim1_Pin GPIO_PIN_9
#define Dim1_GPIO_Port GPIOE
#define Light1_Pin GPIO_PIN_10
#define Light1_GPIO_Port GPIOE
#define Dim2_Pin GPIO_PIN_11
#define Dim2_GPIO_Port GPIOE
#define Light2_Pin GPIO_PIN_12
#define Light2_GPIO_Port GPIOE
#define Dim3_Pin GPIO_PIN_13
#define Dim3_GPIO_Port GPIOE
#define Light3_Pin GPIO_PIN_14
#define Light3_GPIO_Port GPIOE
#define EEPROM_SCL_Pin GPIO_PIN_10
#define EEPROM_SCL_GPIO_Port GPIOB
#define EEPROM_SDA_Pin GPIO_PIN_11
#define EEPROM_SDA_GPIO_Port GPIOB
#define NB_DTR_Pin GPIO_PIN_12
#define NB_DTR_GPIO_Port GPIOB
#define NB_NRESET_Pin GPIO_PIN_13
#define NB_NRESET_GPIO_Port GPIOB
#define NB_PSIM_Pin GPIO_PIN_14
#define NB_PSIM_GPIO_Port GPIOB
#define NB_PowerKey_Pin GPIO_PIN_15
#define NB_PowerKey_GPIO_Port GPIOB
#define NB_TX_Pin GPIO_PIN_8
#define NB_TX_GPIO_Port GPIOD
#define NB_RX_Pin GPIO_PIN_9
#define NB_RX_GPIO_Port GPIOD
#define NB_RTS_Pin GPIO_PIN_10
#define NB_RTS_GPIO_Port GPIOD
#define Lora_EN_Pin GPIO_PIN_11
#define Lora_EN_GPIO_Port GPIOD
#define DEBUG_TX_Pin GPIO_PIN_9
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_10
#define DEBUG_RX_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOB
#define DS3231_SCL_Pin GPIO_PIN_6
#define DS3231_SCL_GPIO_Port GPIOB
#define DS3231_SDA_Pin GPIO_PIN_7
#define DS3231_SDA_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define LOW GPIO_PIN_RESET
#define HIGH GPIO_PIN_SET
#define Dim1 TIM_CHANNEL_1
#define Dim2 TIM_CHANNEL_2
#define Dim3 TIM_CHANNEL_3
/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
