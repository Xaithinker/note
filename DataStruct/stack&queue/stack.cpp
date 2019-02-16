/*
 * 各种栈的实现
 */

#include "stack.h"

/*
 * 动态分配的顺序栈
 */
#ifdef ENABLE_SQSTACK_HEAP

void InitStack(SqStack_H &S)
{//构造空栈，使用动态堆分配
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    echo(InitStack);
    belongt(0);
}

void DestroyStack(SqStack_H &S)
{
    free(S.base);
    S.top = S.base = nullptr;
    echo(DestroyStack);
    belongt(0);
}

void ClearStack(SqStack_H &S)
{
    S.top = S.base; //将栈顶指向栈底，置空
    echo(ClearStack)
    belongt(0);
}

status StackEmpty(SqStack_H S)
{//栈空的判定条件:栈顶等于栈底！
    if(S.top == S.base)
        return TRUE;
    else
        return FALSE;
}

unsigned long StackLength(SqStack_H S)
{
    return S.top - S.base;
}

status GetTop(SqStack_H S, SElemType &e)
{
    if(S.top > S.base)//栈非空
    {
        e = * (S.top -1); //严书的栈顶指针指向下一个要入栈的位置!!
        echo(GetTop);
        belongt(0);
        return OK;
    }
    return 0;
}

void Push(SqStack_H &S, SElemType e)
{
    if(S.top - S.base == S.stacksize)//栈满需要重新分配
    {
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACK_INCREMENT) * sizeof(SElemType));
        if(!S.base)
            exit(OVERFLOW);
        S.top = S.base + S.stacksize; //栈顶更新
        S.stacksize += STACK_INCREMENT;
    }
    *(S.top) = e; //因栈定指向下一个将要存放的空间，故先赋值，再自增
    /*
     *    ----
     *    ！  ！
     *    ----
     *    ！  ！
     *--> ----
     *    ！e ！
     *  ->----
     *    .....
     */
    ++S.top;
    echo(Push);
}

status Pop(SqStack_H &S, SElemType &e)
{//弹出栈的前提是栈非空
    if(S.top == S.base)
        return ERROR;
    --S.top;//先减指针再取值 这里和Push的操作不论何种形式，这两者操作一定是互补的
    e = * S.top;
    return OK;
}

void StackTraverse(SqStack_H S, void (*visit)(SElemType))
{//从栈底到栈顶依次对元素调用函数visit()
    SElemType * p = S.base;
    while(S.top > p)
        visit(* p++);
    echo(StackTraverse);
}

#endif //ENABLE_SQSTACK_HEAP

/*
 * 静态分配的顺序栈
 * 此时将栈空状态定义为-1，则栈顶指针指向当前存放元素。而非堆分配时的指向下一个元素的值
 * 注意此时入栈和出栈的操作顺序略有不同
 */
#ifdef ENABLE_SQSTACK_ARRARY

void InitStack(SqStack_A &S)
{
    S.top = -1;//只需将描述栈的数组中top值改为-1即表示此时栈空
    echo(InitStack);
    belongt(1);
}

void ClearStack(SqStack_A &S)
{
    S.top = -1;//栈置空
}

status StackEmpty(SqStack_A S)
{
    if(S.top == -1)
        return TRUE;
    else
        return FALSE;
}

int StackLength(SqStack_A S)
{
    echo(StackLength);
    belongt(1);
    return S.top + 1;
}

status GetTop(SqStack_A S, SElemType &e)
{
    e = S.data[S.top];
    echo(GetTop);
    belongt(1);
    return OK;
}

void Push(SqStack_A &S, SElemType e)
{//进栈不能满，静态数组退出
    if(S.top == MaxSize -1)
        exit(OVERFLOW);
    ++S.top;//这里先移动指针再入栈
    S.data[S.top] = e;
    echo(Push);
    belongt(1);
}

status Pop(SqStack_A &S, SElemType &e)
{//出栈不能栈空
    if(S.top == -1)
        return OVERFLOW;
    e = S.data[S.top];
    --S.top;//先出栈再移动指针。与入栈动作匹配
    echo(Pop);
    belongt(1);
}

void StackTraverse(SqStack_A S, void (*visit)(SElemType))
{
    if(S.top == -1)
        exit(OVERFLOW);
    int i = 0;//指针
    while(S.top >= i)
        visit(S.data[i++]);
    echo(StackTraverse);
    belongt(1);
}

#endif //ENABLE_SQSTACK_ARRARY

/*
 * 栈的链式存储实现
 * 实际作为线性表含特定操作的例子
 */
#ifdef ENABLE_LINKSTACK

void InitStack(SLinkNode_P &S)//指针值需要修改，故指针的引用型
{
    S = (SLinkNode_P)malloc(sizeof(SLinkNode));//头结点指向第一个元素即栈顶
    if(!S)
        exit(OVERFLOW);
    S->next = nullptr;
    echo(InitStack);
    belongt(2);
}

void DestroyStack(SLinkNode_P S)
{
    SLinkNode_P q;
    while(S)//栈存在
    {
        q = S->next;//开始指向栈顶
        free(S);//从头结点开始释放空间
        S = q;//不断更新指向下一个元素
    }
    echo(DestroyStack);
    belongt(2);
}

void ClearStack(SLinkNode_P S)
{
    SLinkNode_P p = S->next;//指向栈顶
    DestroyStack(p);//释放头结点之后的元素
    S->next = nullptr;//头结点指向空指针，即栈清空，栈顶不存在
    echo(ClearStack);
    belongt(2);
}

status StackEmpty(SLinkNode_P S)
{//判空
    if(S->next == nullptr)
        return OK;
    else
        return FALSE;
}

int StackLength(SLinkNode_P S)
{
    int c = 0;//计数器
    SLinkNode_P p = S->next;//指向栈顶
    while(p)
    {
        ++c;
         p = p->next;//更新直至next == nullptr
    }
    echo(StackLength);
    belongt(2);
    return c;
}

status GetTop(SLinkNode_P S, SElemType &e)
{
    e = S->next->data;//第一个元素即栈顶值
    echo(GetTop);
    belongt(2);
    return OK;
}

void Push(SLinkNode_P S, SElemType e)
{//进栈的实质为线性表的头插法插入第一个位置
    SLinkNode_P p;
    p = (SLinkNode_P)malloc(sizeof(SLinkNode));//创建插入元素的结构体
    p->next = nullptr;//保持良好习惯及时置空
    //执行头插法
    p->next = S->next;
    S->next = p;
    p->data = e;
}

status Pop(SLinkNode_P S, SElemType &e)
{//实质为线性表中删除第一个结点的操作
    if(S->next == nullptr)
        exit(OVERFLOW);
    SLinkNode_P p;
    //删除结点操作
    p = S->next;//指向要删除的结点，删除前要赋值
    e = p->data;
    S->next = p->next;
    free(p);
    echo(Pop);
    belongt(2);
    return OK;
}

void StackTraverse(SLinkNode_P S, void (*visit)(SElemType))
{
    SLinkNode_P p = S->next;
    while(p)
    {
        visit(p->data);
        p = p->next;//指向下一个元素
    }
    echo(StackTraverse);
    belongt(2);
}

#endif //ENABLE_LINKSTACK