/*          ��������������
 *______________________________________
 *|lchild | LTag | data | RTag | rchild| 

 * LTag = 0 lchild��ָʾ��������
 *        1 lchild��ָʾ����ǰ��

 * RTag = 0 rchild��ָʾ�����Һ���
 *        1 rchild��ָʾ����ǰ��
 */
#pragma once
#include "tree.h"

/*
 *  ���������洢��ʾ
 */
typedef enum PointerTag{Link, Thread}; //Link==0:ָ�� Thread==1:����
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild, *rchild; //���Һ���ָ��
	PointerTag LTag, RTag; //���ұ�־
}BiThrNode, *BiThrTree;

//�������Ա�Ĵ洢�ṹ���ڶ��������������������ͷ���
//lchildָ��������ĸ����
//rchildָ���������ʱ���ʵ����һ�����

//����������ĵ�һ������lchild�����һ��rchildָ��ͷ���
//(�ȿ��Դӵ�һ�����˳��̽��б�����Ҳ���Դ����һ�������˳ǰ������)
extern BiThrTree pre;
Status InOrderThreading_Thr(BiThrTree T, Status(*visit)(TElemType e));
Status InOrderThreading(BiThrTree & Thrt, BiThrTree T);
void InThreading(BiThrTree p);