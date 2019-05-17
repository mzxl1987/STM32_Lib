#ifndef __ALL_H__
#define __ALL_H__







//STM32CubeMX ����
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

//�û��Զ���
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


//define ����
#define DEBUG 1
#define VERSION "STM32_LIB_V1.1.1.20190325"
#define UART1_DATA_MAX 1024


//�������ݽṹ��



//�����������
extern uint32_t uart1_idle;
extern uint8_t uart1_data[];

//����ṹ�����
extern DMAQueue dmaQueue_uart1;


































#endif
