/*
 * 模式串匹配算法
 * 及KMP算法相关
 */

#ifndef DATASTRUCT3_INDEX_H
#define DATASTRUCT3_INDEX_H

#include "global_defined.h"
#include "string.h"

/*
 * 模式串匹配算法
 * 文本编辑也比较高
 * 但当处理只有0，1两种字符的文本串时，指针i可能引起多次回溯
 * 最坏情况下的时间复杂度为O(n*m)
 */
#define Index1 Index

int Index(const SString String, const SString SubString, unsigned int FromPosition);


/*
 * KMP算法
 * 时D.E.Knuth 与 V.R.Pratt 和 J.H.Morris同时发现的
 * 其首字母KMP即为名字的由来
 * 算法时间复杂度O(n+m)
 */

int Index_KMP(const SString String, const SString SubString, unsigned int FromPosition, const int next[]);
void get_next(SString T, int next[]);
void get_nextval(SString T, int nextval[]);
#endif //DATASTRUCT3_INDEX_H
