#include "UartUtil.h"

#include "all.h"


/** 数据帧清除 **/
void UartFrame_clear(UartFrame * f){
	f->length = 0;
}


static void UartFrame_analysis_usart1(UartFrame * f){
	
	print_msg("串口1 数据解析  TODO");
	//TODO
	
}

static void UartFrame_analysis_usart2(UartFrame * f){
	
	print_msg("串口2 数据解析  TODO");
	//TODO
	
}

static void UartFrame_analysis_usart3(UartFrame * f){
	
	print_msg("串口3 数据解析  TODO");
	//TODO
	
}

static void UartFrame_analysis_usart4(UartFrame * f){
	
	print_msg("串口4 数据解析  TODO");
	//TODO
	
}

static void UartFrame_analysis_usart5(UartFrame * f){
	
	print_msg("串口5 数据解析  TODO");
	//TODO
	
}


/** 串口数据解析 **/
void UartFrame_analysis(UartFrame * f){
	
	println("**---------------------------------------------------------------**");
	Array_print_str(f->data,0,f->length);
	println("**---------------------------------------------------------------**");
	
	if(f->uart->Instance == USART1){
			print_msg("串口1 数据 ASCII");
			UartFrame_analysis_usart1(f);
	}
	
	if(f->uart->Instance == USART2){
			print_msg("串口2 数据 ASCII");
			UartFrame_analysis_usart2(f);
	}
	
	UartFrame_clear(f);	  
	
}


/** 查找符合 head ..... tail  的数据 ，并返回起始下标和长度 **/
uint8_t UartFrame_find(UartFrame * u, uint8_t * head,uint32_t head_len,uint8_t * tail,uint32_t tail_len,uint32_t * dest_index,uint32_t * dest_len){

	uint32_t read_index = 0;

	while(read_index < u->length){
		
		if(Array_equal(u->data,read_index, head,0, head_len)){
		
			/** 标记head下标  ------------- **/
			*dest_index = read_index;
			
			uint32_t i = 0;
			
			read_index += head_len;
			while(read_index < u->length){
				
				if(Array_equal(u->data,read_index, tail,0, tail_len)){
				
					/** 计算匹配数据长度 [包含头/尾] -----------------**/
					*dest_len = i + tail_len + head_len;
					return 1;
				}
				read_index++;							
				i++;
				
			}
			
			break;
		}
		
		
		read_index ++;
		
	}
	
	return 0;

}

uint8_t UartFrame_equal(UartFrame * f, uint8_t * src,uint32_t len){

	uint32_t read_index = 0;

	while(read_index < f->length){
		
		if(Array_equal(f->data,read_index, src,0, len)){		
			return 1;
		}
		
		read_index ++;
		
	}
	
	return 0;

}

uint8_t UartFrame_equalFromIndex(UartFrame * f,uint16_t readIndex,uint8_t * src,uint32_t len){
		return Array_equal(f->data,readIndex, src,0, len);
}
















