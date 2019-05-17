#ifndef __systemUtil_H__
#define __systemUtil_H__

#include "stm32f1xx_hal.h"
#include "config.h"


/*****************************************
***** ����������
******************************************/
void softReset(void);

/** ������ת  ---------------------------------------  **/     
void jump_to_app(uint32_t addr);

uint8_t timeOver(uint32_t pre, uint32_t SPAN);

#endif
