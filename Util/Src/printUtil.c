#include "printUtil.h"

#include "all.h"

/** ���д�ӡ����     ---------------------  **/
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
				
		/* ��һ�� */
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
		
		/* ���һ�� */
		i = MAX + SPACE;
		while(i > 0){
			printf(format);
			i--;
		}
		printf("\r\n");
		#endif 
}

/** ��ʽ����ӡ��Ϣ   --------------------- **/
void print_msg(uint8_t * msg){
	print_format(msg,"*");
}

/** �ɹ���Ϣ **/
void print_success_msg(uint8_t * msg){
	print_format(msg,"o");
}

/** ������Ϣ **/
void print_error_msg(uint8_t * msg){
	print_format(msg,"x");
}

/** ��Ӧ��Ϣ **/
void print_response_msg(uint8_t * msg){
	print_format(msg,"#");
}

/** ������Ϣ **/
void print_set_msg(uint8_t * msg){
	print_format(msg,"=");
}


















