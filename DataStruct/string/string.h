/*
 * 串结构的定义区
 */

#ifndef DATASTRUCT3_STRING_H
#define DATASTRUCT3_STRING_H

#include "global_defined.h"

/*
 * 定长顺序存储结构
 */
#define MAX_STR_LEN 40 //用户可在255内定义最大串长
typedef unsigned char SString[MAX_STR_LEN+1];//0号单元存放串的长度

#define DestroyString ClearingString; //函数作用与ClearingString()相同
#define InitString ClearingString;

Status StrAssign(SString, const char *);
void StrCopy(SString, SString);
Status StrEmpty(SString);
int StrCompare(SString, SString);
int StringLength(SString);
void ClearingString(SString s);
Status Concat(SString, SString, SString);
Status SubString(SString, const SString, int, unsigned);

Status StrInsert(SString S, int pos, SString T);
Status StrDelete(SString, int pos, int len);
void StrPrint(SString);
#endif //DATASTRUCT3_STRING_H
