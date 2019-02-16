/*
 * 线性表基本操作函数实现
 */

#include "linear_list.h"

DYNAMIC_SEQUENCE_LIST_START
void InitList(SqList *L)
{
    asset(L);
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L->elem)//存储分配失败
        exit(OVERFLOW);
    L->length = 0;  //当前长度为0
    L->listsize = LIST_INIT_SIZE; //初始分配容量
    echo(InitList);
}

void DestroyList(SqList *L)
{//初始条件:顺序表L存在. 操作结果:摧毁线性表L
    asset(L);
    L->listsize = 0;
    L->length = 0;
    free(L->elem);
    L->elem = NULL;
    echo(DestroyList);
}

void ClearList(SqList * L)
{//初始条件，顺序表存在。操作结果 重置空表
    asset(L);
    L->length = 0;
    echo(ClearList);
}

status ListEmpty(SqList L)
{
    asset(&L);
    if(L.length == 0)//判断顺序表是否空
        return TRUE;
    else
        return FALSE;
}

int ListLength(SqList L)
{
    asset(&L);
    return L.length;//返回顺序表长度
}

status GetElem(SqList L, int i, ElemType *e)
{//顺序表存在,且1=<i<=L.length。 e返回第i个数据的值
    if(i<1 || i>L.length)
        return ERROR;
    *e = *(L.elem + i-1); //第i个元素!
    echo(GetElem);
    return OK;
}

int LocateElem(SqList L, ElemType e,status(*compare)(ElemType, ElemType))
{//compare函数是数据元素判定函数（满足为1，否则为0）
    //操作结果:返回L中第一个与e满足关系compare()的数据元素的位序
    //若不存在，返回0
    int i=1;
    ElemType *p = L.elem;
    while(i <= L.length && !compare(e, *p++))  //继续遍历的条件是i未超出表长且compare返回0
        i++;
    if(i <= L.length + 1)
        return i;
    else
        return ERROR;
}

status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e)
{//若cur_e是L的数据元素，且不是第一个，用pre_e返回其前驱
    //否则操作失败，pre_e无定义
    int i=2; //寻找前驱，从第二个开始
    ElemType *p = L.elem + 1; //p指向第二个
    while(i <= L.length && *p != cur_e)//由i控制指针不越界
    {
        p++;
        i++;
    }
    if(i>L.length)//未找到
        return ERROR;//操作失败
    else
    {
        *pre_e = *(--p);//前驱
        return OK;
    }

}

status NextElem(SqList L, ElemType cur_e, ElemType *next_e)
{//后继。cur_e是L中数据元素，且不是最后一个
    int i=1;
    ElemType *p = L.elem;
    while(i<L.length && *p != cur_e)
    {
        p++;
        i++;
    }
    if(i>=L.length)
        return ERROR;
    else
    {
        *next_e = *(++p);
        return OK;
    }
}

status ListInsert(SqList *L, int i, ElemType e)
{//初始条件，顺序表存在
    // 1 =<i<= ListLength(L)+1 从第一个位置到最后一个位置均可插入
    asset(L);
    ElemType * newbase, * q, * p;
    if(i<1 || i>L->length+1)//判断i的合法性
        return ERROR;
    if(L->length == L->listsize)//存储空间已满，需重新分配
    {
        newbase = (ElemType *)realloc(L->elem, (L->listsize + LIST_INCREMENT)* sizeof(ElemType));
        if(!newbase)//分配失败
            exit(OVERFLOW);
        L->elem = newbase; //顺序表状态更新
        L->listsize += LIST_INCREMENT; //顺序表长增加，注意L.length不变
    }
    //进行插入操作
    q = L->elem + i-1; //q指向插入位置待命
    for(p = L->elem + L->length - 1; p >= q; --p)//注意：移动操作需要在表尾部开始，否则元素会覆盖
        *(p+1)=*p;//元素向后逐渐移动一位
    *q=e; //移动完毕后再插入!
    L->length++;
    return OK;
}

status ListDelete(SqList *L, int i, ElemType *e)
{
    asset(L);
    //1 =<i<= L.length 注意与ListInsert的i合法值不同
    ElemType * p, * q;
    p = L->elem + i-1;
    *e = *p;//删除之前先赋值!
    q = L->elem + L->length -1;//表尾
    for(p++; p<=q;p++)//q控制指针不越表界
        *(p-1) = *p;
    L->length--;
    return OK;
}

void Traverse(SqList L, void(* visit)(ElemType *))
{//依次对L中的每一个元素调用函数visit()，且可通过传入指针改变其值的大小。
    ElemType *p = L.elem - 1;//首元素
    for(int i=1; i <= L.length; i++)//i控制指针不越界
        visit(p++);//传入元素指针
    echo(Traverse);
}
DYNAMIC_SEQUENCE_LIST_END