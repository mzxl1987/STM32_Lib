#ifndef __canUtil_H__
#define __canUtil_H__

#include "stm32f1xx_hal.h"
#include "config.h"

/** ��׼ can id���˵�����ģʽ  --------------------------- **/
void can_filter_config_Scale32_IdMask_StandardIdOnly(CAN_HandleTypeDef * hcan,uint16_t * std_id_array,uint32_t std_id_array_len);

/** ��չ֡ can id���˵�����ģʽ  --------------------------- **/
void can_filter_config_Scale32_IdMask_ExtendIdOnly(CAN_HandleTypeDef * hcan,uint32_t * ext_id_array,uint32_t ext_id_array_len);

/** ��׼֡����չ֡��Ϲ���  ------------------------------------------- **/
void can_filter_config_Scale32_IdMask_StandardId_ExtendId_Mix(CAN_HandleTypeDef * hcan,uint32_t * std_id_array,uint32_t std_id_array_len,uint32_t * ext_id_array,uint32_t ext_id_array_len);

/** �ж�canid�Ƿ���ڵ�ǰ������ ------------------------------------------- **/
uint8_t can_id_exist(uint32_t * dest,uint32_t dest_len,uint32_t id);

/** �ж�canid�Ƿ���ڵ�ǰ������ ------------------------------------------- **/
uint8_t can_id_delete(uint32_t * dest,uint32_t dest_len,uint32_t id);


/** �ж�canid�Ƿ���ͬ ------------------------------------------- **/
uint8_t can_copy(CanRxMsgTypeDef * src,uint32_t * len,uint32_t MAX,CanRxMsgTypeDef * dest);

/***
* convert canframe to bytes
* CANID + CANDATA
* ����CAN���ݳ���
*/
uint32_t convert_canframe_to_bytes(uint8_t * dest, uint32_t dest_start ,CanRxMsgTypeDef * frame);

void can_filter_nothing_config(CAN_HandleTypeDef * hcan);


#endif

