/**
 * 本题要求实现一个函数，将给定的单链表逆转
 * 接口定义: 
 * List Reverse( List L );
 * typedef struct Node *PtrToNode;
 * struct Node {
 *      ElementType Data;  存储结点数据 
 *      PtrToNode   Next;  指向下一个结点的指针 
 *  };
 *  typedef PtrToNode List;  定义单链表类型 
 * 
 **/


#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表 */

List Reverse( List L );
int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Reverse(List L)
{
	List temp = NULL, p = NULL;
	while (L)
	{
		p = L->Next;
		L->Next = temp;
		temp = L;
		L = p;
	}
	return temp;
}
