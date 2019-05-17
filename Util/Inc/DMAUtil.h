#ifndef __DMAUTIL_H__
#define __DMAUTIL_H__

#include "stm32f1xx_hal.h"

typedef struct{
	uint8_t readOnly;	      //1:表示只读, 0:表示只写
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



/**        插入产生空闲中断时的下标       **/
uint8_t DMAQueue_push(DMAQueue * dmaQueue,UART_HandleTypeDef uart);

/**        读取数据DMA中的缓存数据      **/
uint8_t DMAQueue_pop(DMAQueue * dmaQueue, uint16_t * from, uint16_t * length);

/**        判断队列是否为空        **/
uint8_t DMAQueue_empty(DMAQueue * dmaQueue);









































#endif
