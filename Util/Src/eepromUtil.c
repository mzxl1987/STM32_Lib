#include "eepromUtil.h"

#include "i2c.h"
 
/**************************************************
** EEPROM ������
** 1.i2c��������
** 2.�豸��ַ
** 3.EEPROM�ڴ��ַ
** 4.EEPROM�ڴ��ַ��С,���ݲ�ͬ��EEPROM���֡�һ��Ϊ8BIT,16BIT  2��
** 5.��������ݵ�ָ��
** 6.���ݴ�С
***************************************************/
HAL_StatusTypeDef EEPROM_Read(I2C_HandleTypeDef * hi2c,uint8_t deviceAddr,uint16_t MemAddress,uint32_t I2C_MEMADD_SIZE, uint8_t *pData, uint16_t Size)
{
    return HAL_I2C_Mem_Read(hi2c, deviceAddr, MemAddress,I2C_MEMADD_SIZE, pData, Size, 0xffff);
}

/**************************************************
** EEPROM ������
** 1.i2c��������
** 2.�豸��ַ
** 3.EEPROM�ڴ��ַ
** 4.EEPROM�ڴ��ַ��С,���ݲ�ͬ��EEPROM���֡�һ��Ϊ8BIT,16BIT  2��
** 5.��������ݵ�ָ��
** 6.���ݴ�С
***************************************************/
HAL_StatusTypeDef EEPROM_Read_To_Array(I2C_HandleTypeDef * hi2c,uint32_t MemAddress,uint8_t *pData, uint16_t Size)
{
    return EEPROM_Read(hi2c,I2C_EEPROM_OWN_ADDR, MemAddress,I2C_MEMADD_SIZE_16BIT, pData, Size);
}

/**************************************************
** EEPROM д����
** 1.i2c��������
** 2.�豸��ַ
** 3.EEPROM�ڴ��ַ
** 4.EEPROM�ڴ��ַ��С,���ݲ�ͬ��EEPROM���֡�һ��Ϊ8BIT,16BIT  2��
** 5.��д�����ݵ�ָ��
** 6.���ݴ�С
***************************************************/
//HAL_StatusTypeDef EEPROM_Write(I2C_HandleTypeDef * hi2c,uint8_t deviceAddr,uint16_t MemAddress,ulong I2C_MEMADD_SIZE, uint8_t *pData, uint16_t Size)
//{
//    return HAL_I2C_Mem_Write(hi2c, deviceAddr, MemAddress,I2C_MEMADD_SIZE, pData, Size, 0xFFFF);
//}

HAL_StatusTypeDef EEPROM_Write_Array(I2C_HandleTypeDef * hi2c,uint32_t MemAddress,uint8_t *pData, uint16_t Size)
{
		uint32_t i = 0;
	for(; i < Size; i++){
		if(HAL_I2C_Mem_Write(hi2c, I2C_EEPROM_OWN_ADDR, (MemAddress + i) ,I2C_MEMADD_SIZE_16BIT, &pData[i], 1, 0xFFFF) != HAL_OK){
		//	printf("x");
			return HAL_ERROR;
		//}else{
		//	printf("o");
		}
		HAL_Delay(8);
	}
	
	return HAL_OK;
}

HAL_StatusTypeDef EEPROM_Write_sub_Array(I2C_HandleTypeDef * hi2c,uint32_t MemAddress,uint8_t * pData, uint32_t start, uint16_t Size)
{
		uint32_t i = 0;
		for(; i < Size; i++){
			if(HAL_I2C_Mem_Write(hi2c, I2C_EEPROM_OWN_ADDR, (MemAddress + i) ,I2C_MEMADD_SIZE_16BIT, &pData[start + i], 1, 0xFFFF) != HAL_OK){
				return HAL_ERROR;
			}
			HAL_Delay(8);
		}
	
	return HAL_OK;
}



