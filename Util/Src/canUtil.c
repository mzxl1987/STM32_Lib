#include "canUtil.h"
#include "can.h"
#include "arrayUtil.h"


/** ��׼ can id���˵�����ģʽ  --------------------------- **/
void can_filter_config_Scale32_IdMask_StandardIdOnly(CAN_HandleTypeDef * hcan,uint16_t * std_id_array,uint32_t std_id_array_len)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  uint16_t      mask,tmp,i;
  
  sFilterConfig.FilterNumber = 2;				//ʹ�ù�����2
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;		//����Ϊ����ģʽ
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;	//����Ϊ32λ��
  sFilterConfig.FilterIdHigh =(std_id_array[0]<<5);		//��֤���������ΪStdIdArray[]����������һ��������ʹ��StdIdArray[0]��Ϊ��֤��
  sFilterConfig.FilterIdLow =0;
  
  mask =0x7ff;						//���濪ʼ����������
  for(i =0; i<std_id_array_len; i++)		//������λStdIdArray[]���������г�Ա��ͬ����
  {
    tmp =std_id_array[i] ^ (~std_id_array[0]);	//���������Ա���0����Ա����ͬ�����
    mask &=tmp;
  }
  sFilterConfig.FilterMaskIdHigh =(mask<<5);
  sFilterConfig.FilterMaskIdLow =0|0x02; 		//ֻ��������֡
  
  sFilterConfig.FilterFIFOAssignment = 0;		//����ͨ��������֡���뵽FIFO0��
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;
  
  if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/** ��չ֡ can id���˵�����ģʽ  --------------------------- **/
void can_filter_config_Scale32_IdMask_ExtendIdOnly(CAN_HandleTypeDef * hcan,uint32_t * ext_id_array,uint32_t ext_id_array_len)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  //����һ����չCAN ID��������
  uint32_t      mask,tmp,i;
  
  sFilterConfig.FilterNumber = 3;					//ʹ�ù�����3
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;			//����Ϊ����ģʽ
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;		//��Ϊ32λ��
  sFilterConfig.FilterIdHigh =((ext_id_array[0]<<3) >>16) &0xffff;//��������һ����Ա��������Ϊ��֤��
  sFilterConfig.FilterIdLow =((ext_id_array[0]<<3)&0xffff) | CAN_ID_EXT;
  
  mask =0x1fffffff;
  for(i =0; i<ext_id_array_len; i++)				//������λ�������Ա�໥ͬ��Ľ��
  {
    tmp =ext_id_array[i] ^ (~ext_id_array[0]);	//�����һ�����ݳ�Ա����ͬ�����
    mask &=tmp;
  }
  mask <<=3;    								//����Ĵ���
  sFilterConfig.FilterMaskIdHigh = (mask>>16)&0xffff;
  sFilterConfig.FilterMaskIdLow = (mask&0xffff)|0x02; 		//ֻ��������֡
  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;
  
  if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}


/** ��׼֡����չ֡��Ϲ���  ------------------------------------------- **/
void can_filter_config_Scale32_IdMask_StandardId_ExtendId_Mix(CAN_HandleTypeDef * hcan,uint32_t * std_id_array,uint32_t std_id_array_len,uint32_t * ext_id_array,uint32_t ext_id_array_len)
{
  CAN_FilterConfTypeDef  sFilterConfig;
	
  uint32_t      mask,num,tmp,i,standard_mask,extend_mask,mix_mask;
  
  sFilterConfig.FilterNumber = 0;				//ʹ�ù�����4
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;		//����Ϊ����ģʽ
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;	//��Ϊ32λ��
  sFilterConfig.FilterIdHigh =((ext_id_array[0]<<3) >>16) &0xffff;	//ʹ�õ�һ����չCAN  ID��Ϊ��֤��
  sFilterConfig.FilterIdLow =((ext_id_array[0]<<3)&0xffff);
  
	//ֻ����ָ�� CAN ID	
  standard_mask =0x7ff;		//�����Ǽ���������
  for(i =0; i<std_id_array_len; i++)			//���ȼ�������б�׼CAN ID��������
  {
    tmp =std_id_array[i] ^ (~std_id_array[0]);
    standard_mask &=tmp;
  }
  
  extend_mask =0x1fffffff;
  for(i =0; i<ext_id_array_len; i++)			//���ż����������չCAN ID��������
  {
    tmp =ext_id_array[i] ^ (~ext_id_array[0]);
    extend_mask &=tmp;
  }
  mix_mask =(std_id_array[0]<<18)^ (~ext_id_array[0]);	//�ټ����׼CAN ID����չCAN ID��ϵ�������
  mask =(standard_mask<<18)& extend_mask &mix_mask;	//���������յ�������
  mask <<=3;    						//����Ĵ���
 

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

/** ��׼֡����չ֡��Ϲ���  ------------------------------------------- **/
void can_filter_nothing_config(CAN_HandleTypeDef * hcan)
{
  CAN_FilterConfTypeDef  sFilterConfig;
	
  uint32_t      mask,num,tmp,i,standard_mask,extend_mask,mix_mask;
	uint32_t canid = 0x00000011;   //���
  
  sFilterConfig.FilterNumber = 0;				//ʹ�ù�����4
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;		//����Ϊ����ģʽ
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;	//��Ϊ32λ��
  sFilterConfig.FilterIdHigh =((canid<<3) >>16) &0xffff;	//ʹ�õ�һ����չCAN  ID��Ϊ��֤��
  sFilterConfig.FilterIdLow =((canid<<3)&0xffff);
  
	//��������
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

/** �ж�canid�Ƿ���ڵ�ǰ������ ------------------------------------------- **/
uint8_t can_id_exist(uint32_t * dest,uint32_t dest_len,uint32_t id){

	uint32_t i = 0;
	for(; i < dest_len; i++){
		if(dest[i] == id) return 1;
	}
	
	return 0;

}

/** �ж�canid�Ƿ���ͬ ------------------------------------------- **/
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

/** �ж�canid�Ƿ���ڵ�ǰ������ ------------------------------------------- **/
uint8_t can_id_add(uint32_t * dest,uint32_t dest_len,uint32_t id){
	
	if(!can_id_exist(dest,dest_len,id)){
		dest[dest_len] = id;
		return 1;
	}
	
	return 0;

}

/** �ж�canid�Ƿ���ڵ�ǰ������ ------------------------------------------- **/
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
* ����CAN���ݳ���
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




