#include "systemUtil.h"
#include "stm32f1xx_hal_rtc.h"
#include "stdarg.h"



/*****************************************
***** ����������
******************************************/
void softReset(void) 

{ 
	__set_FAULTMASK(1);      // �ر������ж� 
	__disable_fault_irq();
	HAL_NVIC_SystemReset();
}

/** ������ת  ---------------------------------------  **/     
void jump_to_app(uint32_t addr)
{

	pFunction goApp;
	uint32_t JumpAddress;

	/* If Program has been written */
	if (((*(__IO uint32_t*)addr) & 0x2FFE0000 ) == 0x20000000)
		{
		
			__disable_irq();          //�ر��жϱ���Ҫ�ӣ�����APP�޷������ж�
			
			JumpAddress = *(__IO uint32_t*) (addr + 4);
			goApp = (pFunction)JumpAddress;
			
			__set_PSP(*(__IO uint32_t*) addr);                  //�������ý���PSP��ջ��ַ
      __set_CONTROL(0);                                                           //����ΪMSP
			__set_MSP(*(__IO uint32_t*) addr);
			
			goApp(); 
			
		}
}

uint8_t timeOver(uint32_t pre, uint32_t SPAN){
	uint32_t now = HAL_GetTick();
	if(now < pre)   return 1;
	return (now - pre) > SPAN;
}






