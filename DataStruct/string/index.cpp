/*
 * 模式串匹配算法实现
 */

#include "index.h"

/*     串的模式匹配算法
 *     io i1|i|
 * [][][][][c1][][][] S串
 *     [][][c2][][]   T串
 *         |j| S[i]!=S[j] i指针后退至io的下个位置i1 !为i-j+1+1
 */
int Index(const SString S, const SString T, unsigned int pos)
{//返回字串T在主串中的第pos个字符之后的位置。若不存在为0
    //其中，T非空，1<=pos<=S[0]
    echo(Index1);
    int i, j;//指示主串S和字串T的当前比较字符
    if(1<=pos && pos<=S[0])
    {
        i = pos;//从pos开始和字串比较
        j = 1;
        while(i<=S[0] && j<=T[0])
        {
            if(S[i] == T[j])//当前比较字符相等
            { ++i;++j;}//继续自增比较后面字符
            else
            {
                i = i - j + 2;
                j = 1;//j从1重新开始匹配
            }
        }
        if(j>T[0])//主串S中存在字串T
        {
            printf("The relative location of matched string is:\n");
            return i-T[0];
        }
        else//主串中不存在字串
            return FALSE;
    }
    else
        return FALSE;//主串位置不合适
}

int Index_KMP(const SString S, const SString T, unsigned int pos , const int next[])
{
    int i = pos, j = 1;
    while(i <= S[0] && j <= T[0])//i,j均为超出主串S和模式串T的范围
    {
        if(j == 0 || S[i] == T[j])
        {
            ++i;++j;
        }
        else//模式串向右移动
            j = next[j];
    }
    echo(Index_KMP);
    if(j > T[0])//匹配成功
        return i - T[0];
    else
        return 0;
}

void get_next(SString T, int next[])
{//求模式串T的next函数修正值并存入数组next中
    int i =1, j = 0;
    next[1] = 0;
    while(i < T[0])
    {
        if(j==0 || T[i] == T[j])
        {
            ++i;++j;
            next[i] = j;//(此处j为下一个字符)当相等时，仅需继续比较
        }
        else
        {
            j = next[j];//j减小到前面字符相等之处
        }
    }
    echo(get_next);
}

void get_nextval(SString T, int nextval[])
{//模式串的T的next函数修正值，并存入next_val。
    //考虑到上述的next[j] = k 而模式串pj=pk.则当主串中的字符si 和 pj不等时，无需再和pj比较
    //直接和Pnext[k]比较
    int i = 1, j = 0;
    nextval[1] = 0;
    while(i < T[0])
    {
        if(j == 0 || T[j] == T[i])
        {
            ++i;++j;
            if(T[i] != T[j])//与上算法不同处
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
    echo(get_nextval);
}
