#include "DMAUtil.h"

#include "all.h"

DMAQueue dmaQueue;
DMAQueue dmaQueue_uart1;


/**        插入产生空闲中断时的下标       **/
uint8_t DMAQueue_push(DMAQueue * dmaQueue, uint16_t remainCount){

	println("DMA Queue PUSH Begin");

	uint16_t usedCount = UART_BUFFER_MAX_LENGTH - remainCount;    //已使用数量
	
	printf("DMA Queue : writeIndex = %04d ,preUsedCount = %04d ,已使用：%04d bytes, 未使用：%04d bytes\r\n",dmaQueue->writeIndex, dmaQueue->preUsedCount ,usedCount,remainCount);
	
	if(usedCount == dmaQueue->preUsedCount){
			println("DMA Queue插入失败, usedCount == preUsedCount, 没有新数据增加!");
			return 0;
	}		

	DMAInfo *info = &dmaQueue->item[dmaQueue->writeIndex];   //获取数据
	
	if(info->readOnly){    //如果数据尚未读取，则丢弃；将readIndex + 1
		dmaQueue->readIndex = (dmaQueue->readIndex == (DMA_QUEUE_LENGTH - 1) ? 0 : dmaQueue->readIndex + 1);		
	}
			
	info->fromIndex =  dmaQueue->preUsedCount % UART_BUFFER_MAX_LENGTH;          //获取需要截取数据的起始下标
	info->length = dmaQueue->preUsedCount < usedCount ? usedCount - dmaQueue->preUsedCount : (UART_BUFFER_MAX_LENGTH - dmaQueue->preUsedCount) + usedCount;    //获取需要截取数据的长度
	info->readOnly = 1;
	
	//printf("DMA Queue Item index = %04d, fromIndex = %04d, length = %04d, readOnly = %d \r\n",dmaQueue->writeIndex,info->fromIndex, info->length,info->readOnly);
	
	dmaQueue->preUsedCount = usedCount;            //记住当前使用数量	
	dmaQueue->writeIndex = (dmaQueue->writeIndex == (DMA_QUEUE_LENGTH - 1) ? 0 : dmaQueue->writeIndex + 1);		//写游标 writeIndex + 1
	
	
	
	println("DMA Queue PUSH 成功!");
	println("DMA Queue PUSH End");
	
	return 1;

}

/**        读取数据DMA中的缓存数据      **/
uint8_t DMAQueue_pop(DMAQueue * dmaQueue, uint16_t * from, uint16_t * length){
	println("DMA Queue POP Begin");
	DMAInfo *info = &dmaQueue->item[dmaQueue->readIndex];

	if(info->readOnly){
	
		*from = info->fromIndex;
		*length = info->length;		
		info->readOnly = 0;       //将readOnly游标修改为可写
		dmaQueue->readIndex = (dmaQueue->readIndex == (DMA_QUEUE_LENGTH - 1) ? 0 : dmaQueue->readIndex + 1);		 //读游标 readIndex + 1
		println("DMA Queue POP 成功!");
		return 1;
	}
	
	println("DMA Queue POP End");

	return 0;
}

/**        判断队列是否为空        **/
uint8_t DMAQueue_empty(DMAQueue * dmaQueue){
	//DMAInfo *info = &dmaQueue->item[dmaQueue->readIndex];
	//printf("DMA Queue Empty : readIndex = %04d, from = %04d, length = %04d, readOnly = %d\r\n",dmaQueue->readIndex,info->fromIndex,info->length,info->readOnly);
	
	return !dmaQueue->item[dmaQueue->readIndex].readOnly;

}


















