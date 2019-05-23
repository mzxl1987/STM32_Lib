#ifndef __eepromUtil_H__
#define __eepromUtil_H__

#include "stm32f1xx_hal.h"


/** EEPROM  ----------------------------------------------------------------------**/
/* AT24C01/02ÿҳ��8���ֽ� */  
#define EE_PAGE_SIZE           8  
	/*      
	
	AT24C256  memAdd size  =  I2C_MEMADD_SIZE_16BIT
	
	*/
	
/* AT24C04/08A/16Aÿҳ��16���ֽ� */  
//#define I2C_PageSize           16  
/* �����ַֻҪ��STM32��ҵ�I2C������ַ��һ������ */  

#define I2C_EEPROM_OWN_ADDR                0xA0
#define RUNNIN_AREA                        0x01  //0:��Bootloader����,1:��ʾ����FLASH_ADDR_APP_1,2:��ʾ����FLASH_ADDR_APP_2,����:������������FLASH_ADDR_APP_BASE
#define EERROM_RUN_AERA_ADDR         0x00
#define EERROM_RUN_AERA_SIZE              0x01    //��ǰ��������־��EEPROM����ռ�ռ��С
#define FLAG_NEED_UPDATE                   0x80  //RUNNIN_AREA���λΪ1��ʾ��Ҫ����

#define EERROM_REBOOT_TIMES_ADDR         0x01   //APP��������
#define EERROM_REBOOT_TIMES_SIZE         0x04   //�豸��������,1bytes����

   
extern uint32_t EEPROM_ADDRESS; 


HAL_StatusTypeDef                 EEPROM_Read(I2C_HandleTypeDef * hi2c,uint8_t deviceAddr,uint16_t MemAddress,uint32_t I2C_MEMADD_SIZE, uint8_t *pData, uint16_t Size);

/**************************************************
** EEPROM ������
** 1.i2c��������
** 2.�豸��ַ
** 3.EEPROM�ڴ��ַ
** 4.EEPROM�ڴ��ַ��С,���ݲ�ͬ��EEPROM���֡�һ��Ϊ8BIT,16BIT  2��
** 5.��������ݵ�ָ��
** 6.���ݴ�С
***************************************************/
HAL_StatusTypeDef                   EEPROM_Read_To_Array(I2C_HandleTypeDef * hi2c,uint32_t MemAddress,uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef                   EEPROM_Write_Array(I2C_HandleTypeDef * hi2c,uint32_t MemAddress,uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef                   EEPROM_Write_sub_Array(I2C_HandleTypeDef * hi2c,uint32_t MemAddress,uint8_t * pData, uint32_t start, uint16_t Size);



#endif
