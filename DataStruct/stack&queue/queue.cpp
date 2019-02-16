/*
 * 各种队列的实现
 */

#include "queue.h"

#ifdef ENABLE_SQUEUE_HEAP
void InitQueue_Sq(SqQueue &Q)
{
    Q.front = Q.rear = 0;
    echo(InitQueue_Sq);
    belongt(3);
}

status EnQueue_Sq(SqQueue &Q, ElemType e)
{//队不满
    if(Q.rear >= MaxSize_q)
        exit(OVERFLOW);
    Q.data[Q.rear] = e;
    Q.rear += 1;
    echo(EnQueue_Sq);
    belongt(3);
    return OK;
}

status DeQueue_Sq(SqQueue &Q, ElemType &e)
{
    if(Q.front > MaxSize_q - 1)
        exit(OVERFLOW);
    e = Q.data[Q.front];
    Q.front += 1;
    echo(DeQueue_Sq);
    belongt(3);
    return OK;
}
#endif //ENABLE_SQUEUE_HEAP


#ifdef ENABLE_LINKQUEUE
void InitQueue_L(LinkQueue_H &Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(LinkNode_Queue));//头结点
    if(!Q.front)
        exit(OVERFLOW);
    Q.front->next = nullptr;
    echo(InitQueue);
    belongt(4);
}

void DestoryQueue_L(LinkQueue_H &Q)
{
    while(Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    echo(DestoryQueue);
    belongt(4);
}

void ClearQueue_L(LinkQueue_H &Q)
{//销毁并重建
    DestoryQueue_L(Q);
    InitQueue_L(Q);
}

status QueueEmpty_L(LinkQueue_H Q)
{
    if(Q.front->next == nullptr)
        return TRUE;
    else
        return FALSE;
}

status QueueLength_L(LinkQueue_H Q)
{
    int i = 0;
    QueuePtr p = Q.front;//头结点
    while(Q.rear != p)
    {
        ++i;
        p = p->next;
    }
    printf("队列的长度是:%d\n", i);
    echo(QueueLength);
    belongt(4);
    return OK;
}

status GetHead_L(LinkQueue_H Q, QElemType &e)
{//队列非空，返回队头
    QueuePtr p;
    if(Q.front == Q.rear) //队列空
        return ERROR;
    p = Q.front->next;//队头
    e = p->data;
    return OK;
}

void EnQueue_L(LinkQueue_H Q, QElemType e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(LinkNode_Queue));
    if(!p)
        exit(OVERFLOW);
    p->data = e;
    p->next = nullptr;
    Q.rear->next = p; //尾元素指向队尾
    Q.rear = p; //头指针的尾指针指向队尾
    echo(EnQueue_L);
    belongt(4);
}

status DeQueue_L(LinkQueue_H Q, QElemType &e)
{
    QueuePtr p;
    if(Q.front == Q.rear) //队列空
        return ERROR;
    p = Q.front->next;//队头元素,将被删除
    e = p->data;//删除前先赋值
    Q.front->next = p->next;//队头指针指向新的队头元素
    /*              ___              ____
     * (队头头指针)|_|_|-->(队尾结点)|_|_|-->nullptr
     *                               p指针指向尾结点(待删除)
     */
    if(Q.rear == p)
    {
        Q.rear = Q.front;//若此时恰好删除p后无队列结点，则令尾指针指向头指针表示空队列
    }
    free(p);
    echo(DeQueue_L);
    belongt(4);
    return OK;
}

void Traverse_L(LinkQueue_H Q, void(* visit)(QElemType))
{
    QueuePtr p = Q.front->next;//指向队头元素
    while(p)
    {
        visit(p->data);
        p = p->next;//直至尾结点
    }
    echo(Traverse_L);
    belongt(4);
}
#endif //ENABLE_SQUEUE_HEAP


#ifdef ENABLE_CYCLICQUEUE_HEAP
void InitQueue_C(CycQueue &Q)
{
    Q.base = (QElemType *)malloc(Max_QSIZE * sizeof(QElemType));
    if(!Q.base)
        exit(OVERFLOW);
    Q.front = Q.rear = 0;//队列初始空的条件
    echo(InitQueue_C);
    belongt(5);
}

void DestoryQueue_C(CycQueue &Q)
{
    if(Q.base)
        free(Q.base);
    Q.base = nullptr;
    Q.rear = Q.front = 0;
    echo(DeQueue_C);
    belongt(5);
}

void ClearQueue_C(CycQueue &Q)
{
    Q.front = Q.rear = 0;//将队尾队头指向0
    echo(ClearQueue_C);
    belongt(5);
}

status QueueEmpty_C(CycQueue Q)
{
    echo(QueueEmpty_C);
    belongt(5);
    if(Q.rear == Q.front)
        return TRUE;
    else
        return FALSE;
}

status QueueLength_C(CycQueue Q)
{//TODO:关键代码！
    /*
     * 假想一个地址递增的地址空间，rear在比front的高地址处，此时长度即为rear-front
     * 当rear循环增加时处于逻辑上的比front的低地址处，此时长度为rear-front+MAX_QSIZE
     * 故综合气来为(Q.rear - Q.front + Max_QSIZE) % Max_QSIZE。第一种情况下%可保证加MAX_QSIZE的无效果
     */
    echo(QueueLength_C);
    belongt(5);
    return (Q.rear - Q.front + Max_QSIZE) % Max_QSIZE;
}

status GetHead_C(CycQueue Q, QElemType &e)
{
    if(Q.rear == Q.front)//队列为空
        return ERROR;
    e = Q.base[Q.front];
    echo(GetHead_C);
    belongt(5);
    return OK;
}

status EnQueue_C(CycQueue &Q, QElemType e)
{//TODO:review
    // 先判断队满
    if((Q.rear + 1) % Max_QSIZE == Q.front)
        return ERROR;
    Q.base[Q.rear] = e;//尾指针指向空元素，故先赋值，再移动尾指针
    Q.rear = (Q.rear + 1) % Max_QSIZE;//队尾指针增一并取余
    echo(EnQueue_C);
    belongt(5);
    return OK;
}

status DeQueue_C(CycQueue &Q, QElemType &e)
{
    if(Q.rear == Q.front)//队列空
        return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % Max_QSIZE;//队头指针指向队头元素，故先交付值，再删除，即增一
    echo(DeQueue_C);
    belongt(5);
    return OK;
}

status QueueTraverse_C(CycQueue Q, void(* visit)(QElemType))
{
    if(Q.front == Q.rear)
        return ERROR;
    int i = Q.front;//指向队头
    while(i != Q.rear)
    {
        visit(Q.base[i]);
        i = (i + 1) % Max_QSIZE;
    }
    echo(QueueTraverse_C);
    belongt(5);
    return OK;
}
#endif // ENABLE_CYCLICQUEUE_HEAP

