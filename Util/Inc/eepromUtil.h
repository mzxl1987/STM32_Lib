#ifndef __eepromUtil_H__
#define __eepromUtil_H__

#include "stm32f1xx_hal.h"


/** EEPROM  ----------------------------------------------------------------------**/
/* AT24C01/02每页有8个字节 */  
#define EE_PAGE_SIZE           8  
	/*      
	
	AT24C256  memAdd size  =  I2C_MEMADD_SIZE_16BIT
	
	*/
	
/* AT24C04/08A/16A每页有16个字节 */  
//#define I2C_PageSize           16  
/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */  

#define I2C_EEPROM_OWN_ADDR                0xA0
#define RUNNIN_AREA                        0x01  //0:从Bootloader启动,1:表示运行FLASH_ADDR_APP_1,2:表示运行FLASH_ADDR_APP_2,其他:基本升级程序FLASH_ADDR_APP_BASE
#define EERROM_RUN_AERA_ADDR         0x00
#define EERROM_RUN_AERA_SIZE              0x01    //当前运行区标志在EEPROM中所占空间大小
#define FLAG_NEED_UPDATE                   0x80  //RUNNIN_AREA最高位为1表示需要升级

#define EERROM_REBOOT_TIMES_ADDR         0x01   //APP重启次数
#define EERROM_REBOOT_TIMES_SIZE         0x04   //设备重启次数,1bytes保持

   
extern uint32_t EEPROM_ADDRESS; 


HAL_StatusTypeDef                 EEPROM_Read(I2C_HandleTypeDef * hi2c,uint8_t deviceAddr,uint16_t MemAddress,uint32_t I2C_MEMADD_SIZE, uint8_t *pData, uint16_t Size);

/**************************************************
** EEPROM 读操作
** 1.i2c对象引用
** 2.设备地址
** 3.EEPROM内存地址
** 4.EEPROM内存地址大小,根据不同的EEPROM区分。一般为8BIT,16BIT  2种
** 5.待存放数据的指针
** 6.数据大小
***************************************************/
HAL_StatusTypeDef                   EEPROM_Read_To_Array(I2C_HandleTypeDef * hi2c,uint32_t MemAddress,uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef                   EEPROM_Write_Array(I2C_HandleTypeDef * hi2c,uint32_t MemAddress,uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef                   EEPROM_Write_sub_Array(I2C_HandleTypeDef * hi2c,uint32_t MemAddress,uint8_t * pData, uint32_t start, uint16_t Size);



#endif
