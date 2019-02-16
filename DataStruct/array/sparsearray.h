#pragma once

#include "globaldefined.h"

#define MAX_SIZE 100
typedef struct SparseTripe
{
	int i, j; //存储稀疏矩阵行列
	ElemType e; //非零元素值
}Tripe;

typedef struct TripleSparseMatrix
{
	Tripe data[MAX_SIZE + 1];//非零三元组表，每一个非零元素用一个三元组表示，data[0]未用
	int mu, nu, tu; //分别表示矩阵的行数，列数，非零元个数
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