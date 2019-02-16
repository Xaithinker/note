/*
 * This is for implementation of array.h
 * edited by xzju @ 9.19.2018
 *
 */
#include "pch.h"

#include "array.h"

Status InitArray(Array &A, int dim, ...)
{
	int elemtotal = 1, i; //elemtotal ������Ԫ����������ֵΪ1(�۳���)Ϊ������洢λ��
	va_list ap; //�䳤���������
	if (dim < 1 || dim > MAX_ARRAY_DIM)
		return ERROR;
	A.dim = dim; //����ά��
	A.bounds = (int *)malloc(dim * sizeof(int));
	if (!A.bounds)
		exit(OVERFLOW);
	va_start(ap, dim); //�䳤����"..."���β�dim֮��ʼ
	for (i = 0; i < dim; i++)
	{
		A.bounds[i] = va_arg(ap, int);
		if (A.bounds < 0)
			return UNDERFLOW;//math.h�ж���Ϊ4
		elemtotal *= A.bounds[i];//����Ԫ������ = ��ά���ȳ˻�
	}
	va_end(ap); //������ȡ�䳤����
	A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if (!A.base)
		exit(OVERFLOW);
	A.constants = (int *)malloc(dim * sizeof(int));
	if (!A.constants)
		exit(OVERFLOW);
	A.constants[dim - 1] = 1;//���һά��ƫ����Ϊ1
	for (i = dim - 2; i >= 0; --i)//����ÿһά��ƫ������������
		A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
	echo(InitArray);
	return OK;
}

void DestoryArray(Array & A)
{
	if (A.base)
		free(A.base);
	if (A.bounds)
		free(A.bounds);
	if (A.constants)
		free(A.constants);
	A.base = A.bounds = A.constants = nullptr;
	A.dim = 0;
}

Status Locate(Array & A, va_list ap, int & off)
{//��ap ָ����±�Ϸ�ֵ���������Ԫ����Array�е���Ե�ַoff
	int i, ind;
	off = 0;
	for (i = 0; i < A.dim; ++i)
	{
		ind = va_arg(ap, int);//��һ��ȡ��ά�±�ֵ
		if (ind < 0 || ind > A.bounds[i])//��ά�±�ֵ���Ϸ�
			return OVERFLOW;
		off += A.constants[i] * ind;
	}
	echo(Locate);
	return OK;
}

Status Value(ElemType &e, Array A, ...)
{
	va_list ap;
	int off;
	va_start(ap, A);
	if (Locate(A, ap, off) == OVERFLOW)
		return ERROR;
	e = *(A.base + off);
	echo(Value);
	return OK;
}

Status Assign(Array A, ElemType e, ...)
{
	va_list ap;
	int off;
	va_start(ap, e);
	if (Locate(A, ap, off) == OVERFLOW)
		return ERROR;
	*(A.base + off) = e;
	echo(Assign);
	return OK;
}