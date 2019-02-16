/*
 * �������Ķ�����������������ӿ�
 */
/*
 * ��������˳��洢�����ڵ�洢��[0]
 * ��i��������(����-1)Ϊ��2^(i-1) -1 �� 2^i - 2
 * ���Ϊj�Ľ�����������iΪ |_log2(j+1)_| - 1
 * �ڲ�i�е�����ΪK = j - 2^(i-1) + 2
 * ˫�����|_j-1 / 2_|,����2j+1,�Һ���2j+2
 */
 /*
 * ��������˳��洢�����ڵ�洢��[1]
 * ��i��������Ϊ��2^(i-1) �� 2^i - 1
 * ���Ϊj�Ľ�����������iΪ |_log2(j)_| - 1
 * �ڲ�i�е�����ΪK = j - 2^(i-1) + 1
 * ˫�����|_j / 2_|,����2j,�Һ���2j+1
 */
#pragma once

#include "tree.h"
#include "queue.h"
#include "stack.h"

//���еĺ���ʹ��
#undef ENABLE_SQUEUE_HEAP
//#define ENABLE_LINKQUEUE
#undef ENABLE_CYCLICQUEUE_HEAP

//ջ�ĺ�����ʹ��
//#define ENABLE_SQSTACK_HEAP
#undef ENABLE_SQSTACK_ARRARY
#undef ENABLE_LINKSTACK


/*
 * �����ʽ�洢
 * ����ͷ��㣬ֱ��ָ�����㼴��(����һ��Ԫ��root)
 */
typedef struct BinaryTreeNode
{
	TElemType data;
	BinaryTreeNode *lchild;
	BinaryTreeNode *rchild;//���Һ���
}BiTNode,  * BiTree;

typedef BiTree QElemType; //���� ����Ԫ�� Ϊ������ָ������
typedef BiTree SElemType; //���� ջԪ�� Ϊ��������ָ������

#define InOrderTraverse_NR1 InOrderTraverse_NRecursion1  
#define InOrderTraverse_NR2 InOrderTraverse_NRecursion1  
/*
 * ����������������
 * ��������Ĵ洢�ṹ�������������������˵ݹ麯��
 */

#define ClearBiTree DestroyBiTree //��ն����������ٶ���������һ��

void InitBiTree(BiTree & T);
void DestroyBiTree(BiTree & T);
void PreOrderTraverse(BiTree T, void(*visit)(TElemType));
void InOrderTraverse(BiTree T, void(*visit)(TElemType));
void PostOrderTraverse(BiTree T, void(*visit)(TElemType));

//(�洢�ṹ�����������)������������
Status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
TElemType Root(BiTree T);
TElemType Value(BiTree p);
void Assign(BiTree p, TElemType value);
Status DeleteChild(BiTree p, int LR);
void CreateBiTree(BiTree &T);
Status InsertChild(BiTree p, int LR, BiTree e);//�β�T����

//ʹ�ö��еĺ���
void LevleOrderTraverse(BiTree T, void(*visit)(TElemType));
BiTree Point(BiTree T, TElemType s);
TElemType LeftChild(BiTree T, TElemType e);
TElemType RightChild(BiTree T, TElemType e);
TElemType Parent(BiTree T, TElemType e);
TElemType LeftSibling(BiTree T, TElemType e);
TElemType RightSibling(BiTree T, TElemType e);

//ʹ��ջ�ĺ���
void InOrderTraverse_NRecursion1(BiTree T, void(*visit)(TElemType));
void InOrderTraverse_NRecursion2(BiTree T, void(*visit)(TElemType));
