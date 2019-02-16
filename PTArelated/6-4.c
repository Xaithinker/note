/**
 * 本题要求实现一个函数，找到并返回链式表的第K个元素。
 * 函数接口定义：
 * ElementType FindKth( List L, int K );
 * 其中List结构定义如下：
 * typedef struct LNode *PtrToLNode;
 * struct LNode {
 *     ElementType Data;
 *     PtrToLNode Next;
 * };
 * typedef PtrToLNode List;
 * 
 * L是给定单链表，函数FindKth要返回链式表的第K个元素。如果该元素不存在，则返回ERROR。
 * 
 **/


#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;

List Read(); /* 细节在此不表 */

ElementType FindKth( List L, int K );

int main()
{
    int N, K;
    ElementType X;
    List L = Read();
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &K);
        X = FindKth(L, K);
        if ( X!= ERROR )
            printf("%d ", X);
        else
            printf("NA ");
    }
    return 0;
}

/* 你的代码将被嵌在这里 */

ElementType FindKth( List L, int K )
{
  int counter = 0;
  while(L != NULL)
  {
    counter++;
    if(counter == K)
    {
      return L->Data;
    }
    L = L->Next;
  }
  return ERROR;
}