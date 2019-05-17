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

/** ���Ͷ���  ---------------------------------------- **/

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


/** �汾��Ϣ --------------------------------------------------------------------------  **/
#define DEBUG 1    //0:��ʾ���Ͱ�,����ӡ������Ϣ,1:��ʾ���ԣ���Ӧ������Ϣ

#define COPYRIGHT "Miicrown @ Copyright"


/** Flash��ַ����----------------------------------------------------------------------  **/

#define FLASH_ADDR_BOOTLOADER  0x08000000     //bootloader��ʼ��ַ
#define FLASH_ADDR_APP_STORAGE 0x0800F800     //[��������洢��]��ʼ��ַ
#define FLASH_ADDR_APP         0x08035000     //APP1 ��ʼ��ַ
#define FLASH_ADDR_APP_BAK     0x0805A800     //������ֻ�����������
#define FLASH_APP_SIZE         0x00025800     //APP��ռFlash�洢����С



#define FLASH_SIZE 512          //��ѡMCU��FLASH������С(��λΪK)

#if FLASH_SIZE < 256
  #define PAGE_SIZE           1024    //�ֽ�
#else 
  #define PAGE_SIZE           2048    //�ֽ�
#endif

/** �������ݻ����� -----------------------------------------------------------  **/

/**  Lora����  ---------------------------------------------------------- **/


/**  NB-IOT���� ----------------------------------------------------------**/



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

   
extern uint EEPROM_ADDRESS; 


/** ADC����  ---------------------------------------------------------------------  **/

#define ADC_SIZE 2
/**  
a[0]  =  ����
a[1]  =  ��ѹ
  **/
extern uint32_t adc_DATA[];

/**  ��������  -------------------------------------------------------------------- **/

#define MINUTE_TICK                      0xEA60      //1���ӵĺ�����
#define TENMINUTE_TICK                   (MINUTE_TICK * 10)      //10���ӵĺ�����

#define SECOND_TICK                      1000      //һ���ӵĺ�����
#define TENSECOND_TICK                   (10 *  SECOND_TICK)     //10S�ĺ�����
#define THIRTYSECOND_TICK                   (30 *  SECOND_TICK)     //30S�ĺ�����

#define HOUR_TICK                        (MINUTE_TICK * 60)      //һСʱ�ĺ�����
#define DAY_TICK                        (HOUR_TICK * 24)      //һ��ĺ�����
#define MINUTES_BY_DAY                  1440            //һ��ķ�����

#define MAX_REBOOT_TIMES                 0x0064      //APP����������������������ת��������ѡ����

extern uint32_t ApplicationAddress;   //������ʼ��ַ

extern uint32_t runningArea;          //��ǰ����������,��8λ��ʾ�Ƿ���Ҫ����,��1-7λ��ʾ������

typedef void(*pFunction)(void);


#define FRAME_STARTWITH "+rev:"













#endif
