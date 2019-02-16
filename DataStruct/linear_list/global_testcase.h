/*
 * This is for the correctness of different struct and algorithms
 */
#ifndef DATASTRUCT_GLOBAL_TESTCASE_H
#define DATASTRUCT_GLOBAL_TESTCASE_H

#include "linear_list.h"
#include "link_list.h"

/*
 * 测试用例的两个开关
 */
#define SEQUENCE_LIST_TESTCASE
#define LINK_LIST_TESTCASE //turn on testcase when needed

/*
 * common function-like macro defined
 */
#define equal(c1, c2) {if((c1)==(c2))                \
                         return TRUE;                \
                       else                          \
                         return FALSE;               \
                        }
#define comp(a, b) {if((a)==(b))                     \
                      return 0;                      \
                    else                             \
                      return ((a)-(b))/abs((a)-(b)); \
                    }
#define printfint(c) printf("%d", (c)) //以十进制整型格式输出元素值
#define printfptr(c) printf("%d", *(c)) //c是一个指针，输出指向的其元素值
#define printfc(c) printf("%c", c) //以格式串形式输出值

/*
 * 顺序表测试用例封装
 */
#ifdef SEQUENCE_LIST_TESTCASE
#define  ENABLE_SEQUENCE_LIST_TESTCASE
#define SEQUENCE_LIST_TESTCASE_START
#define SEQUENCE_LIST_TESTCASE_END

#define printfad_sq(c) {int *addr = (c).elem;printf("The %s addr is %X\n",(#c), (*addr));}  //打印其地址值

boolean sqlist_test_func();
#endif //SEQUENCE_LIST_TESTCASE

/*
 * 链表测试用例封装
 */
#ifdef LINK_LIST_TESTCASE
#define ENABLE_LINK_LIST_TESTCASE
#define SINGLE_LINK_LIST_TESTCASE_START
#define SINGLE_LINK_LIST_TESTCASE_END

#define printfad_link(lkptr) {printf("The %s addr is %p\n",(#lkptr), &(lkptr));}

boolean linklist_test_func();

#endif //LINK_LIST_TESTCASE


#endif //DATASTRUCT_GLOBAL_TESTCASE_H