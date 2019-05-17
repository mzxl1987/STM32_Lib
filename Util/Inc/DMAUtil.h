#ifndef __DMAUTIL_H__
#define __DMAUTIL_H__

#include "stm32f1xx_hal.h"

typedef struct{
	uint8_t readOnly;	      //1:��ʾֻ��, 0:��ʾֻд
	uint16_t fromIndex;
	uint16_t length;
		
} DMAInfo;

#define DMA_QUEUE_LENGTH 50

typedef struct {

	uint16_t preUsedCount;
	uint16_t writeIndex;
	uint16_t readIndex;
	DMAInfo  item[DMA_QUEUE_LENGTH];

} DMAQueue;



/**        ������������ж�ʱ���±�       **/
uint8_t DMAQueue_push(DMAQueue * dmaQueue,UART_HandleTypeDef uart);

/**        ��ȡ����DMA�еĻ�������      **/
uint8_t DMAQueue_pop(DMAQueue * dmaQueue, uint16_t * from, uint16_t * length);

/**        �ж϶����Ƿ�Ϊ��        **/
uint8_t DMAQueue_empty(DMAQueue * dmaQueue);









































#endif
