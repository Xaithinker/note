/*
 * 栈定义区，包括顺序栈和链栈(这里栈的概念和虚存中栈空间不同
 * 这里栈只代表了FILO的特性，不强调地址增长的方向性
 * 虚存中的栈空间为过程调用使用的向低地址增长的栈结构
 * TODO:栈的应用代码实现
 */

#ifndef DATASTRUCT2_STACK_H
#define DATASTRUCT2_STACK_H

#include "global_defined.h"

#define ENABLE_SQSTACK_HEAP
#define ENABLE_SQSTACK_ARRARY
#define ENABLE_LINKSTACK

#ifdef ENABLE_SQSTACK_HEAP
#define ENABLE_SQSTACK_HEAP_START
#define ENABLE_SQSTACK_HEAP_END

ENABLE_SQSTACK_HEAP_START
// 定义堆分配顺序栈
#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 2
typedef struct SqStack_Heap
{
    SElemType * base;
    SElemType * top;
    int stacksize; //当前以分配的存储空间，以元素为单位
}SqStack_H;

/*
 * 基本操作函数定义
 */
void InitStack(SqStack_H &);
void DestroyStack(SqStack_H &);
void ClearStack(SqStack_H &);
status StackEmpty(SqStack_H);
unsigned long StackLength(SqStack_H);
status GetTop(SqStack_H, SElemType &e);
void Push(SqStack_H &, SElemType);
status Pop(SqStack_H &, SElemType &);
void StackTraverse(SqStack_H, void (* visit)(SElemType));
ENABLE_SQSTACK_HEAP_END
#endif //ENABLE_SQSTACK_HEAP

#ifdef ENABLE_SQSTACK_ARRARY
#define ENABLE_SQSTACK_ARRARY_START
#define ENABLE_SQSTACK_ARRARY_END

ENABLE_SQSTACK_ARRARY_START
//定义数组分配顺序栈
#define MaxSize 50
typedef struct SqStack_Array
{
    SElemType data[MaxSize];
    int top;
}SqStack_A;
void InitStack(SqStack_A &);
void ClearStack(SqStack_A &);
status StackEmpty(SqStack_A);
int StackLength(SqStack_A);
status GetTop(SqStack_A, SElemType &e);
void Push(SqStack_A &, SElemType);
status Pop(SqStack_A &, SElemType &);
void StackTraverse(SqStack_A, void (* visit)(SElemType));

ENABLE_SQSTACK_ARRARY_END

#endif //ENABLE_SQSTACK_ARRARY


#ifdef ENABLE_LINKSTACK
#define ENABLE_LINKSTACK_START
#define ENABLE_LINKSTACK_END

ENABLE_LINKSTACK_START
//定义链栈
typedef struct SLinkNode
{
    SElemType data; //数据域
    struct SLinkNode * next; //指向下一元素
}SLinkNOde, *SLinkNode_P;

void InitStack(SLinkNode_P &);
void DestroyStack(SLinkNode_P);
void ClearStack(SLinkNode_P);
status StackEmpty(SLinkNode_P);
int StackLength(SLinkNode_P);
status GetTop(SLinkNode_P, SElemType &e);
void Push(SLinkNode_P, SElemType);
status Pop(SLinkNode_P, SElemType &);
void StackTraverse(SLinkNode_P, void (* visit)(SElemType));

ENABLE_LINKSTACK_END
#endif //ENABLE_LINKSTACK


#endif //DATASTRUCT2_STACK_H
