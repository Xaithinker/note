#include "pch.h"
#include "ThreadedBinaryTree.h"

Status InOrderThreading_Thr(BiThrTree T, Status(*visit)(TElemType e))
{//T指向头结点，lchild指向根结点
	//中序遍历二叉线索树T的非递归算法，对每个数据元素调用函数visit
	BiThrTree p = T->lchild;//p指向根结点
	while (p != T)
	{
		while (p->LTag == Link)
			p = p->lchild;
		if (!visit(p->data))
			return ERROR;  //访问其左子树为空的结点
		while (p->RTag == Thread && p->lchild != T)//通过后继可以方便的快速定位接下来要访问的结点
		{
			p = p->rchild;
			visit(p->data); //访问后继结点
		}
		p = p->rchild;//定位到子树的根结点即可，循环自此开始
	}
	return OK;
}

Status InOrderThreading(BiThrTree & Thrt, BiThrTree T)
{//中序遍历二叉树T,并将其中序线索化，Thrt指向头结点
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));//头结点
	if (!Thrt)
		exit(OVERFLOW);
	Thrt->LTag = Link;//指向头结点 枚举类型的成员直接访问。为const value,一旦定义不可更改。
	Thrt->RTag = Thread;//指向最后一个结点
	if (!T)
		Thrt->lchild = Thrt;//空树，指向自己
	else
	{
		Thrt->lchild = T;
		pre = Thrt; //定义临时变量
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;//最后一个结点线索化
		Thrt->rchild = pre;
	}
	return OK;
}

void InThreading(BiThrTree p)
{
	if (p)
	{
		InThreading(p->lchild); //左子树线索化
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}//前驱线索
		if (!pre->lchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}//后继线索
		pre = p;
		InThreading(p->rchild);
	}
}
