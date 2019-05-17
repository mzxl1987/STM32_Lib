#ifndef __LQueue_H__
#define __LQueue_H__

#include "config.h"


//取出并移除第一个元素
int poll(LQueue *q);

//获取长度
int len(LQueue *q);

//插入k，返回1表示插入成功
int add(LQueue *q,ubyte k);

//取出头部元素，不删除此元素，peek是“偷看”的意思
int peek(LQueue* q);

//返回1表示为空，0表示不空
int isEmpty(LQueue *q);

//创建大小为n的队列
void createQue(LQueue *q,int n);
LQueue * createQueue(int n,ubyte *val);

void display(LQueue *q);

void clear(LQueue *q);























#endif
