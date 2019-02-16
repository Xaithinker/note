#pragma once

/*
 * 定义全局头文件和状态码
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

 //   In《The C Preprocessor》Richard M. Stallman, Zachary Weinberg
 //  "When a macro parameter is used with a leading ‘#’, the preprocessor replaces it
 //   with the literal text of the actual argument, converted to a string constant."

//#define echo(func_name) {                                                                    \
//                          printf("%s has finished!\n",(#func_name));                        \
//                          printf(".............................\n"); }  //确保函数返回
#define echo(func_name) { }  //确保函数返回

/*
 * 全局静态变量定义
 */
 //extern const char _struct_name[5][7];
 //@DATE9.5.2019 copied from.
// static const char _struct_name[6][10] = { "SqStack_H", "SqStack_A", "SLinkNode", "SqQueue", "LinkQueue", "CycQueue" }; //for function of belongt

/*
 * 类型别名定义区
 */
typedef int Status;
typedef int ElemType;

#endif //DATASTRUCT2_GLOBAL_DEFINED_H

