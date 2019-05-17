#include "arrayUtil.h"


/**
 * uint8_t[] to uint32_t
 */
uint32_t convert_to_uint32(uint8_t *data,uint32_t start){
  uint32_t result = 0;
	uint32_t i = 0;
   for(; i < 4;i++){
    result = (result << 8) + data[start + i];
  }
  return result;
}

/** uint8_t[] 装换成 uint32_t ,小端模式, uint8_t[]中低字节在前 **/
uint32_t convert_to_uint32_low_mode(uint8_t *data,uint32_t start){
  uint32_t result = 0;
	uint32_t i = 0;
   for(; i < 4;i++){
    result |=  (data[start + i] << (8 * i));
  }
  return result;
}

/** uint8_t[] 装换成 uint16_t ,小端模式, uint8_t[]中低字节在前 **/
uint16_t convert_to_uint16_low_mode(uint8_t *data,uint32_t start){
  uint16_t result = 0;
	uint16_t i = 0;
   for(; i < 2;i++){
    result |=  (data[start + i] << (8 * i));
  }
  return result;
}

/** uint32_t to uint8_t[] 小端模式 **/
void convert_uint32_to_uint8_array_low_mode(uint32_t source,uint8_t * dest,uint32_t dest_start){
	dest[dest_start + 0] = source & 0xFF;
	dest[dest_start + 1] = (source >> 8) & 0xFF;
	dest[dest_start + 2] = (source >> 16) & 0xFF;
	dest[dest_start + 3] = source >> 24;
}


/************************************************/
/** BCD字符转换成Dec **/
/************************************************/
uint8_t bcdCharToDec(uint8_t c){
  return c - '0';
}

uint8_t numberToChar(uint32_t number){
  uint8_t result[] = "0123456789ABCDEF";
  return result[number];
}

/**
 * 获取指定次数字符的位置
 */
uint32_t array_char_index(uint8_t * source,uint32_t source_length, uint8_t value,uint32_t count){  

  uint32_t inner_count = 0;
	uint32_t i = 0;
  for(; i < source_length;i++){
    if(source[i] == value){
      inner_count ++;
    }

    if(inner_count == count){
      return i;
    }
  }
  return -1;
}


 /********************************************
 * 拷贝部分数据到目标数组中
 ********************************************/
 void array_copy(uint8_t * dest, uint32_t dest_start, uint8_t * source, uint32_t source_start, uint32_t count){
	uint32_t i = 0;
	 for(; i < count; i++){
			dest[dest_start + i] = source[source_start + i];
	 }
 }

/*********************************
 * print HEx
 */
void print_hex(uint8_t * data ,uint32_t count){
  
	uint32_t j = 0;
  for(; j < count; j ++){
    printf("%02X ",data[j]);
  }
	printf("\r\n");
	
}

/*********************************
 * print HEx
 */
void print_hex_sub(uint8_t * data, uint32_t start ,uint count){
  
	uint32_t j = 0;
  for(; j < count; j ++){
		printf("%02X ",data[start + j]);
  }
	printf("\r\n");
	
}


void array_set(uint8_t * source,uint32_t start, uint32_t len,uint8_t xx){
		for(uint32_t i = 0; i < len; i++){
					source[start + i] = xx;
		}
}




/*****************************************/
/** HEX[0x16] BCD to DEC[16]   **/
/*****************************************/
void bcdToDec(uint8_t * bcd,uint32_t bcd_index,uint8_t * hex,uint32_t hex_index,uint32_t length){
	uint32_t i = 0;
	uint8_t tmp;
	for(; i < length;i++){
		tmp = bcd[bcd_index + i];
		hex[hex_index + i] = ((tmp >> 4) * 10) + (tmp & 0x0F);
	}
}

/** 反转数组  -------------------------------------------- **/
void array_reverse(uint8_t * source,uint32_t len){
  uint32_t i = 0;
	uint16_t middle = len / 2;
  uint8_t tmp;
  for(; i < middle;i++){
		tmp = source[i];
		source[i] = source[len - i - 1];
		source[len - i - 1] = tmp;
    //desc[i] = source[len - i - 1];
  }
}


uint8_t byteToBCD(uint8_t b){
  return (b / 10) * 16 + (b % 10);
}

/** 数据和循环数组比较是否相等  ------------------------------------- **/
uint8_t array_equal(uint8_t * dest,uint32_t dest_start,uint8_t * src,uint32_t src_start,uint32_t len){

	uint32_t i = 0;
	
	for(; i < len;i++){
		if(dest[dest_start + i] != src[src_start + i]){ 
			return 0;
		}
	}
	return 1;
}

/** 打印数据  ------------------------------------------------- **/
void array_print_hex(uint8_t * src,uint32_t start,uint32_t len){
   #if DEBUG
	 uint32_t i = 0;
	 
	 for(; i < len; i++)  printf("%02X ",src[start + i]);
	 
	 printf((uint8_t *)" \r\n");
	 #endif
}

/** 打印数据  ------------------------------------------------- **/
void array_print_str(uint8_t * src,uint32_t start,uint32_t len){
   #if DEBUG
	 uint32_t i = 0;
	 
	 for(; i < len; i++)   printf("%c",src[start + i]);  
	 
	 printf((uint8_t *)" \r\n");
	 #endif
	 
}

/** 循环数组拷贝  ------------------------------------------------- **/
void array_loop_buffer_copy(uint8_t * src,uint32_t src_start,uint8_t * dest,uint32_t dest_start,uint32_t len,uint32_t src_len){
	uint32_t i = 0,index;
	 for(; i < len; i++){
			index = (src_start + i) % src_len;
			dest[dest_start + i] = src[index];
	 }
}






