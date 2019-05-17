#include "systemUtil.h"
#include "stm32f1xx_hal_rtc.h"
#include "stdarg.h"



/*****************************************
***** 软重启命令
******************************************/
void softReset(void) 

{ 
	__set_FAULTMASK(1);      // 关闭所有中端 
	__disable_fault_irq();
	HAL_NVIC_SystemReset();
}

/** 程序跳转  ---------------------------------------  **/     
void jump_to_app(uint32_t addr)
{

	pFunction goApp;
	uint32_t JumpAddress;

	/* If Program has been written */
	if (((*(__IO uint32_t*)addr) & 0x2FFE0000 ) == 0x20000000)
		{
		
			__disable_irq();          //关闭中断必须要加，否则APP无法进入中断
			
			JumpAddress = *(__IO uint32_t*) (addr + 4);
			goApp = (pFunction)JumpAddress;
			
			__set_PSP(*(__IO uint32_t*) addr);                  //重新设置进程PSP堆栈地址
      __set_CONTROL(0);                                                           //设置为MSP
			__set_MSP(*(__IO uint32_t*) addr);
			
			goApp(); 
			
		}
}

uint8_t timeOver(uint32_t pre, uint32_t SPAN){
	uint32_t now = HAL_GetTick();
	if(now < pre)   return 1;
	return (now - pre) > SPAN;
}






