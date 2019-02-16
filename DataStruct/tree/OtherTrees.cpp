#include "pch.h"
#include "OtherTrees.h"

void InitTree(CSTree & T)
{
	T = nullptr; //构造空树
}

void DestroyTree(CSTree & T)
{
	if (T)
	{
		DestroyTree(T->firstchild);
		DestroyTree(T->nextsibing);
		free(T);
		T = nullptr;
	}
}

void CreateTree(CSTree T)
{
	char c[20];//临时存放孩子结点
	CSTree p, p1;
	LinkQueue_H q;
	int i, m;
	InitQueue_L(q);
	printf("请输入根结点(字符型,#为空)：");
	scanf("%c% * c", &c[0]); //输入根结点的值
	if (c[0] != Nil)//非空树
	{
		T = (CSTree)malloc(sizeof(CSNode));
		T->data = c[0];
		T->nextsibing = nullptr;
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, p);//出队第一结点的指针
			printf("请按长幼顺序输入结点 %c 的所有孩子：", p->data);
			gets_s(c);//将结点的所有孩子作为字符串的输入
			m = strlen(c);
			if (m > 0)//有孩子
			{
				p1 = p->firstchild = (CSTree)malloc(sizeof(CSNode));//建立长子结点
				p1->data = c[0];
				EnQueue_L(q, p1);//入队p1结点的指针
				for (i = 1; i < m; i++)//除长子之外的其他孩子
				{
					p1->nextsibing = (CSTree)malloc(sizeof(CSNode));//建立下一个兄弟结点
					p1 = p1->nextsibing;
					p1->data = c[i];
					EnQueue_L(q, p1);
				}
				p1->nextsibing = nullptr;//最后一个结点没有下一个兄弟
			}
			else
				p->firstchild = nullptr; //长子指针为空
		}
	}
	else
		T = nullptr; //空树
}

Status TreeEmpty(CSTree T)
{
	if (T)
		return FALSE;
	else
		return TRUE;
}

int TreeDepth(CSTree T)
{
	CSTree p = T->firstchild;
	int depth, max = 0;
	if (!T)
		return 0;
	for (; p; p = p->nextsibing)
	{
		depth = TreeDepth(p);
		if (depth > max)
			max = depth;
	}
	return max + 1; //树的深度 = 子树深度 + 1
	return 0;
}

TElemType Value(CSTree p)
{
	return p->data;
}

TElemType Root(CSTree T)
{
	if (T)
		return Value(T);
	else
		return Nil;
}

CSTree Point(CSTree T, TElemType s)
{//返回二叉链表中指向元素为s的结点的指针
	LinkQueue_H q;
	QElemType a;
	if (T)
	{
		InitQueue_L(q);
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, a); //出队
			if (a->data == s)
				return a;
			if (a->firstchild)//有长子
				EnQueue_L(q, a->firstchild);
			if (a->nextsibing)
				EnQueue_L(q, a->nextsibing);//入队下一个兄弟
		}
	}
	return nullptr;
}

Status Assign(CSTree & T, TElemType cur_e, TElemType value)
{
	CSTree p;
	if (T)
	{
		p = Point(T, cur_e);
		if (p)
		{
			p->data = value;
			return OK;
		}
	}
	return ERROR;//树未找到或空
}

TElemType Parent(CSTree T, TElemType cur_e)
{
	CSTree p, t;
	LinkQueue_H q;
	InitQueue_L(q);
	if (T)
	{
		if (Value(T) == cur_e)
			return Nil;
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, p);//出队元素（指针）赋值p
			if (p->firstchild->data == cur_e)//p有长子
			{
				return Value(p); //返回双亲的值
				t = p;//双亲指针赋值t
				p = p->firstchild;//p指向长子
				EnQueue_L(q, p);
				while (p->nextsibing) //有下一个兄弟
				{
					if (Value(p) == cur_e)
						return Value(t);//双亲值
					EnQueue_L(q, p);
				}
			}
		}
	}
	return Nil;
}
