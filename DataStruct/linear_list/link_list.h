/*
 * 链表结构定义和基本操作函数接口
 */

#ifndef DATASTRUCT_LINK_LIST_H
#define DATASTRUCT_LINK_LIST_H

#include "global_deined.h"



#ifndef SINGLE_LINK_LIST
#define SINGLE_LINK_LIST

#define SINGLE_LINK_LIST_START
#define SINGLE_LINK_LIST_END

#define CYCLIC_SINGLE_LINK_LIST //属于循环单链表的操作

typedef int ElemType;

//含头结点的线性链表
typedef struct LNode
{
    ElemType data;
    struct LNode * next;
}LNode, * LinkList;

/*
 * 基本操作函数
 */
LinkList InitList_();
void DestroyList_(LinkList);
void ClearList_(LinkList);
status ListEmpty_(LinkList);
int ListLength_(LinkList);
status GetElem_(LinkList, int, ElemType *);
int LocateElem_(LinkList, ElemType, status(* compare)(ElemType, ElemType));
status PriorElem_(LinkList, ElemType, ElemType *);
status NextElem_(LinkList, ElemType, ElemType *);
status ListInsert_(LinkList, int, ElemType);
status ListDelete_(LinkList, int, ElemType *);
void ListTraverse_(LinkList , void (* visit)(ElemType));

#endif //SINGLE_LINK_LIST



#ifndef DOUBLE_LINK_LIST
#define DOUBLE_LINK_LIST

#define CYCLIC_DOUBLE_LINK_LIST //属于循环双链表的操作

//双链表的定义
typedef struct DLNode
{
    ElemType data;
    struct DLNode * prior;
    struct DLNode * next;
}DLNode, * DLinkList;

#endif //DOUBLE_LINK_LIST



//静态链表的定义
#ifndef STATIC_LINK_LIST
#define STATIC_LINK_LIST

#define MaxSize 20

typedef struct
{
    ElemType data;
    int next; //下一个元素的数组下标
}SLinkList[MaxSize];

#endif //STATIC_LINK_LIST


#endif //DATASTRUCT_LINK_LIST_H
