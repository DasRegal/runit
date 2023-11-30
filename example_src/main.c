#include <stdio.h>
#include "module_1.h"

int main(void)
{
    char buf[16];

    ModuleOneInit();
    ModuleOneChangeState(5);
    printf("Module 1. Val=%d\n", ModuleOneGetState());

    ModuleOneGetText(buf);
    printf("%s\n", buf);

    return 0;
}
