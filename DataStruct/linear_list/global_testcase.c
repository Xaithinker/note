/*
 * This is for the correctness of different struct and algorithms
 */

#include "global_testcase.h"

/*
 * 线性表的TestCase实现
 */
#ifdef  ENABLE_SEQUENCE_LIST_TESTCASE

SEQUENCE_LIST_TESTCASE_START
//code between there
boolean sqlist_test_func()
{//顺序表的专属测试用例
    SqList sqlist = {NULL, 0, 0};
    SqList *sqlist_p = &sqlist;
    InitList(sqlist_p);
/*
 * @query:how to avoid the collision if same function name was included in one c source file
 *        or how to write a wrapper to work out?
 */
#if defined(SEQUENCE_LIST_TESTCASE)  //如何两个同时包含呢，该如何处理相同的函数名？？？
    printfad_sq(sqlist);
#endif

    DestroyList(sqlist_p);
    belongt(0);
    return OK;
}
SEQUENCE_LIST_TESTCASE_END

#endif //Enable_SEQUENCE_LIST_TESTCASE

/*
 * 单链表的TestCase实现
 */
#ifdef ENABLE_LINK_LIST_TESTCASE

SINGLE_LINK_LIST_TESTCASE_START
//code between there
boolean linklist_test_func()
{
    LinkList linklistptr = InitList_();
#if defined(LINK_LIST_TESTCASE)
    printfad_link(linklistptr);
#endif //LINK_LIST_TESTCASE
    DestroyList_(linklistptr);
    belongt(1)
    return OK;
}
SINGLE_LINK_LIST_TESTCASE_END

#endif //ENABLE_SEQUENCE_LIST_TESTCASE