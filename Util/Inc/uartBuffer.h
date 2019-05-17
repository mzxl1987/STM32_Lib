#ifndef __uartBuffer_H__
#define __uartBuffer_H__

#include "miniConfig.h"
#include "stm32f1xx_hal.h"



/** ���ݺ�ѭ������Ƚ��Ƿ����  ------------------------------------- **/
static uint8_t                loop_buffer_equal(uint8_t * dest,uint32_t dest_start,uint8_t * src,uint32_t src_start,uint32_t len,uint32_t dest_len);

/** ѭ����������ָ��ֵ  --------------------------------------------- **/
static uint8_t                loop_buffer_set(uint8_t * dest,uint32_t dest_start,uint32_t len,uint8_t xx,uint32_t dest_len);

/** ѭ�����鿽��  ------------------------------------------------- **/
void                          loop_buffer_copy(uint8_t * src,uint32_t src_start,uint8_t * dest,uint32_t dest_start,uint32_t len,uint32_t src_len);

uint8_t                       uart_buffer_equal(UartBuffer * src,uint32_t src_start,uint8_t * dest,uint32_t dest_start,uint32_t len);

uint8_t                       uart_buffer_equalAt(UartBuffer * src,uint8_t * dest,uint32_t dest_start,uint32_t len,uint32_t * dest_index,uint32_t * dest_len);

uint8_t                       uart_buffer_set(UartBuffer * src,uint32_t start,uint32_t len,uint8_t xx);

void                          uart_buffer_copy(UartBuffer * src,uint32_t src_start,uint8_t * dest,uint32_t dest_start,uint32_t len);

uint8_t                       uart_buffer_find(UartBuffer * src,uint8_t * head,uint32_t head_len,uint8_t * tail,uint32_t tail_len,uint32_t * dest_index,uint32_t * dest_len);

void                          uart_buffer_next(UartBuffer * src,uint32_t move_len);

void                          uart_buffer_print_hex(UartBuffer * src,uint32_t start,uint32_t len);

/** ��ӡ����  ------------------------------------------------- **/
void                          uart_buffer_print_str(UartBuffer * src,uint32_t start,uint32_t len);

void                          uart_buffer_pre(UartBuffer * src,uint32_t move_len);

void                          uart_buffer_jump(UartBuffer * src,uint32_t jump_to_index);














#endif
