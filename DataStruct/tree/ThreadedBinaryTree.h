/*          线索二叉树定义
 *______________________________________
 *|lchild | LTag | data | RTag | rchild| 

 * LTag = 0 lchild域指示结点的左孩子
 *        1 lchild域指示结点的前驱

 * RTag = 0 rchild域指示结点的右孩子
 *        1 rchild域指示结点的前驱
 */
#pragma once
#include "tree.h"

/*
 *  二叉线索存储表示
 */
typedef enum PointerTag{Link, Thread}; //Link==0:指针 Thread==1:线索
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild, *rchild; //左右孩子指针
	PointerTag LTag, RTag; //左右标志
}BiThrNode, *BiThrTree;

//仿照线性表的存储结构，在二叉树的线索链表上添加头结点
//lchild指向二叉树的根结点
//rchild指向中序遍历时访问的最后一个结点

//令中序遍历的第一个结点的lchild和最后一个rchild指向头结点
//(既可以从第一个结点顺后继进行遍历，也可以从最后一个结点其顺前驱遍历)
extern BiThrTree pre;
Status InOrderThreading_Thr(BiThrTree T, Status(*visit)(TElemType e));
Status InOrderThreading(BiThrTree & Thrt, BiThrTree T);
void InThreading(BiThrTree p);