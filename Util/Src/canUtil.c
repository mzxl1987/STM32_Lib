#include "canUtil.h"
#include "can.h"
#include "arrayUtil.h"


/** 标准 can id过滤的掩码模式  --------------------------- **/
void can_filter_config_Scale32_IdMask_StandardIdOnly(CAN_HandleTypeDef * hcan,uint16_t * std_id_array,uint32_t std_id_array_len)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  uint16_t      mask,tmp,i;
  
  sFilterConfig.FilterNumber = 2;				//使用过滤器2
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;		//配置为掩码模式
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;	//设置为32位宽
  sFilterConfig.FilterIdHigh =(std_id_array[0]<<5);		//验证码可以设置为StdIdArray[]数组中任意一个，这里使用StdIdArray[0]作为验证码
  sFilterConfig.FilterIdLow =0;
  
  mask =0x7ff;						//下面开始计算屏蔽码
  for(i =0; i<std_id_array_len; i++)		//屏蔽码位StdIdArray[]数组中所有成员的同或结果
  {
    tmp =std_id_array[i] ^ (~std_id_array[0]);	//所有数组成员与第0个成员进行同或操作
    mask &=tmp;
  }
  sFilterConfig.FilterMaskIdHigh =(mask<<5);
  sFilterConfig.FilterMaskIdLow =0|0x02; 		//只接收数据帧
  
  sFilterConfig.FilterFIFOAssignment = 0;		//设置通过的数据帧进入到FIFO0中
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;
  
  if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/** 拓展帧 can id过滤的掩码模式  --------------------------- **/
void can_filter_config_Scale32_IdMask_ExtendIdOnly(CAN_HandleTypeDef * hcan,uint32_t * ext_id_array,uint32_t ext_id_array_len)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  //定义一组扩展CAN ID用来测试
  uint32_t      mask,tmp,i;
  
  sFilterConfig.FilterNumber = 3;					//使用过滤器3
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;			//配置为掩码模式
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;		//设为32位宽
  sFilterConfig.FilterIdHigh =((ext_id_array[0]<<3) >>16) &0xffff;//数组任意一个成员都可以作为验证码
  sFilterConfig.FilterIdLow =((ext_id_array[0]<<3)&0xffff) | CAN_ID_EXT;
  
  mask =0x1fffffff;
  for(i =0; i<ext_id_array_len; i++)				//屏蔽码位数组各成员相互同或的结果
  {
    tmp =ext_id_array[i] ^ (~ext_id_array[0]);	//都与第一个数据成员进行同或操作
    mask &=tmp;
  }
  mask <<=3;    								//对齐寄存器
  sFilterConfig.FilterMaskIdHigh = (mask>>16)&0xffff;
  sFilterConfig.FilterMaskIdLow = (mask&0xffff)|0x02; 		//只接收数据帧
  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;
  
  if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}


