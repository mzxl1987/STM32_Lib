#ifndef __arrayUtil_H__
#define __arrayUtil_H__

#include "stm32f1xx_hal.h"
#include "config.h"


/************************************************/
/** BCD字符转换成Dec **/
/************************************************/
uint8_t                       bcdCharToDec(uint8_t c);
/** number 转 字符  **/
uint8_t                       numberToChar(uint32_t number);
 /**  拷贝部分数据到目标数组中  **/
void                          array_copy(uint8_t * dest, uint32_t dest_start, uint8_t * source, uint32_t source_start, uint32_t count);
/**  打印字节数组,以HEX字符串的形式输出  **/
void                          print_hex(uint8_t * data ,uint count);
/**  打印字节数组,以HEX字符串的形式输出  **/
void                          print_hex_sub(uint8_t * data, uint32_t start ,uint count);
/**  数组赋初值  **/
void                          array_set(uint8_t * source,uint32_t start, uint32_t len,uint8_t xx);
/*****************************************/
/** HEX[0x16] BCD to DEC[16]   **/
/*****************************************/
void                          bcdToDec(uint8_t * bcd,uint32_t bcd_index,uint8_t * hex,uint32_t hex_index,uint32_t length);
/** 反转数组  **/
void                          array_reverse(uint8_t * source,uint32_t len);
/** byte to BCD **/
uint8_t                       byteToBCD(uint8_t b);
/**   uint8_t[] to uint32_t  **/
uint32_t                      convert_to_uint32(uint8_t *data,uint32_t start);
/** uint8_t[] 装换成 uint32_t ,小端模式, uint8_t[]中低字节在前 **/
uint32_t                      convert_to_uint32_low_mode(uint8_t *data,uint32_t start);
/** uint8_t[] 装换成 uint16_t ,小端模式, uint8_t[]中低字节在前 **/
uint16_t                      convert_to_uint16_low_mode(uint8_t *data,uint32_t start);
/** uint32_t to uint8_t[] 小端模式 **/
void                          convert_uint32_to_uint8_array_low_mode(uint32_t source,uint8_t * dest,uint32_t dest_start);
/** 比较数组指定区间是否相等  **/
uint8_t                       array_equal(uint8_t * dest,uint32_t dest_start,uint8_t * src,uint32_t src_start,uint32_t len);

/** 打印数据  ------------------------------------------------- **/
void                          array_print_hex(uint8_t * src,uint32_t start,uint32_t len);
/** 打印数据  ------------------------------------------------- **/
void                          array_print_str(uint8_t * src,uint32_t start,uint32_t len);




#endif
