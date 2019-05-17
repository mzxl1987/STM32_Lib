#include "DMAUtil.h"

#include "all.h"

DMAQueue dmaQueue;
DMAQueue dmaQueue_uart1;


/**        ������������ж�ʱ���±�       **/
uint8_t DMAQueue_push(DMAQueue * dmaQueue, uint16_t remainCount){

	println("DMA Queue PUSH Begin");

	uint16_t usedCount = UART_BUFFER_MAX_LENGTH - remainCount;    //��ʹ������
	
	printf("DMA Queue : writeIndex = %04d ,preUsedCount = %04d ,��ʹ�ã�%04d bytes, δʹ�ã�%04d bytes\r\n",dmaQueue->writeIndex, dmaQueue->preUsedCount ,usedCount,remainCount);
	
	if(usedCount == dmaQueue->preUsedCount){
			println("DMA Queue����ʧ��, usedCount == preUsedCount, û������������!");
			return 0;
	}		

	DMAInfo *info = &dmaQueue->item[dmaQueue->writeIndex];   //��ȡ����
	
	if(info->readOnly){    //���������δ��ȡ����������readIndex + 1
		dmaQueue->readIndex = (dmaQueue->readIndex == (DMA_QUEUE_LENGTH - 1) ? 0 : dmaQueue->readIndex + 1);		
	}
			
	info->fromIndex =  dmaQueue->preUsedCount % UART_BUFFER_MAX_LENGTH;          //��ȡ��Ҫ��ȡ���ݵ���ʼ�±�
	info->length = dmaQueue->preUsedCount < usedCount ? usedCount - dmaQueue->preUsedCount : (UART_BUFFER_MAX_LENGTH - dmaQueue->preUsedCount) + usedCount;    //��ȡ��Ҫ��ȡ���ݵĳ���
	info->readOnly = 1;
	
	//printf("DMA Queue Item index = %04d, fromIndex = %04d, length = %04d, readOnly = %d \r\n",dmaQueue->writeIndex,info->fromIndex, info->length,info->readOnly);
	
	dmaQueue->preUsedCount = usedCount;            //��ס��ǰʹ������	
	dmaQueue->writeIndex = (dmaQueue->writeIndex == (DMA_QUEUE_LENGTH - 1) ? 0 : dmaQueue->writeIndex + 1);		//д�α� writeIndex + 1
	
	
	
	println("DMA Queue PUSH �ɹ�!");
	println("DMA Queue PUSH End");
	
	return 1;

}

/**        ��ȡ����DMA�еĻ�������      **/
uint8_t DMAQueue_pop(DMAQueue * dmaQueue, uint16_t * from, uint16_t * length){
	println("DMA Queue POP Begin");
	DMAInfo *info = &dmaQueue->item[dmaQueue->readIndex];

	if(info->readOnly){
	
		*from = info->fromIndex;
		*length = info->length;		
		info->readOnly = 0;       //��readOnly�α��޸�Ϊ��д
		dmaQueue->readIndex = (dmaQueue->readIndex == (DMA_QUEUE_LENGTH - 1) ? 0 : dmaQueue->readIndex + 1);		 //���α� readIndex + 1
		println("DMA Queue POP �ɹ�!");
		return 1;
	}
	
	println("DMA Queue POP End");

	return 0;
}

/**        �ж϶����Ƿ�Ϊ��        **/
uint8_t DMAQueue_empty(DMAQueue * dmaQueue){
	//DMAInfo *info = &dmaQueue->item[dmaQueue->readIndex];
	//printf("DMA Queue Empty : readIndex = %04d, from = %04d, length = %04d, readOnly = %d\r\n",dmaQueue->readIndex,info->fromIndex,info->length,info->readOnly);
	
	return !dmaQueue->item[dmaQueue->readIndex].readOnly;

}


















