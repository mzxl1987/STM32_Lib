#include "ATUtil.h"

#include "all.h"

ATFrame atFrame;
ATFrame atFrame_uart1;

/** ����ATָ������ **/
void ATFrame_copy(UartBuffer * src, uint16_t from, uint16_t length){
	
	uart_buffer_copy(src,from,atFrame.data,0,length);
	atFrame.length = length;
	
	println("**-------------  LTE M8321 �������� ASCII------------------------**");
	array_print_str(atFrame.data,0,atFrame.length);
	println("**---------------------------------------------------------------**");
	
	ATFrame_analysis();  //���ݽ���
	

}

/** ����ATָ������ UART1 **/
void ATFrame_copy_uart1(UartBuffer * src, ATFrame * atFrame_uart1,uint16_t from, uint16_t length){
		
	uart_buffer_copy(src,from,atFrame_uart1->data,atFrame_uart1->length,length);
	atFrame_uart1->length = length;
	
	ATFrame_clear(atFrame_uart1);
}

/** ����֡��� **/
void ATFrame_clear(ATFrame * atFrame){
	atFrame->length = 0;
}



/** ����ģʽ �ֶ��������� **/
void ATFrame_analysis(){
	
	
	
	
	ATFrame_clear(&atFrame);	  
	
}
































/** ���ҷ��� head ..... tail  ������ ����������ʼ�±�ͳ��� **/
uint8_t ATFrame_find(uint8_t * head,uint32_t head_len,uint8_t * tail,uint32_t tail_len,uint32_t * dest_index,uint32_t * dest_len){

	uint32_t read_index = 0;

	while(read_index < atFrame.length){
		
		if(array_equal(atFrame.data,read_index, head,0, head_len)){
		
			/** ���head�±�  ------------- **/
			*dest_index = read_index;
			
			uint32_t i = 0;
			
			read_index += head_len;
			while(read_index < atFrame.length){
				
				if(array_equal(atFrame.data,read_index, tail,0, tail_len)){
				
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

uint8_t ATFrame_equal(uint8_t * src,uint32_t len){

	uint32_t read_index = 0;

	while(read_index < atFrame.length){
		
		if(array_equal(atFrame.data,read_index, src,0, len)){		
			return 1;
		}
		
		read_index ++;
		
	}
	
	return 0;

}

uint8_t ATFrame_equalFromIndex(uint16_t readIndex,uint8_t * src,uint32_t len){
		return array_equal(atFrame.data,readIndex, src,0, len);
}



uint8_t ATFrame_uart1_analysis(ATFrame * atFrame){

	
	
	return 0;	
}





















