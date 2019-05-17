
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */


#include "config.h"

#include "rtcUtil.h"
#include "i2c.h"
#include "flashUtil.h"
#include "systemUtil.h"


/*******************   重写printf函数  *************************/
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
return ch;
}

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/*****************************************************************/
uint32_t ApplicationAddress;   //程序起始地址

uint32_t runningArea;          //当前程序运行区
uint32_t app_reBootTimes;   //app上次运行时长
uint32_t tmp;

_calendar_obj calendar;				//时钟结构体 

/*****************************************************************/


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  MX_TIM3_Init();
//  MX_RTC_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
	{
		
		printf("************************************\r\n");
		printf("***     Start From BootLoader    ***\r\n");
		printf("************************************\r\n");
		
		/** 自定义配置RTC时钟  ------------------------------ **/
		MY_RTC_Init(&hrtc);
		
		RTC_Get(&hrtc);				
		printf("*****************************************************\r\n");
		printf("**   RTC当前时间 : %04d-%02d-%02d %02d:%02d:%02d   **\r\n",
			calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec
		);
		printf("*****************************************************\r\n");
		HAL_Delay(500);
		/** 打开TIM3定时器中断 -------------------------------------------------- **/
		HAL_TIM_Base_Start_IT(&htim3);
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		HAL_I2C_Mem_Read(&hi2c2,I2C_EEPROM_OWN_ADDR,EERROM_RUN_AERA_ADDR,I2C_MEMADD_SIZE_16BIT,(uint8_t*)&runningArea,EERROM_RUN_AERA_SIZE,0xFFFF);
		HAL_Delay(10);
		printf("程序运行区 : 0x%08X\r\n",runningArea);
		
		/** 程序需要升级  -----------------------------------**/
		if(runningArea != 0xFF && runningArea & FLAG_NEED_UPDATE){
		
			HAL_FLASH_Unlock();
			printf(" >> 升级程序,拷贝程序到程序区......\r\n");
			if(flash_copy(FLASH_ADDR_APP_STORAGE,FLASH_ADDR_APP,FLASH_APP_SIZE,PAGE_SIZE) == HAL_OK){
				printf(" >> 程序拷贝完成\r\n");
				
				printf(" >> 比较拷贝元数据和目标数据是否相同\r\n");
				if(flash_compare(FLASH_ADDR_APP_STORAGE,FLASH_ADDR_APP,FLASH_APP_SIZE) == HAL_OK){
					printf(" >> Flash数据比较结束,完全相同\r\n");
					
					app_reBootTimes = 0;
					HAL_I2C_Mem_Write(&hi2c2,I2C_EEPROM_OWN_ADDR,EERROM_REBOOT_TIMES_ADDR,I2C_MEMADD_SIZE_16BIT,(uint8_t*)&app_reBootTimes,EERROM_REBOOT_TIMES_SIZE,0xFFFF);	
					HAL_Delay(10);
					
				}
				else{
					printf(" >> 原数据与目标程序数据不相同,打印Storage数据:\r\n");
					flash_print(FLASH_ADDR_APP_STORAGE,FLASH_APP_SIZE);
				}
				
			}else{
				printf(" >> 程序拷贝失败XX\r\n");
			}
			HAL_FLASH_Lock();
			
			runningArea = runningArea & (~FLAG_NEED_UPDATE);  //获取程序运行区,同时擦除 [FLAG_NEED_UPDATE] 标志位
			HAL_I2C_Mem_Write(&hi2c2,I2C_EEPROM_OWN_ADDR,EERROM_RUN_AERA_ADDR,I2C_MEMADD_SIZE_16BIT,(uint8_t*)&runningArea,EERROM_RUN_AERA_SIZE,0xFFFF);	
			HAL_Delay(10);   //注意对EEPROM读写需要延时
		
		/** 程序无需升级  -------------------------------------**/	
		}else{
			
			if(runningArea == 0xFF){
				runningArea = 0x00;
				runningArea = runningArea & (~FLAG_NEED_UPDATE);  //获取程序运行区,同时擦除 [FLAG_NEED_UPDATE] 标志位
				HAL_I2C_Mem_Write(&hi2c2,I2C_EEPROM_OWN_ADDR,EERROM_RUN_AERA_ADDR,I2C_MEMADD_SIZE_16BIT,(uint8_t*)&runningArea,EERROM_RUN_AERA_SIZE,0xFFFF);	
				HAL_Delay(10);   //注意对EEPROM读写需要延时
			}
			
			/** 获取App运行次数  --------------------------------------------------- **/
			HAL_I2C_Mem_Read(&hi2c2,I2C_EEPROM_OWN_ADDR,EERROM_REBOOT_TIMES_ADDR,I2C_MEMADD_SIZE_16BIT,(uint8_t*)&app_reBootTimes,EERROM_REBOOT_TIMES_SIZE,0xFFFF);
			HAL_Delay(10);
			
		}
				
		if(app_reBootTimes > MAX_REBOOT_TIMES){
			ApplicationAddress = FLASH_ADDR_APP_BAK;    //基本版升级程序
			printf("运行[基本版升级程序]\r\n");
		}else{
			ApplicationAddress = FLASH_ADDR_APP;    //APP区程序
			printf("运行[APP程序]\r\n");
		}
		
		/** 累加APP重启次数  --------------------------------------------------- **/
		printf(" >> 程序APP重启次数 : 0x%08X\r\n",app_reBootTimes);
		app_reBootTimes ++;
		HAL_I2C_Mem_Write(&hi2c2,I2C_EEPROM_OWN_ADDR,EERROM_REBOOT_TIMES_ADDR,I2C_MEMADD_SIZE_16BIT,(uint8_t*)&app_reBootTimes,EERROM_REBOOT_TIMES_SIZE,0xFFFF);	
		HAL_Delay(10);
		
		printf("跳转至 APP[0x%08X]\r\n",ApplicationAddress);
		printf("************************************\r\n");
		jump_to_app(ApplicationAddress);
		
		printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
		printf("xx           JUMP  ERROR          xx\r\n");
		printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
		HAL_Delay(1000);
		
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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* RTC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(RTC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(RTC_IRQn);
}

/* USER CODE BEGIN 4 */



/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM8 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM8) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
