#ifndef __ALL_H__
#define __ALL_H__







//STM32CubeMX 生成
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "crc.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

//STLIB
#include "string.h"
#include "stdlib.h"

//用户自定义
//#include "config.h"
//#include "miniConfig.h"
//#include "gpioUtil.h"
//#include "arrayUtil.h"
//#include "ds3231Util.h"
//#include "eepromUtil.h"
//#include "flashUtil.h"
//#include "systemUtil.h"
//#include "rtcUtil.h"
//#include "lightUtil.h"
//#include "nbUtil.h"
//#include "equipUtil.h"
//#include "crcUtil.h"
#include "printUtil.h"
#include "DMAUtil.h"
#include "uartBuffer.h"
#include "ATUtil.h"
//#include "ProtocolUtil.h"
//#include "LTE_M8321.h"


//define 数据
#define DEBUG 1
#define VERSION "STM32_LIB_V1.1.1.20190325"
#define UART1_DATA_MAX 1024


//定义数据结构体



//定义基本变量
extern uint32_t uart1_idle;
extern uint8_t uart1_data[];

//定义结构体变量
extern DMAQueue dmaQueue_uart1;


































#endif
