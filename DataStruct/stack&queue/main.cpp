#include <iostream>
#include "stack.h"
using namespace std;

//#undef ENABLE_SQSTACK_HEAP
//#undef ENABLE_SQSTACK_ARRARY

#ifdef ENABLE_SQSTACK_HEAP
int main() {
    SqStack_H seqstack = {nullptr, nullptr, 0};
    SqStack_H & seqstack1 = seqstack;
    InitStack(seqstack1);
    DestroyStack(seqstack1);
    cout << "Hello, World!" << endl;
    return 0;
}

#elif defined(ENABLE_SQSTACK_ARRARY)
int main()
{
    return 0;
}
#else

int main()
{
    return 0;
}
#endif //ENABLE_LINKSTACK