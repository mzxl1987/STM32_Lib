#ifndef __config_H
#define __config_H

#include "stdlib.h"
#include "stm32f1xx_hal.h"

#undef null
#if defined(__cplusplus)
#define null 0
#else
#define null ((void *)0)
#endif

/** 类型定义  ---------------------------------------- **/

typedef char byte;
typedef unsigned char ubyte;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef struct 
{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;	
	
	uint16_t w_year;
	uint8_t  w_month;
	uint8_t  w_date;
	uint8_t  week;	
}_calendar_obj;	


/** 版本信息 --------------------------------------------------------------------------  **/
#define DEBUG 1    //0:表示发型版,不打印调试信息,1:表示调试，答应调试信息

#define COPYRIGHT "Miicrown @ Copyright"


/** Flash地址分配----------------------------------------------------------------------  **/

#define FLASH_ADDR_BOOTLOADER  0x08000000     //bootloader起始地址
#define FLASH_ADDR_APP_STORAGE 0x0800F800     //[升级程序存储区]起始地址
#define FLASH_ADDR_APP         0x08035000     //APP1 起始地址
#define FLASH_ADDR_APP_BAK     0x0805A800     //基本版只负责程序升级
#define FLASH_APP_SIZE         0x00025800     //APP所占Flash存储区大小



#define FLASH_SIZE 512          //所选MCU的FLASH容量大小(单位为K)

#if FLASH_SIZE < 256
  #define PAGE_SIZE           1024    //字节
#else 
  #define PAGE_SIZE           2048    //字节
#endif

/** 串口数据缓冲区 -----------------------------------------------------------  **/

/**  Lora串口  ---------------------------------------------------------- **/


/**  NB-IOT串口 ----------------------------------------------------------**/



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

   
extern uint EEPROM_ADDRESS; 


/** ADC数据  ---------------------------------------------------------------------  **/

#define ADC_SIZE 2
/**  
a[0]  =  电流
a[1]  =  电压
  **/
extern uint32_t adc_DATA[];

/**  程序升级  -------------------------------------------------------------------- **/

#define MINUTE_TICK                      0xEA60      //1分钟的毫秒数
#define TENMINUTE_TICK                   (MINUTE_TICK * 10)      //10分钟的毫秒数

#define SECOND_TICK                      1000      //一分钟的毫秒数
#define TENSECOND_TICK                   (10 *  SECOND_TICK)     //10S的毫秒数
#define THIRTYSECOND_TICK                   (30 *  SECOND_TICK)     //30S的毫秒数

#define HOUR_TICK                        (MINUTE_TICK * 60)      //一小时的毫秒数
#define DAY_TICK                        (HOUR_TICK * 24)      //一天的毫秒数
#define MINUTES_BY_DAY                  1440            //一天的分钟数

#define MAX_REBOOT_TIMES                 0x0064      //APP最大的重启次数，超过则跳转到升级备选区域

extern uint32_t ApplicationAddress;   //程序起始地址

extern uint32_t runningArea;          //当前程序运行区,第8位表示是否需要升级,第1-7位表示运行区

typedef void(*pFunction)(void);


#define FRAME_STARTWITH "+rev:"













#endif
