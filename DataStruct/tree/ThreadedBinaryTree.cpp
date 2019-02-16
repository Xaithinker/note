#include "pch.h"
#include "ThreadedBinaryTree.h"

Status InOrderThreading_Thr(BiThrTree T, Status(*visit)(TElemType e))
{//Tָ��ͷ��㣬lchildָ������
	//�����������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���visit
	BiThrTree p = T->lchild;//pָ������
	while (p != T)
	{
		while (p->LTag == Link)
			p = p->lchild;
		if (!visit(p->data))
			return ERROR;  //������������Ϊ�յĽ��
		while (p->RTag == Thread && p->lchild != T)//ͨ����̿��Է���Ŀ��ٶ�λ������Ҫ���ʵĽ��
		{
			p = p->rchild;
			visit(p->data); //���ʺ�̽��
		}
		p = p->rchild;//��λ�������ĸ���㼴�ɣ�ѭ���Դ˿�ʼ
	}
	return OK;
}

Status InOrderThreading(BiThrTree & Thrt, BiThrTree T)
{//�������������T,������������������Thrtָ��ͷ���
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));//ͷ���
	if (!Thrt)
		exit(OVERFLOW);
	Thrt->LTag = Link;//ָ��ͷ��� ö�����͵ĳ�Աֱ�ӷ��ʡ�Ϊconst value,һ�����岻�ɸ��ġ�
	Thrt->RTag = Thread;//ָ�����һ�����
	if (!T)
		Thrt->lchild = Thrt;//������ָ���Լ�
	else
	{
		Thrt->lchild = T;
		pre = Thrt; //������ʱ����
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;//���һ�����������
		Thrt->rchild = pre;
	}
	return OK;
}

void InThreading(BiThrTree p)
{
	if (p)
	{
		InThreading(p->lchild); //������������
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}//ǰ������
		if (!pre->lchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}//�������
		pre = p;
		InThreading(p->rchild);
	}
}
