/*
 * The implementation of algorithms of sequence list and link_list interface.
 */
#include "linear_list_algo.h"


SEQUENCE_LIST_ALGO_START
void MergeList_sq(SqList La, SqList Lb, SqList * Lc)
{//La和Lb的元素值按非递减排列
    // 归并La 和 Lb 的元素按值非递减排列
    ElemType * pa, *pa_last, *pb, *pb_last, *pc;
    pa = La.elem;
    pb = Lb.elem;
    Lc->listsize = Lc->length = La.length + Lb.length;//初始化Lc的表长
    pc = Lc->elem = (ElemType *)malloc(Lc->length * sizeof(ElemType));
    if(!Lc->elem)//存储分配失败
        exit(OVERFLOW);
    pa_last = La.elem + La.length - 1;
    pb_last = Lb.elem + Lb.length - 1;//均指向最后一个元素
    while(pa <= pa_last && pb <= pb_last)
    {//归并
        if(* pa <= * pb)
            * pc++ = * pa++;
        else
            * pc++ = * pb++;
    }//以下循环仅有一个被执行
    while(pa <= pa_last)//pa剩余元素
        * pc++ = * pa++;
    while(pb <= pb_last)
        * pc++ = * pb++;
    echo(MergeList_L);
    belongt(0);
}
SEQUENCE_LIST_ALGO_END


LINK_LIST_ALGO_START
void MergeList_L(LinkList La, LinkList Lb, LinkList Lc)
{
    echo(MergeList_L);
}
LINK_LIST_ALGO_END