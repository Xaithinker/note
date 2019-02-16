/*
 * 二叉树基本操作函数实现
 */
#include "pch.h"

#include "BinaryTree.h"

void InitBiTree(BiTree & T)
{//构造空二叉树
	T = nullptr;
}

void DestroyBiTree(BiTree & T)
{
	if (T)
	{//根结点的地址即T,T指向根结点
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);//释放根节点
		T = nullptr;
	}
}

void PreOrderTraverse(BiTree T, void(* visit)(TElemType))
{//先序递归遍历，对每个结点调用Visit一次
	if (T)
	{
		visit(T->data);//先访问根结点
		PreOrderTraverse(T->lchild, visit);//先左子树
		PreOrderTraverse(T->rchild, visit);//后右子树
	}

}

void InOrderTraverse(BiTree T, void(*visit)(TElemType))
{//中序递归遍历
	if (T)
	{
		InOrderTraverse(T->lchild, visit);//先中序遍历左子树
		visit(T->data);//在访问根结点
		InOrderTraverse(T->rchild, visit);//最后中序遍历右子树
	}
}

void PostOrderTraverse(BiTree T, void(*visit)(TElemType))
{//后序遍历
	if (T)
	{
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T->data);
	}
}

Status BiTreeEmpty(BiTree T)
{
	if (T)
		return FALSE; //这里不加分号！！！
	else
		return TRUE;
}

int BiTreeDepth(BiTree T)
{
	int i, j;
	if (!T)
		return 0;
	i = BiTreeDepth(T->lchild);//i为左子树的深度
	j = BiTreeDepth(T->rchild);//右子树深度
	return i > j ? i + 1 : j + 1;
}

TElemType Root(BiTree T)
{
	if (BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

TElemType Value(BiTree p)
{
	return p->data;
}

void Assign(BiTree p, TElemType value)
{
	p->data = value;
}

BiTree Point(BiTree T, TElemType s)
{//返回二叉树中指向元素值为s的结点的指针
	LinkQueue_H q;
	QElemType a;
	if (T)//T非空
	{
		InitQueue_L(q);
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, a);//出队,队列元素赋给a
			if (a->data == s)//a所指结点值为s
			{
				DestoryQueue_L(q);
				return a;
			}
			if (a->lchild)
				EnQueue_L(q, a->lchild);//入队左孩子
			if (a->rchild)
				EnQueue_L(q, a->rchild);//入队右孩子
		}
		DestoryQueue_L(q);//销毁队列
	}
	return nullptr;
}

TElemType LeftChild(BiTree T, TElemType e)
{//返回T的左孩子
	BiTree a;
	if (T)
	{
		a = Point(T, e);
		if (a && a->lchild)//如果T存在结点e，且其左孩子存在
		{
			return a->lchild->data;
		}
	}
	return Nil;
}

TElemType RightChild(BiTree T, TElemType e)
{
	BiTree a;
	if (T)
	{
		a = Point(T, e);
		if (a && a->rchild)//如果T存在结点e，且其右孩子存在
		{
			return a->rchild->data;
		}
	}
	return Nil;
}

Status DeleteChild(BiTree p, int LR)
{
	if (p)
	{
		if (LR == 0)//删除左子树
			ClearBiTree(p->lchild);
		else if (LR == 1)
			ClearBiTree(p->rchild);
		return OK;
	}
}

void LevleOrderTraverse(BiTree T, void(*visit)(TElemType))
{//层序递归遍历T(利用队列)，对每个结点调用一次visit
	LinkQueue_H q;
	QElemType a;
	if (T)
	{
		InitQueue_L(q);
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, a);
			visit(a->data);
			if (a->lchild != nullptr)
				EnQueue_L(q, a->lchild);
			if (a->rchild != nullptr)
				EnQueue_L(q, a->rchild);
		}
		printf("\n");
		DestoryQueue_L(q);
	}
}

void CreateBiTree(BiTree & T)
{//按先序输入二叉树中的值(可为字符型或整型)
	//构造二叉链表表示的二叉树T.Nil表示空(子)树
	TElemType ch;
	scanf(form, &ch);
	if (ch == Nil)
		T = nullptr;
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));//根结点
		if (!T)
			exit(OVERFLOW);
		T->data = ch;//将值赋予根结点
		CreateBiTree(T->lchild);//递归的构造左子树
		CreateBiTree(T->rchild);//递归的构造右子树
	}
}

TElemType Parent(BiTree T, TElemType e)
{//若e是T的非根结点，则返回它的双亲，否则返回"空"
	LinkQueue_H q;
	QElemType a;
	if (T)//T非空
	{
		InitQueue_L(q);
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, a);
			if (a->lchild && a->lchild->data == e || a->rchild && a->rchild->data == e)
				return a->data;//返回e的双亲
			else
			{
				if (a->lchild)
					EnQueue_L(q, a->lchild);
				if (a->rchild)
					EnQueue_L(q, a->rchild);
			}

		}
	}
	return Nil;
}

TElemType LeftSibling(BiTree T, TElemType e)
{//返回e的左兄弟。若e是T的左孩子或无左兄弟，则返回0
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T, e);
		if (a != Nil)
		{
			p = Point(T, a);
			if (p->lchild && p->rchild && p->rchild->data == e)//p存在左右孩子且右孩子是e
				return p->lchild->data;//返回p的左孩子(e的左兄弟)
		}
	}
	return Nil; //其余情况
}

TElemType RightSibling(BiTree T, TElemType e)
{//返回e的右兄弟。若e是T的右孩子或无右兄弟，则返回0
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T, e);
		if (a != Nil)
		{
			p = Point(T, a);
			if (p->lchild && p->rchild && p->lchild->data == e)//p存在左右孩子且右孩子是e
				return p->rchild->data;//返回p的右孩子(e的右兄弟)
		}
	}
	return Nil; //其余情况
}

Status InsertChild(BiTree p, int LR, BiTree c)
{//根据LR为0或1，插入c为T中p所指结点的左或右子树。
	//非空二叉树c与T不相交且右子树为空
	if (p)
	{
		if (LR == 0)
		{
			c->rchild = p->lchild; //p所指结点的原有左子树成为c的右子树
			p->lchild = c;
		}
		else
		{
			c->rchild = p->rchild;
			p->rchild = c;
		}
		return OK;
	}
	return ERROR;
}

void InOrderTraverse_NRecursion1(BiTree T, void(*visit)(TElemType))
{//使用栈的非递归中序遍历二叉树
	SqStack_H s;
	SqStack_H & S = s;
	BiTree &T_R = T;
	InitStack(S);
	while (T || !StackEmpty(s))
	{
		if (T)
		{
			Push(S, T);//根结点入栈
			T = T->lchild;//T指向其左子树
	    }
		else
		{
			Pop(S, T_R);
			visit(T->data);
			T = T->rchild;
		}
	}
	printf("\n");
	DestroyStack(S);//销毁栈
}

void InOrderTraverse_NRecursion2(BiTree T, void(*visit)(TElemType))
{
	SqStack_H s = {nullptr, nullptr, 0};
	SqStack_H &S = s;
	BiTree p;
	InitStack(S);
	Push(S, T);
	while (!StackEmpty(s))
	{
		while (GetTop(S, p) && p)
			Push(S, p->lchild);//向左走向尽头，入栈左孩子指针
		Pop(S, p);
		if (!StackEmpty(s))//访问结点，向右一步
		{
			Pop(S, p);
			visit(p->data);
			Push(S, p->rchild);
		}
	}
}
