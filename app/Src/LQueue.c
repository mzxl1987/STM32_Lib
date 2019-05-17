#include "LQueue.h"
#include "config.h"
#include "stdlib.h"


//ȡ�����Ƴ���һ��Ԫ��
int poll(LQueue* q){
		int res = q->array[q->front];
		q->front = (++(q->front))%q->size;
		q->eleNum--;
		return res;
}

//��ȡ����
int len(LQueue *q){
		return q->eleNum;
}

//����k������1��ʾ����ɹ�
int add(LQueue *q,ubyte k){
		//printf("[add FUN]Queue len : %d, Size : %d, Tail:%d,array size : %d\r\n",q->eleNum,q->size,q->tail,sizeof(q->array));
		if(q->size==q->eleNum){
				return 0;
		}
		
		q->eleNum++;
		//q->array[0] = k;
		q->array[q->tail] = k;
		q->tail = (q->tail+1) % q->size;
		
		//printf("[add FUN]Queue len : %d\r\n",q->eleNum);
		
		return 1;
}

//ȡ��ͷ��Ԫ�أ���ɾ����Ԫ�أ�peek�ǡ�͵��������˼
int peek(LQueue* q){
		return q->array[q->front];
}

//����1��ʾΪ�գ�0��ʾ����
int isEmpty(LQueue* q){
		if(q->eleNum==0){
				return 1;
		}
		return 0;
}

//������СΪn�Ķ���
void createQue(LQueue *que,int n){

		que = (LQueue *)malloc(sizeof(LQueue));
		que->size = n;
		que->eleNum = 0;
		//que->array = (ubyte *)malloc(sizeof(int) * n);
		que->front = 0;
		que->tail = 0;
		
		//printf("[createQue FUN]Queue size : %d\r\n",que->size);
		//printf("[createQue FUN]Queue len : %d\r\n",que->eleNum);
		
}

 //������СΪn�Ķ���
LQueue * createQueue(int n,ubyte *val){
		LQueue * que;
		que = (LQueue *)malloc(sizeof(LQueue));
		que->size = n;
		que->eleNum = 0;
		que->array = val;
		que->front = 0;
		que->tail = 0;
		
		//printf("[createQue FUN]Queue size : %d\r\n",que->size);
		//printf("[createQue FUN]Queue len : %d\r\n",que->eleNum);
		return que;
}

void display(LQueue* q){
		int i = q->front;
		printf("elements: ");
		while(i!=q->tail){
				printf("%d ",q->array[i]);
				i = (i+1)%q->size;
		}
		printf("\n");
		printf("size: %d,elements num: %d\n",q->size,q->eleNum);
		printf("front: %d, tail:%d \n",q->front,q->tail);
}


void clear(LQueue *que){
	que->eleNum = 0;
	que->front = 0;
	que->tail = 0;
}





































