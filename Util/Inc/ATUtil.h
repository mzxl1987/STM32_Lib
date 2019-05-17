#ifndef __ATUTIL_H__
#define __ATUTIL_H__

#include "stm32f1xx_hal.h"

#include "uartBuffer.h"

#define ATFRAME_MAX_LENGTH 1024

typedef struct{
	
	uint16_t length;
	uint8_t data[ATFRAME_MAX_LENGTH];
	
} ATFrame;

extern ATFrame atFrame;
extern ATFrame atFrame_uart1;

void              ATFrame_copy(UartBuffer * src,uint16_t from,uint16_t length);
void              ATFrame_clear(ATFrame * atFrame);
void              ATFrame_analysis(void);
uint8_t           ATFrame_find(uint8_t * head,uint32_t head_len,uint8_t * tail,uint32_t tail_len,uint32_t * dest_index,uint32_t * dest_len);
uint8_t           ATFrame_equal(uint8_t * src,uint32_t len);
uint8_t           ATFrame_equalFromIndex(uint16_t readIndex,uint8_t * src,uint32_t len);
uint8_t           ATFrame_uart1_analysis(ATFrame * atFrame);









































#endif
