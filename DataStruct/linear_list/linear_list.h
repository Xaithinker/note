/*
 * 线性表的定义及操作接口
 */

#ifndef DATASTRUCT_LINEAR_LIST_H
#define DATASTRUCT_LINEAR_LIST_H

#include "global_deined.h"

#define LIST_INIT_SIZE 10 //线性表存储空间分配量
#define LIST_INCREMENT 2 //线性表空间分配增量

typedef int ElemType;

//定义动态顺序表
#ifndef DYNAMIC_SEQUENCE_LIST
#define DYNAMIC_SEQUENCE_LIST

#define DYNAMIC_SEQUENCE_LIST_START
#define DYNAMIC_SEQUENCE_LIST_END

typedef struct SqList  //动态分配的顺序表
{
    ElemType * elem;
    int length;     //当前线性表长度
    int listsize;   //线性表总长度
}SqList;

/*
 * 线性表的基本操作接口
 */

void InitList(SqList *);
void DestroyList(SqList *);
void ClearList(SqList *);
status ListEmpty(SqList);
int ListLength(SqList);
status GetElem(SqList, int, ElemType *);
int LocateElem(SqList, ElemType, status(*compare)(ElemType, ElemType));
status PriorElem(SqList, ElemType, ElemType *);
status NextElem(SqList, ElemType, ElemType *);
status ListInsert(SqList *, int, ElemType);
status ListDelete(SqList *, int, ElemType *);
void Traverse(SqList, void(* visit)(ElemType *));

#endif //DYNAMIC_SEQUENCE_LIST


//静态顺序表
#ifndef STATIC_SEQUENCE_LIST
#define STATIC_SEQUENCE_LIST

#define STATIC_SEQUENCE_LIST_START
#define STATIC_SEQUENCE_LIST_END

#define MaxSize 20

typedef struct
{
   ElemType data[MaxSize]; //静态分配的一维数组作顺序表，其长度固定
   int length;
}SSqList;

#endif //STATIC_SEQUENCE_LIST


#endif //DATASTRUCT_LINEAR_LIST_H
