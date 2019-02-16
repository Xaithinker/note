/*
 * for testcase
 */
#include "testcase.h"

void testIndex1()
{
    char c[MAX_STR_LEN+1];
    SString s1, s2;
    printf("please input string1\n");
    gets(c);
    StrAssign(s1, c);
    StrPrint(s1);
    printf("************************\n"
           "*     ...Loading...    *\n"
           "************************\n"
           "*     ...Loading...    *\n"
           "************************\n");
    printf("please input string2\n");
    gets(c);
    StrAssign(s2, c);
    StrPrint(s2);

    printf("First to next()func.....\n");
    int *p = (int *)malloc((StringLength(s2)+1) * sizeof(int));
    get_next(s2, p);
    printval(s2, p);
    int pos = Index_KMP(s1, s2, 1, p);
    printf("Second to next_val()func......\n");
    get_nextval(s2, p);
    printval(s2, p);
    int pos1 = Index_KMP(s1, s2, 1, p);
    if(pos)
    {
        printf("next()test:Matched in %d\n", pos);
    }
    if(pos1)
    {
        printf("next_val()test:Matched in %d\n", pos1);
    }
}

void printval(SString S, int *p)
{
    printf("\nThe next func is .........\n");
    for(int i=1;i<=S[0];++i)
        printf("%d", *(p+i));
    printf("\nThe next func is over ......\n");
}