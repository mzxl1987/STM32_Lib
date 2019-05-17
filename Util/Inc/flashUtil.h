#ifndef __flashUtil_H__
#define __flashUtil_H__

#include "stm32f1xx_hal.h"
#include "config.h"


/**  Flashָ���������  -------------------------------------------------------- **/
HAL_StatusTypeDef flash_erase(uint32_t start_addr,uint32_t end_addr,uint32_t page_size);


///**  Flashָ����ַд��  -------------------------------------------------------- **/
//void flash_write(uint32_t TypeProgram, uint32_t Address, uint64_t Data);

/** Flashд������  --------------------------------------------------------------  **/
HAL_StatusTypeDef flash_write_array(uint32_t addr_offset,uint32_t addr_max,uint8_t *data,uint32_t data_offset,uint32_t data_len);

/**  Flash������  -------------------------------------------------------------- **/
HAL_StatusTypeDef flash_copy(uint32_t source_start_addr,uint32_t dest_start_addr, uint32_t copy_size,uint32_t page_size);

/**  Flash����Ƚ�  -------------------------------------------------------------- **/
HAL_StatusTypeDef flash_compare(uint32_t source_start_addr,uint32_t dest_start_addr, uint32_t copy_size);

/** ��ӡflash����  ----------------------------------------------------- **/
void flash_print(uint32_t start_addr,uint32_t size);




#endif
