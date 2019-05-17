#include "uartBuffer.h"

#include "printUtil.h"


/** 数据和循环数组比较是否相等  ------------------------------------- **/
static uint8_t loop_buffer_equal(uint8_t * dest,uint32_t dest_start,uint8_t * src,uint32_t src_start,uint32_t len,uint32_t dest_len){

	uint32_t index,i = 0;
	
	for(; i < len;i++){
		index = (dest_start + i) % dest_len;
		if(dest[index] != src[src_start + i]){ 
			return 0;
		}
	}
	return 1;
}

/** 循环数组设置指定值  --------------------------------------------- **/
static uint8_t loop_buffer_set(uint8_t * dest,uint32_t dest_start,uint32_t len,uint8_t xx,uint32_t dest_len){

	uint32_t index,i = 0;
	
	for(; i < len;i++){
		index = (dest_start + i) % dest_len;
		dest[index] = xx;
	}
	return 1;
}

/** 循环数组拷贝  ------------------------------------------------- **/
void loop_buffer_copy(uint8_t * src,uint32_t src_start,uint8_t * dest,uint32_t dest_start,uint32_t len,uint32_t src_len){
	uint32_t i = 0,index;
	 for(; i < len; i++){
			index = (src_start + i) % src_len;
			dest[dest_start + i] = src[index];
	 }
}

/** 打印数据  ------------------------------------------------- **/
void uart_buffer_print_hex(UartBuffer * src,uint32_t start,uint32_t len){
   #if DEBUG
	 uint32_t i = 0,index;
	 print_msg((uint8_t *)"打印 UartBuffer 数据");
	 for(; i < len; i++){
			index = (start + i) % src->MAX_LENGTH;
			printf("%02X ",src->data[index]);
	 }
	 println((uint8_t *)" ");
	 #endif
}

/** 打印数据  ------------------------------------------------- **/
void uart_buffer_print_str(UartBuffer * src,uint32_t start,uint32_t len){
   
	 uint32_t i = 0,index;
	
	 print_msg((uint8_t *)"打印 UartBuffer 数据");
	 for(; i < len; i++){
			index = (start + i) % src->MAX_LENGTH;
			printf("%c",src->data[index]);
	 }
	 println((uint8_t *)" ");
	 
}

uint8_t uart_buffer_equal(UartBuffer * src,uint32_t src_start,uint8_t * dest,uint32_t dest_start,uint32_t len){
	return loop_buffer_equal(src->data,src_start,dest,dest_start,len,src->MAX_LENGTH);
}

uint8_t uart_buffer_equalAt(UartBuffer * src,uint8_t * dest,uint32_t dest_start,uint32_t len,uint32_t * dest_index,uint32_t * dest_len){
  uint32_t index = src->index;
	uint8_t loop = 1;
	while(loop){
	
		if(loop_buffer_equal(src->data,src->index,dest,dest_start,len,src->MAX_LENGTH)){
			*dest_index = src->index;
			*dest_len = len;
			return 1;
		}
	
		uart_buffer_next(src,1);
		loop = (index != src->index);
	}
	return 0;
}

uint8_t uart_buffer_set(UartBuffer * src,uint32_t start,uint32_t len,uint8_t xx){

	len = len > src->MAX_LENGTH ? src->MAX_LENGTH : len ;

	return loop_buffer_set(src->data,start,len,xx,src->MAX_LENGTH);
}

void uart_buffer_copy(UartBuffer * src,uint32_t src_start,uint8_t * dest,uint32_t dest_start,uint32_t len){

  len = len > src->MAX_LENGTH ? src->MAX_LENGTH : len ;

	loop_buffer_copy(src->data,src_start,dest,dest_start,len,src->MAX_LENGTH);
}

uint8_t uart_buffer_find(UartBuffer * src,uint8_t * head,uint32_t head_len,uint8_t * tail,uint32_t tail_len,uint32_t * dest_index,uint32_t * dest_len){

	uint32_t read_index = src->index;
	
	uint8_t loop = 1;
	

	while(loop){
		
		if(uart_buffer_equal(src,src->index, head,0, head_len)){
		
			/** 标记head下标  ------------- **/
			*dest_index = src->index;
			
			uint32_t i = 0;
			
			uart_buffer_next(src,head_len);
			read_index = src->index;
			while(loop){
				
				if(uart_buffer_equal(src,src->index, tail,0, tail_len)){
				
					/** 计算匹配数据长度 [包含头/尾] -----------------**/
					*dest_len = i + tail_len + head_len;
					return 1;
				}
				
				
				uart_buffer_next(src,1);
				loop = (read_index != src->index);
				i++;
				
			}
			
			break;
		}
		
		uart_buffer_next(src,1);
		loop = (read_index != src->index);
		
	}
	
	return 0;

}

void uart_buffer_jump(UartBuffer * src,uint32_t jump_to_index){
	src->index = jump_to_index % src->MAX_LENGTH;
}

void uart_buffer_next(UartBuffer * src,uint32_t move_len){
	src->index = (src->index + move_len) % src->MAX_LENGTH;
}

void uart_buffer_pre(UartBuffer * src,uint32_t move_len){
	src->index = (src->index + (src->MAX_LENGTH - move_len)) % src->MAX_LENGTH;
}















