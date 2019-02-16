#pragma once
/*
 * This is the header of array
 */

#include "globaldefined.h"

#define MAX_ARRAY_DIM 8
typedef struct array
{
	ElemType * base;
	int dim;  //数组维数
	int * bounds; //数组维界地址
	int * constants; //数组映像函数常量基址
}Array;


/*
 * Functions defined HERE
 */
Status InitArray(Array &A, int dim, ...);
void DestoryArray(Array &A);
Status Locate(Array &A, va_list ap, int &off);
Status Value(ElemType &e, Array A, ...);
Status Assign(Array A, ElemType e, ...);

/*
 * This is for different arrays.
 * such as sparse array, 
 * defined in another header
 */