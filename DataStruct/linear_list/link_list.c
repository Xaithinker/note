/*
 * 链表的基本函数操作实现
 */

#include "link_list.h"

SINGLE_LINK_LIST_START
LinkList InitList_()//初始化过程中的L要变化，故需要一个指针，但记得释放指针！
{
    LinkList L = (LinkList)malloc(sizeof(LNode));//L是指向头结点的指针
    if(! L)
        exit(OVERFLOW);
    L->next = NULL;//L->next指向第一个元素的指针，其值为NULL初始化
    echo(InitList_);
    return L;
}

void DestroyList_(LinkList L)
{
    assert(L!=NULL);
    LinkList q;
    while(L)//遍历链表,依次free存储空间,直到尾节点指向的NULL来终止循环
    {
        q = L->next;
        free(L);
        L = q;//L不断指向新的"首节点"
    }
    echo(DestroyList_);
}

void ClearList_(LinkList L)
{
    assert(L!=NULL);
    LinkList p = L->next;//指向第一个结点(带数据)而不是头结点
    L->next = NULL;//头结点指向NULL，说明只剩下头结点，链表清空
    DestroyList_(p);//从第一个结点开始释放空间
    echo(ClearList_);
}

status ListEmpty_(LinkList L)
{
    if(L->next)
        return FALSE;
    else
    {
        echo(ListEmpty_);
        return TRUE;
    }
}

int ListLength_(LinkList L)
{
    int i = 0;
    LinkList p = L->next;//第一个结点
    while(p)
    {
        i++;
        p=p->next;//p更新下一个结点
    }
    echo(ListLength_);
    return i;//返回长度值i
}

status GetElem_(LinkList L, int i, ElemType *e)
{
    int j = 1;//计数器初值1
    LinkList p = L->next;//从第一个结点开始；
    while(p && j<i)//j达到i的前一个时，继续执行一个，此时p.next 正好指向第i个
    {
        j++;
        p = p->next;
    }
    if(!p || j>i)return ERROR;//报告错误
    *e = p->data;//赋值（当i=1时直接执行此段代码赋值！！！！）
    echo(GetElem_);
}

 int LocateElem_(LinkList L, ElemType e, status(* compare)(ElemType, ElemType))
 {//返回第一个满足关系的元素的位序
    int i = 0;
    LinkList p = L->next;//第一个元素结点
    while(p)
    {
        i++;
        if(compare(p->data, e))
            return i;
        p = p->next;
    }
    echo(LocateElem_);
    return 0;
 }

 status PriorElem_(LinkList L, ElemType cur_e, ElemType *pre_e)
 {
    LinkList q, p = L->next;
    while(p && p->next)
    {
        q = p->next;//q指向p的后继
        if(q->data == cur_e)
        {
            *pre_e = p->data;
            echo(PriorElem_);
            return OK;
        }
        p = q;//向后移
    }
     return ERROR;
 }

 status NextElem_(LinkList L, ElemType cur_e, ElemType *next_e)
 {
    LinkList p = L->next;//第一个元素结点
    while(p && p->next)
    {
        if(p->data == cur_e)
        {
            *next_e = p->next->data;
            echo(NextElem_);
            return 0;
        }
        p = p->next;//继续后移
    }
     return ERROR;
 }

 status ListInsert_(LinkList L, int i, ElemType e)
 {
    int j = 0;
    LinkList s, p=L;
    while(p && j < i-1)//寻找第i-1个结点
    {
        j++;
        p = p->next;
    }
    if(!p || j > i-1)return ERROR;
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;//新结点首先指向原第i个结点
    p->next = s;//原i-1个结点指向新插入结点
    echo(ListInsert_);
 }

 status ListDelete_(LinkList L, int i, ElemType *e)
 {//同样先找到第i-1个结点
    int j = 0;
    LinkList q, p=L;
    while(p->next && j < i-1)
    {//寻找第i个结点并指向其前驱
        j++;
        p = p->next;
    }
    if(!p || j > i-1)return ERROR;
    q = p->next; //q指向待删除结点
    p->next = q->next;
    *e = q->data;
    free(q);
    echo(ListDelete_);
    return 0;
 }

void ListTraverse_(LinkList L, void (* visit)(ElemType))
{//依次对L的每个数据调用函数visit()
    LinkList p = L->next;//第一个结点
    while(p)
    {
        visit(p->data);
        p = p->next;//遍历
    }
    echo(ListTraverse_);
}
SINGLE_LINK_LIST_END