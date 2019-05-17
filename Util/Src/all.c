#include "all.h"

uint32_t uart1_idle;

uint8_t uart1_data[UART1_DATA_MAX];

DMAQueue dmaQueue_uart1;