#pragma once
#include "tree.h"

/* 
 * 双亲表示法
 * 使用数组表示
 */
#define MAX_TREE_SIZE 100
typedef struct PTNode  //结点结构
{
	TElemType data;
	int parent;//双亲位置域
}PTNode;
typedef struct //树的结构
{
	PTNode nodes[MAX_TREE_SIZE];
	int r, n; //根的位置和结点数
}PTree;

/*
 * 树的孩子链表存储表示
 */
typedef struct CTNode //孩子结点
{
	int child;
	struct CTNode * next;
}*ChildPtr;

typedef struct
{
	TElemType data;
	ChildPtr firstchild; //孩子链表头指针
}CTBox;

typedef struct
{
	CTBox nodes[MAX_TREE_SIZE]; 
	int n, r; //结点数和根的位置
}CTree;

/*
 * 树的二叉链表(孩子-兄弟)存储表示
 *
 */
typedef struct CSNode
{
	TElemType data;
	struct CSNode *firstchild, *nextsibing; //该结点的第一个孩子结点和下一个兄弟结点
}CSNode, *CSTree;

// 孩子-兄弟存储基本操作
#define ClearTree DestroyTree //二者操作相同
void InitTree(CSTree &T);
void DestroyTree(CSTree &T);

typedef CSTree QElemType; //定义队列元素为孩子-兄弟二叉链表的指针类型
#include "queue.h"
#undef ENABLE_SQUEUE_HEAP //使用链队列
#undef ENABLE_CYCLICQUEUE_HEAP

void CreateTree(CSTree T);
Status TreeEmpty(CSTree T);
int TreeDepth(CSTree T);
TElemType Value(CSTree p);
TElemType Root(CSTree T);
CSTree Point(CSTree T, TElemType s);
Status Assign(CSTree &T, TElemType cur_e, TElemType value);
TElemType Parent(CSTree T, TElemType cur_e);