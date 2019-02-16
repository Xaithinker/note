/**
 * 本题要求实现一个函数，求链式表的表长。
 * 函数接口定义：
 * int Length( List L );
 * 其中List结构定义如下：
 * typedef struct LNode *PtrToLNode;
 * struct LNode {
 *     ElementType Data;
 *     PtrToLNode Next;
 * };
 * typedef PtrToLNode List;
 * L是给定单链表，函数Length要返回链式表的长度。
 * 
 **/


#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;

List Read(); /* 细节在此不表 */

int Length( List L );

int main()
{
    List L = Read();
    printf("%d\n", Length(L));
    return 0;
}

/* 你的代码将被嵌在这里 */
int Length(List L)
{
  int counter = 0;
  while(L != NULL)
  {
    counter++;
    L = L->Next;
  }
  return counter;
}