#include "all.h"

uint32_t uart1_idle;

uint8_t uart1_data_DMA[UART1_DATA_MAX];
uint8_t uart1_data[UART1_DATA_MAX];

DMAQueue dmaQueue_uart1;
UartFrame uartFrame_uart1 = {
	.uart = &huart1,
	.data = uart1_data,
	.length = 0,
	.MAX = UART1_DATA_MAX
};

