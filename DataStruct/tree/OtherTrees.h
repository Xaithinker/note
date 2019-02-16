#pragma once
#include "tree.h"

/* 
 * ˫�ױ�ʾ��
 * ʹ�������ʾ
 */
#define MAX_TREE_SIZE 100
typedef struct PTNode  //���ṹ
{
	TElemType data;
	int parent;//˫��λ����
}PTNode;
typedef struct //���Ľṹ
{
	PTNode nodes[MAX_TREE_SIZE];
	int r, n; //����λ�úͽ����
}PTree;

/*
 * ���ĺ�������洢��ʾ
 */
typedef struct CTNode //���ӽ��
{
	int child;
	struct CTNode * next;
}*ChildPtr;

typedef struct
{
	TElemType data;
	ChildPtr firstchild; //��������ͷָ��
}CTBox;

typedef struct
{
	CTBox nodes[MAX_TREE_SIZE]; 
	int n, r; //������͸���λ��
}CTree;

/*
 * ���Ķ�������(����-�ֵ�)�洢��ʾ
 *
 */
typedef struct CSNode
{
	TElemType data;
	struct CSNode *firstchild, *nextsibing; //�ý��ĵ�һ�����ӽ�����һ���ֵܽ��
}CSNode, *CSTree;

// ����-�ֵܴ洢��������
#define ClearTree DestroyTree //���߲�����ͬ
void InitTree(CSTree &T);
void DestroyTree(CSTree &T);

typedef CSTree QElemType; //�������Ԫ��Ϊ����-�ֵܶ��������ָ������
#include "queue.h"
#undef ENABLE_SQUEUE_HEAP //ʹ��������
#undef ENABLE_CYCLICQUEUE_HEAP

void CreateTree(CSTree T);
Status TreeEmpty(CSTree T);
int TreeDepth(CSTree T);
TElemType Value(CSTree p);
TElemType Root(CSTree T);
CSTree Point(CSTree T, TElemType s);
Status Assign(CSTree &T, TElemType cur_e, TElemType value);
TElemType Parent(CSTree T, TElemType cur_e);