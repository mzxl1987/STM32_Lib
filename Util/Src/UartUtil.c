#include "UartUtil.h"

#include "all.h"


/** ����֡��� **/
void UartFrame_clear(UartFrame * f){
	f->length = 0;
}


static void UartFrame_analysis_usart1(UartFrame * f){
	
	print_msg("����1 ���ݽ���  TODO");
	//TODO
	
}

static void UartFrame_analysis_usart2(UartFrame * f){
	
	print_msg("����2 ���ݽ���  TODO");
	//TODO
	
}

static void UartFrame_analysis_usart3(UartFrame * f){
	
	print_msg("����3 ���ݽ���  TODO");
	//TODO
	
}

static void UartFrame_analysis_usart4(UartFrame * f){
	
	print_msg("����4 ���ݽ���  TODO");
	//TODO
	
}

static void UartFrame_analysis_usart5(UartFrame * f){
	
	print_msg("����5 ���ݽ���  TODO");
	//TODO
	
}


/** �������ݽ��� **/
void UartFrame_analysis(UartFrame * f){
	
	println("**---------------------------------------------------------------**");
	Array_print_str(f->data,0,f->length);
	println("**---------------------------------------------------------------**");
	
	if(f->uart->Instance == USART1){
			print_msg("����1 ���� ASCII");
			UartFrame_analysis_usart1(f);
	}
	
	if(f->uart->Instance == USART2){
			print_msg("����2 ���� ASCII");
			UartFrame_analysis_usart2(f);
	}
	
	UartFrame_clear(f);	  
	
}


/** ���ҷ��� head ..... tail  ������ ����������ʼ�±�ͳ��� **/
uint8_t UartFrame_find(UartFrame * u, uint8_t * head,uint32_t head_len,uint8_t * tail,uint32_t tail_len,uint32_t * dest_index,uint32_t * dest_len){

	uint32_t read_index = 0;

	while(read_index < u->length){
		
		if(Array_equal(u->data,read_index, head,0, head_len)){
		
			/** ���head�±�  ------------- **/
			*dest_index = read_index;
			
			uint32_t i = 0;
			
			read_index += head_len;
			while(read_index < u->length){
				
				if(Array_equal(u->data,read_index, tail,0, tail_len)){
				
					/** ����ƥ�����ݳ��� [����ͷ/β] -----------------**/
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
















