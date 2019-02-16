#pragma once

/*
 * ����ȫ��ͷ�ļ���״̬��
 */

#ifndef DATASTRUCT2_GLOBAL_DEFINED_H
#define DATASTRUCT2_GLOBAL_DEFINED_H

#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <cstdlib>

 // #define NDEBUG //disable "assert"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

/*
 * Function-like Macros defined
 */

 //   In��The C Preprocessor��Richard M. Stallman, Zachary Weinberg
 //  "When a macro parameter is used with a leading ��#��, the preprocessor replaces it
 //   with the literal text of the actual argument, converted to a string constant."

//#define echo(func_name) {                                                                    \
//                          printf("%s has finished!\n",(#func_name));                        \
//                          printf(".............................\n"); }  //ȷ����������
#define echo(func_name) { }  //ȷ����������

/*
 * ȫ�־�̬��������
 */
 //extern const char _struct_name[5][7];
 //@DATE9.5.2019 copied from.
// static const char _struct_name[6][10] = { "SqStack_H", "SqStack_A", "SLinkNode", "SqQueue", "LinkQueue", "CycQueue" }; //for function of belongt

/*
 * ���ͱ���������
 */
typedef int Status;
typedef int ElemType;

#endif //DATASTRUCT2_GLOBAL_DEFINED_H

