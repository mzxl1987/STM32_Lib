#include "printUtil.h"

#include "all.h"

/** 换行打印数据     ---------------------  **/
void println(uint8_t * msg){
  
	printRTCTime_Log();
	printf(msg);
	printf("\r\n");
	
  
}

static void print_format(uint8_t * msg,uint8_t * format){
    
    #if DEBUG
		printRTCTime_Log();
		printf("\r\n");
		
		int32_t len = 0,i,size;
		while(msg[len] != 0x00)  len++;
		uint32_t MAX = 100;
		
		MAX = MAX > len ? len : MAX;
		
		uint32_t SPACE = 20;
		size = len % MAX ? len / MAX + 1 : len / MAX;
				
		/* 第一行 */
		i = MAX + SPACE;
		while(i > 0){
			printf(format);
			i--;
		}
		printf("\r\n");
		
		for(uint8_t j = 0; j < size; j++){
			printf(format);
			printf("         ");
			
			uint32_t k = 0;
			for(; k < MAX && (k + j*MAX) < len; k++){
				printf("%c",msg[k + j*MAX]);					
			}
			
			while(k < MAX){
				printf(" ");
				k++;
			}
			
			printf("         ");
			printf(format);
			printf("\r\n");
			
		}
		
		/* 最后一行 */
		i = MAX + SPACE;
		while(i > 0){
			printf(format);
			i--;
		}
		printf("\r\n");
		#endif 
}

/** 格式化打印消息   --------------------- **/
void print_msg(uint8_t * msg){
	print_format(msg,"*");
}

/** 成功消息 **/
void print_success_msg(uint8_t * msg){
	print_format(msg,"o");
}

/** 错误消息 **/
void print_error_msg(uint8_t * msg){
	print_format(msg,"x");
}

/** 回应消息 **/
void print_response_msg(uint8_t * msg){
	print_format(msg,"#");
}

/** 设置消息 **/
void print_set_msg(uint8_t * msg){
	print_format(msg,"=");
}


















