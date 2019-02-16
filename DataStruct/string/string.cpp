/*
 * 串操作简单实现
 */

#include "string.h"

Status StrAssign(SString T, const char * chars) {//生成一个其值等于chars的串T
    int i;
    if (strlen(chars) > MAX_STR_LEN)//chars长度大于最大串长
        return ERROR;
    else
    {
        T[0] = (char)strlen(chars);
        for(i=1; i<=T[0]; ++i)
            T[i] =(unsigned char) *(chars + i - 1);
    }
    echo(StrAssign);
    return OK;
}

void StrCopy(SString T, SString S)
{
    int i;
    for(i=1; i<=S[0]; ++i)
        T[i] = S[i];
    echo(StrCopy);
}

Status StrEmpty(SString S)
{
    if(S[0] == 0)
        return TRUE;
    else
        return FALSE;
}

int StrCompare(SString S, SString T)
{
    int i;
    for(i=1; i<=S[0] && i<=T[0]; ++i)
        if(S[i] != T[i])
            return S[i]-T[i];
    return S[0] - T[0];
}

int StringLength(SString S)
{
    echo(StringLength);
    return S[0];
}

void ClearingString(SString S)
{
    S[0] = 0;
    echo(ClearingString);
}
//TODO:完成串的定义。重点KMP算法！
Status Concat(SString T, SString S1, SString S2)
{//串T返回两串的连接
    int i;
    if(S1[0] + S2[0] <= MAX_STR_LEN)//未截断
    {
        for(i=1; i<=S1[0]; ++i)
            T[i] = S1[i];
        for(i=1; i<=S2[0]; ++i)
            T[S1[0] + i] = S2[i];
        T[0] = S1[0] + S2[0];
        echo(Concat);
        return OK;
    }
    else//对S2截断
    {
        for(i=1; i<=S1[0]; ++i)
            T[i] = S1[i];
        for(i=1; i<= MAX_STR_LEN - S1[0]; ++i)
            T[S1[0] + 1] = S2[0];
        T[0] = MAX_STR_LEN;
        echo(Concat);
        printf("another case");
        return FALSE;
    }
}

Status SubString(SString Sub, const SString S, int pos, unsigned len)
{
    int i;
    if(pos<1 || pos>S[0] || len<0 || len>S[0]-pos+1) //重点:pos和len值超出范围
        return ERROR;
    for(i=1; i<=len; ++i)
        Sub[i] = S[pos+i-1];//遍历并赋值
    Sub[0] =(char) len;
    echo(SubString);
    return OK;
}



//TODO:not used temporary
Status StrInsert(SString S, int pos, SString T)
{
    return 0;
}
//TODO:not used temporary
Status StrDelete(SString S, int pos, int len)
{
    return 0;
}

void StrPrint(SString S)
{
    for(int i=1; i<=S[0]; ++i)
        printf("%c", S[i]);
    printf("\n");
    echo(StrPrint);
}