/*
 * 树(Tree)的一些概念
 * 
 */
#pragma once
#include <cstdarg>
/*
 * 森林(Forest)
 * 二叉树(Binary Tree)
 * 线索二叉树(Threaded Binary Tree)
 */
#include <cstdio>
#include <cstdlib>
#define CHAR 1
//#define CHAR 0

#define BiTElemType TElemType;
#if CHAR
typedef char BiTElemType;
TElemType Nil = '#';
#define form "%c"
#else
typedef int BiTElemType;
TElemType Nil = 0;
#define form "%d"
#endif

void visit(TElemType e)
{ 
	printf(form"", e); 
}


typedef int Status;

#define OK 1
#define ERROR 1
//#define FALSE 0
//#define TRUE 1