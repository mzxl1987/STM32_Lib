#ifndef __canUtil_H__
#define __canUtil_H__

#include "stm32f1xx_hal.h"
#include "config.h"

/** 标准 can id过滤的掩码模式  --------------------------- **/
void can_filter_config_Scale32_IdMask_StandardIdOnly(CAN_HandleTypeDef * hcan,uint16_t * std_id_array,uint32_t std_id_array_len);

/** 拓展帧 can id过滤的掩码模式  --------------------------- **/
void can_filter_config_Scale32_IdMask_ExtendIdOnly(CAN_HandleTypeDef * hcan,uint32_t * ext_id_array,uint32_t ext_id_array_len);

/** 标准帧和拓展帧混合过滤  ------------------------------------------- **/
void can_filter_config_Scale32_IdMask_StandardId_ExtendId_Mix(CAN_HandleTypeDef * hcan,uint32_t * std_id_array,uint32_t std_id_array_len,uint32_t * ext_id_array,uint32_t ext_id_array_len);

/** 判断canid是否存在当前数组中 ------------------------------------------- **/
uint8_t can_id_exist(uint32_t * dest,uint32_t dest_len,uint32_t id);

/** 判断canid是否存在当前数组中 ------------------------------------------- **/
uint8_t can_id_delete(uint32_t * dest,uint32_t dest_len,uint32_t id);


/** 判断canid是否相同 ------------------------------------------- **/
uint8_t can_copy(CanRxMsgTypeDef * src,uint32_t * len,uint32_t MAX,CanRxMsgTypeDef * dest);

/***
* convert canframe to bytes
* CANID + CANDATA
* 返回CAN数据长度
*/
uint32_t convert_canframe_to_bytes(uint8_t * dest, uint32_t dest_start ,CanRxMsgTypeDef * frame);

void can_filter_nothing_config(CAN_HandleTypeDef * hcan);


#endif

