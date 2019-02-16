/*
 * 二叉树的定义与基本操作函数接口
 */
/*
 * 二叉树的顺序存储：根节点存储在[0]
 * 第i层结点的序号(个数-1)为：2^(i-1) -1 至 2^i - 2
 * 序号为j的结点其所处层次i为 |_log2(j+1)_| - 1
 * 在层i中的排序为K = j - 2^(i-1) + 2
 * 双亲序号|_j-1 / 2_|,左孩子2j+1,右孩子2j+2
 */
 /*
 * 二叉树的顺序存储：根节点存储在[1]
 * 第i层结点的序号为：2^(i-1) 至 2^i - 1
 * 序号为j的结点其所处层次i为 |_log2(j)_| - 1
 * 在层i中的排序为K = j - 2^(i-1) + 1
 * 双亲序号|_j / 2_|,左孩子2j,右孩子2j+1
 */
#pragma once

#include "tree.h"
#include "queue.h"
#include "stack.h"

//队列的函数使用
#undef ENABLE_SQUEUE_HEAP
//#define ENABLE_LINKQUEUE
#undef ENABLE_CYCLICQUEUE_HEAP

//栈的函数的使用
//#define ENABLE_SQSTACK_HEAP
#undef ENABLE_SQSTACK_ARRARY
#undef ENABLE_LINKSTACK


/*
 * 结点链式存储
 * 无需头结点，直接指向根结点即可(即第一个元素root)
 */
typedef struct BinaryTreeNode
{
	TElemType data;
	BinaryTreeNode *lchild;
	BinaryTreeNode *rchild;//左右孩子
}BiTNode,  * BiTree;

typedef BiTree QElemType; //定义 队列元素 为二叉树指针类型
typedef BiTree SElemType; //定义 栈元素 为二叉树的指针类型

#define InOrderTraverse_NR1 InOrderTraverse_NRecursion1  
#define InOrderTraverse_NR2 InOrderTraverse_NRecursion1  
/*
 * 基本操作函数定义
 * 二叉链表的存储结构的许多基本操作都采用了递归函数
 */

#define ClearBiTree DestroyBiTree //清空二叉树和销毁二叉树操作一样

void InitBiTree(BiTree & T);
void DestroyBiTree(BiTree & T);
void PreOrderTraverse(BiTree T, void(*visit)(TElemType));
void InOrderTraverse(BiTree T, void(*visit)(TElemType));
void PostOrderTraverse(BiTree T, void(*visit)(TElemType));

//(存储结构由上述定义的)基本操作函数
Status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
TElemType Root(BiTree T);
TElemType Value(BiTree p);
void Assign(BiTree p, TElemType value);
Status DeleteChild(BiTree p, int LR);
void CreateBiTree(BiTree &T);
Status InsertChild(BiTree p, int LR, BiTree e);//形参T无用

//使用队列的函数
void LevleOrderTraverse(BiTree T, void(*visit)(TElemType));
BiTree Point(BiTree T, TElemType s);
TElemType LeftChild(BiTree T, TElemType e);
TElemType RightChild(BiTree T, TElemType e);
TElemType Parent(BiTree T, TElemType e);
TElemType LeftSibling(BiTree T, TElemType e);
TElemType RightSibling(BiTree T, TElemType e);

//使用栈的函数
void InOrderTraverse_NRecursion1(BiTree T, void(*visit)(TElemType));
void InOrderTraverse_NRecursion2(BiTree T, void(*visit)(TElemType));
