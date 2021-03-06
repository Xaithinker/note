// array.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

#include "array.h"

int main()
{
	Array A;
	int i, j, k, dim = 3, bound1 = 3, bound2 = 4, bound3 = 2;//A[3][4][2]数组
	ElemType e;
	InitArray(A, dim, bound1, bound2, bound3);
	printf("A.bounds is =");
	for (i = 0; i < dim; ++i)
		printf("%d", *(A.bounds + i));
	printf("\nA.constants=");
	for (i = 0; i < dim; ++i)
		printf("%d", *(A.constants + i));
	printf("\n%d页%d行%d列矩阵如下:\n", bound1, bound2, bound3);
	for (i = 0; i < bound1; ++i)
	{
		for (j = 0; j < bound2; ++j)
		{
			for (k = 0; k < bound3; ++k)
			{
				Assign(A, i * 100 + j * 10 + k, i, j, k);//将ix100+jx10+k 赋值给A[i][j][k]
				Value(e, A, i, j, k);//将A[i][j][k]赋值给e
				printf("A[%d][%d][%d]= %2d  ", i, j, k, e);//输出A[i][j][k]
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("A.base = \n");
	for (i = 0; i < bound1 * bound2 * bound3; ++i)
	{
		printf("%4d", *(A.base + i));
		if (i % (bound2 * bound3) == bound2 * bound3 - 1)
			printf("\n");
	}
	printf("A.dim = %d\n", A.dim);
	DestoryArray(A);
	system("pause");
}
