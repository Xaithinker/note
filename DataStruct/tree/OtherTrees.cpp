#include "pch.h"
#include "OtherTrees.h"

void InitTree(CSTree & T)
{
	T = nullptr; //�������
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
	char c[20];//��ʱ��ź��ӽ��
	CSTree p, p1;
	LinkQueue_H q;
	int i, m;
	InitQueue_L(q);
	printf("����������(�ַ���,#Ϊ��)��");
	scanf("%c% * c", &c[0]); //���������ֵ
	if (c[0] != Nil)//�ǿ���
	{
		T = (CSTree)malloc(sizeof(CSNode));
		T->data = c[0];
		T->nextsibing = nullptr;
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, p);//���ӵ�һ����ָ��
			printf("�밴����˳�������� %c �����к��ӣ�", p->data);
			gets_s(c);//���������к�����Ϊ�ַ���������
			m = strlen(c);
			if (m > 0)//�к���
			{
				p1 = p->firstchild = (CSTree)malloc(sizeof(CSNode));//�������ӽ��
				p1->data = c[0];
				EnQueue_L(q, p1);//���p1����ָ��
				for (i = 1; i < m; i++)//������֮�����������
				{
					p1->nextsibing = (CSTree)malloc(sizeof(CSNode));//������һ���ֵܽ��
					p1 = p1->nextsibing;
					p1->data = c[i];
					EnQueue_L(q, p1);
				}
				p1->nextsibing = nullptr;//���һ�����û����һ���ֵ�
			}
			else
				p->firstchild = nullptr; //����ָ��Ϊ��
		}
	}
	else
		T = nullptr; //����
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
	return max + 1; //������� = ������� + 1
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
{//���ض���������ָ��Ԫ��Ϊs�Ľ���ָ��
	LinkQueue_H q;
	QElemType a;
	if (T)
	{
		InitQueue_L(q);
		EnQueue_L(q, T);
		while (!QueueEmpty_L(q))
		{
			DeQueue_L(q, a); //����
			if (a->data == s)
				return a;
			if (a->firstchild)//�г���
				EnQueue_L(q, a->firstchild);
			if (a->nextsibing)
				EnQueue_L(q, a->nextsibing);//�����һ���ֵ�
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
	return ERROR;//��δ�ҵ����
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
			DeQueue_L(q, p);//����Ԫ�أ�ָ�룩��ֵp
			if (p->firstchild->data == cur_e)//p�г���
			{
				return Value(p); //����˫�׵�ֵ
				t = p;//˫��ָ�븳ֵt
				p = p->firstchild;//pָ����
				EnQueue_L(q, p);
				while (p->nextsibing) //����һ���ֵ�
				{
					if (Value(p) == cur_e)
						return Value(t);//˫��ֵ
					EnQueue_L(q, p);
				}
			}
		}
	}
	return Nil;
}
