/**
 * 本题要求实现链式表的操作集。
 * 函数接口定义：
 * Position Find( List L, ElementType X );
 * List Insert( List L, ElementType X, Position P );
 * List Delete( List L, Position P );
 * 其中List结构定义如下：
 * typedef struct LNode *PtrToLNode;
 * struct LNode {
 *     ElementType Data;
 *     PtrToLNode Next;
 * };
 * typedef PtrToLNode Position;
 * typedef PtrToLNode List;
 * 
 * Position Find( List L, ElementType X )：返回线性表中首次出现X的位置。若找不到则返回ERROR；
 * List Insert( List L, ElementType X, Position P )：将X插入在位置P指向的结点之前，返回链表的表头。如果参数P指向非法位置，则打印“Wrong Position for Insertion”，返回ERROR；
 * List Delete( List L, Position P )：将位置P的元素删除并返回链表的表头。若参数P指向非法位置，则打印“Wrong Position for Deletion”并返回ERROR。
 * 
 **/

#include <stdio.h>
#include <stdlib.h>

#define ERROR NULL
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

Position Find( List L, ElementType X );
List Insert( List L, ElementType X, Position P );
List Delete( List L, Position P );

int main()
{
    List L;
    ElementType X;
    Position P, tmp;
    int N;

    L = NULL;
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        L = Insert(L, X, L);
        if ( L==ERROR ) printf("Wrong Answer\n");
    }
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        P = Find(L, X);
        if ( P == ERROR )
            printf("Finding Error: %d is not in.\n", X);
        else {
            L = Delete(L, P);
            printf("%d is found and deleted.\n", X);
            if ( L==ERROR )
                printf("Wrong Answer or Empty List.\n");
        }
    }
    L = Insert(L, X, NULL);
    if ( L==ERROR ) printf("Wrong Answer\n");
    else
        printf("%d is inserted as the last element.\n", X);
    P = (Position)malloc(sizeof(struct LNode));
    tmp = Insert(L, X, P);
    if ( tmp!=ERROR ) printf("Wrong Answer\n");
    tmp = Delete(L, P);
    if ( tmp!=ERROR ) printf("Wrong Answer\n");
    for ( P=L; P; P = P->Next ) printf("%d ", P->Data);
    return 0;
}

/* 你的代码将被嵌在这里 */
Position Find(List L, ElementType X)
{
	while (L != NULL)
	{
		if (L->Data == X)
			return L;
		L = L->Next;
	}
	return ERROR;
}

List Insert(List L, ElementType X, Position P)
{
	if (L == P) {
		Position temp = (List)malloc(sizeof(struct LNode));
		P = temp;
		P->Next = L;
		P->Data = X;
		L = P;
		return L;
	}
	else if (P == NULL && L)
	{
		PtrToLNode q = L;
		while (q->Next != NULL)
			q = q->Next;
		Position lastelem = (List)malloc(sizeof(struct LNode));
		lastelem->Next = q->Next;
		q->Next = lastelem;
		lastelem->Data = X;
		return L;
	}
	else
	{
		Position k = L;
		while (k->Next != NULL)
		{
			if (k->Next == P)
				break;
			k = k->Next;
		}
		if(!k->Next)
		{
		    printf("Wrong Position for Insertion\n");
		    return ERROR;
		}
		List inelem = (List)malloc(sizeof(struct LNode));
		inelem->Next = P;
		k->Next = inelem;
		inelem->Data = X;
		return L;
	}
}

List Delete(List L, Position P)
{
	if (!P)
	{
		printf("Wrong Position for Deletion\n");
		return ERROR;
	}
	if (L == P)
	{
		L = L->Next;
		return L;
	}
	Position q = L;
	while (q)
	{
		if (q->Next == P)
		{
			q->Next = P->Next;
			free(P);
			return L;
		}
		q = q->Next;
	}
	printf("Wrong Position for Deletion\n");
	return ERROR;
}