#include <process.h>
#include "global_testcase.h"
#include "link_list.h"
#include "linear_list.h"

int main() {
    sqlist_test_func();
    linklist_test_func();
    printf("%X\n",2147483647);//MAX SIGNED INT
    printf("%s\n", _struct_name[1]);
    belongt(2);
    system("pause");
    return 0;
}

