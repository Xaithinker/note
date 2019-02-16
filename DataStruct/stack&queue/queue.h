/*
 * 队列的基本内容
 * 1.顺序队列包括循环队列
 * 2.链队列
 * 3.双端队列
 */
#ifndef DATASTRUCT2_QUEUE_H
#define DATASTRUCT2_QUEUE_H

#include "global_defined.h"


/*
 * 静态分配的顺序队列
 * 初始状态：Q.rear=Q.front=0
 * 进队操作：队不满，值送队尾，队尾指针再加一！
 * 出队操作：队不空，取对头值，队头指针加一！
 */
#define ENABLE_SQUEUE_HEAP
#define ENABLE_LINKQUEUE
#define ENABLE_CYCLICQUEUE_HEAP

#ifdef ENABLE_SQUEUE_HEAP
#define ENABLE_SQUEUE_HEAP_START
#define ENABLE_SQUEUE_HEAP_END
ENABLE_SQUEUE_HEAP_START
#define MaxSize_q 50
typedef struct SqQueue_Heap
{
    ElemType data[MaxSize_q];
    int front;//队头
    int rear; //队尾
}SqQueue;

void InitQueue_Sq(SqQueue &);
status EnQueue_Sq(SqQueue &, ElemType);
status DeQueue_Sq(SqQueue &, ElemType &);
ENABLE_SQUEUE_HEAP_END
#endif //ENABLE_SQUEUE_HEAP


/*
 * 链队列
 * 带头结点
 * front指向头结点；rear指向队尾元素
 * 由front->next依次指向后面的元素直至rear->next=nullptr
 */
#ifdef ENABLE_LINKQUEUE
#define ENABLE_LINKQUEUE_START
#define ENABLE_LINKQUEUE_END

ENABLE_LINKQUEUE_START
typedef struct LinkQueue //元素类型
{
    QElemType data;
    struct LinkQueue * next;
}* QueuePtr;

typedef struct LinkNode_Queue //定义头结点
{
    QueuePtr front;//指向头结点，非第一个队头元素Q.front->next为第一即队头元素
    QueuePtr rear;//指向尾节点，是最后一个元素
}LinkQueue_H;

void InitQueue_L(LinkQueue_H &);
void DestoryQueue_L(LinkQueue_H &);
void ClearQueue_L(LinkQueue_H &);
status QueueEmpty_L(LinkQueue_H);
status QueueLength_L(LinkQueue_H);
status GetHead_L(LinkQueue_H, QElemType &);
void EnQueue_L(LinkQueue_H, QElemType);
status DeQueue_L(LinkQueue_H, QElemType &);
ENABLE_LINKQUEUE_END
#endif //ENABLE_LINKQUEUE


#ifdef ENABLE_CYCLICQUEUE_HEAP
#define ENABLE_CYCLICQUEUE_HEAP_START
#define ENABLE_CYCLICQUEUE_HEAP_END
/*
 * 循环队列-队列的顺序表示和实现
 * 这里队列长度少用一个存储单元为了区分队满和队空
 */
#define Max_QSIZE 5 //最大队列长度+1
typedef struct CyclicQueue_Sq
{
    QElemType * base;
    int front;
    int rear;
}CycQueue;

ENABLE_CYCLICQUEUE_HEAP_START
void InitQueue_C(CycQueue &);
void DestoryQueue_C(CycQueue &);
void ClearQueue_C(CycQueue &);
status QueueEmpty_C(CycQueue);
status QueueLength_C(CycQueue);
status GetHead_C(CycQueue, QElemType &);
status EnQueue_C(CycQueue &, QElemType);
status DeQueue_C(CycQueue &, QElemType &);
status QueueTraverse_C(CycQueue, void(* visit)(QElemType));
ENABLE_CYCLICQUEUE_HEAP_END
#endif // ENABLE_CYCLICQUEUE_HEAP

#endif //DATASTRUCT2_QUEUE_H
