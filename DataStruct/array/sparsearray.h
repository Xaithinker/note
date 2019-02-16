#pragma once

#include "globaldefined.h"

#define MAX_SIZE 100
typedef struct SparseTripe
{
	int i, j; //�洢ϡ���������
	ElemType e; //����Ԫ��ֵ
}Tripe;

typedef struct TripleSparseMatrix
{
	Tripe data[MAX_SIZE + 1];//������Ԫ���ÿһ������Ԫ����һ����Ԫ���ʾ��data[0]δ��
	int mu, nu, tu; //�ֱ��ʾ���������������������Ԫ����
}TSMatrix;

int comp(int c1, int c2)
{
	if (c1 < c2)
		return -1;
	if (c1 = c2)
		return 0;
	return 1;
}

/*
 * Function defined HERE
 */
Status CreateSMatrix(TSMatrix &M);
void DestorySMatrix(TSMatrix &M);
void PrintSMatrix(TSMatrix M);
void CopySMatrix(TSMatrix M, TSMatrix &T);
Status SubSmatrix(TSMatrix M, TSMatrix N, TSMatrix &Q);
Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q);
void TransposeSMatrix(TSMatrix M, TSMatrix &T);
Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q);