/** 标准帧和拓展帧混合过滤  ------------------------------------------- **/
void can_filter_config_Scale32_IdMask_StandardId_ExtendId_Mix(CAN_HandleTypeDef * hcan,uint32_t * std_id_array,uint32_t std_id_array_len,uint32_t * ext_id_array,uint32_t ext_id_array_len)
{
  CAN_FilterConfTypeDef  sFilterConfig;
	
  uint32_t      mask,num,tmp,i,standard_mask,extend_mask,mix_mask;
  
  sFilterConfig.FilterNumber = 0;				//使用过滤器4
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;		//配置为掩码模式
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;	//设为32位宽
  sFilterConfig.FilterIdHigh =((ext_id_array[0]<<3) >>16) &0xffff;	//使用第一个扩展CAN  ID作为验证码
  sFilterConfig.FilterIdLow =((ext_id_array[0]<<3)&0xffff);
  
	//只接受指定 CAN ID	
  standard_mask =0x7ff;		//下面是计算屏蔽码
  for(i =0; i<std_id_array_len; i++)			//首先计算出所有标准CAN ID的屏蔽码
  {
    tmp =std_id_array[i] ^ (~std_id_array[0]);
    standard_mask &=tmp;
  }
  
  extend_mask =0x1fffffff;
  for(i =0; i<ext_id_array_len; i++)			//接着计算出所有扩展CAN ID的屏蔽码
  {
    tmp =ext_id_array[i] ^ (~ext_id_array[0]);
    extend_mask &=tmp;
  }
  mix_mask =(std_id_array[0]<<18)^ (~ext_id_array[0]);	//再计算标准CAN ID与扩展CAN ID混合的屏蔽码
  mask =(standard_mask<<18)& extend_mask &mix_mask;	//最后计算最终的屏蔽码
  mask <<=3;    						//对齐寄存器
 

  sFilterConfig.FilterMaskIdHigh = (mask>>16)&0xffff;
  sFilterConfig.FilterMaskIdLow = (mask&0xffff);

  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;
  
  if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/** 标准帧和拓展帧混合过滤  ------------------------------------------- **/
void can_filter_nothing_config(CAN_HandleTypeDef * hcan)
{
  CAN_FilterConfTypeDef  sFilterConfig;
	
  uint32_t      mask,num,tmp,i,standard_mask,extend_mask,mix_mask;
	uint32_t canid = 0x00000011;   //随机
  
  sFilterConfig.FilterNumber = 0;				//使用过滤器4
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;		//配置为掩码模式
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;	//设为32位宽
  sFilterConfig.FilterIdHigh =((canid<<3) >>16) &0xffff;	//使用第一个扩展CAN  ID作为验证码
  sFilterConfig.FilterIdLow =((canid<<3)&0xffff);
  
	//不做过滤
  sFilterConfig.FilterMaskIdHigh = 0x00;
  sFilterConfig.FilterMaskIdLow = 0x00;

  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;
  
  if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/** 判断canid是否存在当前数组中 ------------------------------------------- **/
uint8_t can_id_exist(uint32_t * dest,uint32_t dest_len,uint32_t id){

	uint32_t i = 0;
	for(; i < dest_len; i++){
		if(dest[i] == id) return 1;
	}
	
	return 0;

}

/** 判断canid是否相同 ------------------------------------------- **/
uint8_t can_copy(CanRxMsgTypeDef * src,uint32_t *len,uint32_t MAX,CanRxMsgTypeDef * dest){
	
	uint8_t exist = 0;
	uint32_t i = 0;
	
	for(; i < *len; i++){
		if(src[i].IDE == dest->IDE 
		&& ((dest->IDE == CAN_ID_STD && src[i].StdId == dest->StdId) || (dest->IDE == CAN_ID_EXT && src[i].ExtId == dest->ExtId))){  
			exist = 1;
			break;
		}
	}
	
	CanRxMsgTypeDef * tmp;
	if(i < MAX){
		tmp = &src[i];
		
		if(dest->IDE == CAN_ID_STD){
			tmp->StdId = dest->StdId;
		}else if(dest->IDE == CAN_ID_EXT){
			tmp->ExtId = dest->ExtId;
		}
		
		tmp->DLC = dest->DLC;
		tmp->IDE = dest->IDE;
		tmp->RTR = dest->RTR;
		
		Array_copy(tmp->Data,0,dest->Data,0,8);
		
	}
	
	if(!exist){
		*len = i+1;
	}
	
	return 0;

}

/** 判断canid是否存在当前数组中 ------------------------------------------- **/
uint8_t can_id_add(uint32_t * dest,uint32_t dest_len,uint32_t id){
	
	if(!can_id_exist(dest,dest_len,id)){
		dest[dest_len] = id;
		return 1;
	}
	
	return 0;

}

/** 判断canid是否存在当前数组中 ------------------------------------------- **/
uint8_t can_id_delete(uint32_t * dest,uint32_t dest_len,uint32_t id){
	
	if(can_id_exist(dest,dest_len,id)){
		uint32_t i = 0;
		for(; i < dest_len; i++){
			if(dest[i] == id) {
				for(; i < dest_len - 1; i++){
					dest[i] = dest[i+1];
				}
				break;
			}
		}
		return 1;
	}
	return 0;
}

/***
* convert canframe to bytes
* CANID + CANDATA
* 返回CAN数据长度
*/
uint32_t convert_canframe_to_bytes(uint8_t * dest, uint32_t dest_start ,CanRxMsgTypeDef * frame){
  
	//printf(" convert_canframe_to_bytes CAN STDID:%08X,EXTID:%08X,DATA:%08X",frame->StdId,frame->ExtId,frame->Data);
	
  //CAN ID
	if(frame->IDE == CAN_ID_STD){
		dest[dest_start++] = (frame->StdId & 0xFF000000) >> 24;
		dest[dest_start++] = (frame->StdId & 0xFF0000) >> 16;
		dest[dest_start++] = (frame->StdId & 0xFF00) >> 8;
		dest[dest_start++] = (frame->StdId & 0xFF);

	}else if(frame->IDE == CAN_ID_EXT){
		dest[dest_start++] = (frame->ExtId & 0xFF000000) >> 24;
		dest[dest_start++] = (frame->ExtId & 0xFF0000) >> 16;
		dest[dest_start++] = (frame->ExtId & 0xFF00) >> 8;
		dest[dest_start++] = (frame->ExtId & 0xFF);
		
	}
	
	//CAN Data
	Array_copy(dest,dest_start,frame->Data,0,8);
  
  return 12;
}




