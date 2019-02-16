/*
 * ������������������ʵ��
 */
#include "pch.h"

#include "BinaryTree.h"

void InitBiTree(BiTree & T)
{//����ն�����
	T = nullptr;
}

void DestroyBiTree(BiTree & T)
{
	if (T)
	{//�����ĵ�ַ��T,Tָ������
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);//�ͷŸ��ڵ�
		T = nullptr;
	}
}

void PreOrderTraverse(BiTree T, void(* visit)(TElemType))
{//����ݹ��������ÿ��������Visitһ��
	if (T)
	{
		visit(T->data);//�ȷ��ʸ����
		PreOrderTraverse(T->lchild, visit);//��������
		PreOrderTraverse(T->rchild, visit);//��������
	}

}

void InOrderTraverse(BiTree T, void(*visit)(TElemType))
{//����ݹ����
	if (T)
	{
		InOrderTraverse(T->lchild, visit);//���������������
		visit(T->data);//�ڷ��ʸ����
		InOrderTraverse(T->rchild, visit);//����������������
	}
}

void PostOrderTraverse(BiTree T, void(*visit)(TElemType))
{//�������
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
		return FALSE; //���ﲻ�ӷֺţ�����
	else
		return TRUE;
}

int BiTreeDepth(BiTree T)
{
	int i, j;
	if (!T)
		return 0;
	i = BiTreeDepth(T->lchild);//iΪ�����������
	j = BiTreeDepth(T->rchild);//���������
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
{//���ض�������ָ��Ԫ��ֵΪs�Ľ���ָ��
	LinkQueue_H q;
	QElemType a;
	if (T)//T�ǿ�
	{
		InitQueue_L(q);
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, a);//����,����Ԫ�ظ���a
			if (a->data == s)//a��ָ���ֵΪs
			{
				DestoryQueue_L(q);
				return a;
			}
			if (a->lchild)
				EnQueue_L(q, a->lchild);//�������
			if (a->rchild)
				EnQueue_L(q, a->rchild);//����Һ���
		}
		DestoryQueue_L(q);//���ٶ���
	}
	return nullptr;
}

TElemType LeftChild(BiTree T, TElemType e)
{//����T������
	BiTree a;
	if (T)
	{
		a = Point(T, e);
		if (a && a->lchild)//���T���ڽ��e���������Ӵ���
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
		if (a && a->rchild)//���T���ڽ��e�������Һ��Ӵ���
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
		if (LR == 0)//ɾ��������
			ClearBiTree(p->lchild);
		else if (LR == 1)
			ClearBiTree(p->rchild);
		return OK;
	}
}

void LevleOrderTraverse(BiTree T, void(*visit)(TElemType))
{//����ݹ����T(���ö���)����ÿ��������һ��visit
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
{//����������������е�ֵ(��Ϊ�ַ��ͻ�����)
	//������������ʾ�Ķ�����T.Nil��ʾ��(��)��
	TElemType ch;
	scanf(form, &ch);
	if (ch == Nil)
		T = nullptr;
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));//�����
		if (!T)
			exit(OVERFLOW);
		T->data = ch;//��ֵ��������
		CreateBiTree(T->lchild);//�ݹ�Ĺ���������
		CreateBiTree(T->rchild);//�ݹ�Ĺ���������
	}
}

TElemType Parent(BiTree T, TElemType e)
{//��e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻�"��"
	LinkQueue_H q;
	QElemType a;
	if (T)//T�ǿ�
	{
		InitQueue_L(q);
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, a);
			if (a->lchild && a->lchild->data == e || a->rchild && a->rchild->data == e)
				return a->data;//����e��˫��
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
{//����e�����ֵܡ���e��T�����ӻ������ֵܣ��򷵻�0
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T, e);
		if (a != Nil)
		{
			p = Point(T, a);
			if (p->lchild && p->rchild && p->rchild->data == e)//p�������Һ������Һ�����e
				return p->lchild->data;//����p������(e�����ֵ�)
		}
	}
	return Nil; //�������
}

TElemType RightSibling(BiTree T, TElemType e)
{//����e�����ֵܡ���e��T���Һ��ӻ������ֵܣ��򷵻�0
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T, e);
		if (a != Nil)
		{
			p = Point(T, a);
			if (p->lchild && p->rchild && p->lchild->data == e)//p�������Һ������Һ�����e
				return p->rchild->data;//����p���Һ���(e�����ֵ�)
		}
	}
	return Nil; //�������
}

Status InsertChild(BiTree p, int LR, BiTree c)
{//����LRΪ0��1������cΪT��p��ָ���������������
	//�ǿն�����c��T���ཻ��������Ϊ��
	if (p)
	{
		if (LR == 0)
		{
			c->rchild = p->lchild; //p��ָ����ԭ����������Ϊc��������
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
{//ʹ��ջ�ķǵݹ��������������
	SqStack_H s;
	SqStack_H & S = s;
	BiTree &T_R = T;
	InitStack(S);
	while (T || !StackEmpty(s))
	{
		if (T)
		{
			Push(S, T);//�������ջ
			T = T->lchild;//Tָ����������
	    }
		else
		{
			Pop(S, T_R);
			visit(T->data);
			T = T->rchild;
		}
	}
	printf("\n");
	DestroyStack(S);//����ջ
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
			Push(S, p->lchild);//��������ͷ����ջ����ָ��
		Pop(S, p);
		if (!StackEmpty(s))//���ʽ�㣬����һ��
		{
			Pop(S, p);
			visit(p->data);
			Push(S, p->rchild);
		}
	}
}
