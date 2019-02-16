/*
 * This is for implementation of array.h
 * edited by xzju @ 9.19.2018
 *
 */
#include "pch.h"

#include "array.h"

Status InitArray(Array &A, int dim, ...)
{
	int elemtotal = 1, i; //elemtotal 是数组元素总数，初值为1(累乘器)为计算各存储位置
	va_list ap; //变长数组表类型
	if (dim < 1 || dim > MAX_ARRAY_DIM)
		return ERROR;
	A.dim = dim; //数组维数
	A.bounds = (int *)malloc(dim * sizeof(int));
	if (!A.bounds)
		exit(OVERFLOW);
	va_start(ap, dim); //变长参数"..."从形参dim之后开始
	for (i = 0; i < dim; i++)
	{
		A.bounds[i] = va_arg(ap, int);
		if (A.bounds < 0)
			return UNDERFLOW;//math.h中定义为4
		elemtotal *= A.bounds[i];//数组元素总数 = 各维长度乘积
	}
	va_end(ap); //结束提取变长参数
	A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if (!A.base)
		exit(OVERFLOW);
	A.constants = (int *)malloc(dim * sizeof(int));
	if (!A.constants)
		exit(OVERFLOW);
	A.constants[dim - 1] = 1;//最后一维的偏移量为1
	for (i = dim - 2; i >= 0; --i)//进行每一维的偏移量常数计算
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
{//若ap 指向各下表合法值，则求出该元素在Array中的相对地址off
	int i, ind;
	off = 0;
	for (i = 0; i < A.dim; ++i)
	{
		ind = va_arg(ap, int);//逐一读取各维下标值
		if (ind < 0 || ind > A.bounds[i])//各维下标值不合法
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