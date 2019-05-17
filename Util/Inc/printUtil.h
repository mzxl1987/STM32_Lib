#ifndef __printUtil_H__
#define __printUtil_H__

#include "stm32f1xx_hal.h"

void println(uint8_t * msg);
static void print_format(uint8_t * msg,uint8_t * format);
void print_msg(uint8_t * msg);
void print_success_msg(uint8_t * msg);
void print_error_msg(uint8_t * msg);
void print_response_msg(uint8_t * msg);
/** ÉèÖÃÏûÏ¢ **/
void print_set_msg(uint8_t * msg);

#endif
