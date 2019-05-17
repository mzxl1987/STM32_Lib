#ifndef __UARTUTIL_H__
#define __UARTUTIL_H__

#include "stm32f1xx_hal.h"

#include "uartBuffer.h"

#define ATFRAME_MAX_LENGTH 1024

typedef struct{
	
	UART_HandleTypeDef * uart;
	uint16_t length;
	uint8_t *data;
	const uint16_t MAX;
	
} UartFrame;


void              UartFrame_clear(UartFrame * f);
void              UartFrame_analysis(UartFrame * f);
uint8_t           UartFrame_find(UartFrame * u, uint8_t * head,uint32_t head_len,uint8_t * tail,uint32_t tail_len,uint32_t * dest_index,uint32_t * dest_len);
uint8_t           UartFrame_equal(UartFrame * f, uint8_t * src,uint32_t len);
uint8_t           UartFrame_equalFromIndex(UartFrame * f,uint16_t readIndex,uint8_t * src,uint32_t len);









































#endif
