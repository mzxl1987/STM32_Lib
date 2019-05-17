#include "flashUtil.h"



/**  Flash指定区域擦除  -------------------------------------------------------- **/
HAL_StatusTypeDef flash_erase(uint32_t start_addr,uint32_t end_addr,uint32_t page_size){
	
	/*Variable used for Erase procedure*/
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError = 0;
	uint32_t tmp_addr = start_addr;

	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.NbPages     = 1;   //每次擦除1页数据
	
	while(tmp_addr < end_addr){
	
		EraseInitStruct.PageAddress = tmp_addr;
		
		if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) == HAL_OK){
			//printf("Flash 擦除 OK[0x%08X].\r\n",tmp_addr);
			tmp_addr += page_size;
		}
		else
		{
			printf("Flash 擦除 失败[0x%08X]!\r\n",tmp_addr);
			return HAL_ERROR;
		}
	}
	
	return HAL_OK;
	
}

///**  Flash指定地址写入  -------------------------------------------------------- **/
//void flash_write(uint32_t TypeProgram, uint32_t Address, uint64_t Data){
//	HAL_FLASH_Unlock();
//	HAL_FLASH_Program(TypeProgram,Address,Data);
//	HAL_FLASH_Lock();

//}

/** Flash写入数组  --------------------------------------------------------------  **/
HAL_StatusTypeDef flash_write_array(uint32_t addr_offset,uint32_t addr_max,uint8_t *data,uint32_t data_offset,uint32_t data_end_index){
	
	uint32_t flash_addr_offset = addr_offset,
					i = data_offset,
					innerData;
	
	for(; i < data_end_index && flash_addr_offset < addr_max;){
		
		innerData = (data[i]) | (data[i + 1] << 8) | (data[i + 2] << 16) | (data[i + 3] << 24);
		
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,flash_addr_offset,innerData) != HAL_OK){
			//printf("Flash[%08X] 写入ERROR\r\n",flash_addr_offset);
			return HAL_ERROR;
		}
		
		i += 4;
		flash_addr_offset += 4;
		
	}
	
	return HAL_OK;
	
}


/**  Flash区域复制  -------------------------------------------------------------- **/
HAL_StatusTypeDef flash_copy(uint32_t source_start_addr,uint32_t dest_start_addr, uint32_t copy_size,uint32_t page_size){
	
	uint32_t data32,sourAddr,destAddr;

	/**  目标区域擦除  --------------------------------------------- **/	
	const uint32_t MAX_ADDRESS = source_start_addr + copy_size;
	sourAddr = source_start_addr;
	destAddr = dest_start_addr;

	/** 擦除数据 ------------------------------------------ **/
	if(flash_erase(dest_start_addr,dest_start_addr + copy_size,page_size) == HAL_OK){
		
		/** 拷贝数据 ------------------------------------------**/
		while (sourAddr < MAX_ADDRESS)
		{
			data32 = *(__IO uint32_t *)sourAddr;

			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,destAddr,data32) == HAL_OK){
				sourAddr = sourAddr + 4;
				destAddr = destAddr + 4;
				//printf("flash写入[OK]:原地址[ADD:%08X][0x%08X] - 目标地址[0x%08X]\r\n",sourAddr,data32,destAddr);
			}else{
				//printf("flash写入[ERROR]:原地址[0x%08X] - 目标地址[0x%08X]\r\n",sourAddr,destAddr);
				return HAL_ERROR;
				break;
			}
		}
		
	}else{
		return HAL_ERROR;
	}
	

	return HAL_OK;

}

/**  Flash区域比较  -------------------------------------------------------------- **/
HAL_StatusTypeDef flash_compare(uint32_t source_start_addr,uint32_t dest_start_addr, uint32_t size){
		uint32_t i = 0;
		uint32_t data,data1;
		
		while (i < size){
			data = *(__IO uint32_t *)(source_start_addr + i);
			data1 = *(__IO uint32_t *)(dest_start_addr + i);
			if(data != data1){
				//printf("0x%08X[0x%08X]  -  0x%08X[0x%08X] - 0x%d\r\n",(source_start_addr + i),data,(dest_start_addr + i),data1,(data - data1));
				//return HAL_ERROR;
			}
			i += 4;
		}
		
		
		return HAL_OK;
}


/** 打印flash区域  ----------------------------------------------------- **/
void flash_print(uint32_t start_addr,uint32_t size){

	uint32_t end_addr = start_addr + size;
	uint32_t data;

	while(start_addr < end_addr){
	
		data = *(__IO uint32_t *)start_addr;
		printf("0x%08X ",data);
		start_addr = start_addr + 4;
	
	}

}






