#ifndef __LQueue_H__
#define __LQueue_H__

#include "config.h"


//ȡ�����Ƴ���һ��Ԫ��
int poll(LQueue *q);

//��ȡ����
int len(LQueue *q);

//����k������1��ʾ����ɹ�
int add(LQueue *q,ubyte k);

//ȡ��ͷ��Ԫ�أ���ɾ����Ԫ�أ�peek�ǡ�͵��������˼
int peek(LQueue* q);

//����1��ʾΪ�գ�0��ʾ����
int isEmpty(LQueue *q);

//������СΪn�Ķ���
void createQue(LQueue *q,int n);
LQueue * createQueue(int n,ubyte *val);

void display(LQueue *q);

void clear(LQueue *q);























#endif
