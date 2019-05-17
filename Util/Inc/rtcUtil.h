#ifndef __rtcUtil_H__
#define __rtcUtil_H__

#include "stm32f1xx_hal.h"
#include "config.h"

extern _calendar_obj calendar;				//时钟结构体 

uint8_t                   MY_RTC_Init(RTC_HandleTypeDef * hrtc);
uint8_t                   Is_Leap_Year(uint16_t year);
HAL_StatusTypeDef         RTC_Set(RTC_HandleTypeDef *hrtc,uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec);
void                      RTC_Get(RTC_HandleTypeDef *hrtc);
uint8_t                   RTC_Get_Week(uint16_t year,uint8_t month,uint8_t day);


static HAL_StatusTypeDef      RTC_SetCounter(RTC_HandleTypeDef* hrtc, uint32_t TimeCounter);
static uint32_t               RTC_ReadTimeCounter(RTC_HandleTypeDef* hrtc);
static HAL_StatusTypeDef      RTC_EnterInitMode(RTC_HandleTypeDef* hrtc);
static HAL_StatusTypeDef      RTC_ExitInitMode(RTC_HandleTypeDef* hrtc);
static HAL_StatusTypeDef      RTC_WriteAlarmCounter(RTC_HandleTypeDef* hrtc, uint32_t AlarmCounter);


void                      printRTCTime(void);
/** 打印日志的时候前面加上时间 **/
void                      printRTCTime_Log(void);









#endif
