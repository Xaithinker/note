/*
 * There is some algorithms based on key algorithms of sqlist and link_list struct
 */

#ifndef DATASTRUCT_LINEAR_LIST_ALGO_H
#define DATASTRUCT_LINEAR_LIST_ALGO_H

#include "global_deined.h"
#include "linear_list.h"
#include "link_list.h"


#ifndef SEQUENCE_LIST_ALGO
#define SEQUENCE_LIST_ALGO //定义宏:顺序表的算法
#define SEQUENCE_LIST_ALGO_START
#define SEQUENCE_LIST_ALGO_END

void MergeList_sq(SqList, SqList, SqList *);

#endif //SEQUENCE_LIST_ALGO


#ifndef LINK_LIST_ALGO
#define LINK_LIST_ALGO //定义宏:线性链表的算法
#define LINK_LIST_ALGO_START
#define LINK_LIST_ALGO_END

void MergeList_L(LinkList, LinkList, LinkList);

#endif //LINK_LIST_ALGO






#endif //DATASTRUCT_LINEAR_LIST_ALGO_H
