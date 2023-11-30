#include <string.h>
#include "module_1.h"

int state=0;

void ModuleOneInit()
{
    state = MOD_1_VAL;
}

void ModuleOneChangeState(int new_state)
{
    state = new_state;
}

int ModuleOneGetState(void)
{
    return state;
}

bool ModuleOneIsZero(void)
{
    if (state == 0)
        return true;

    return false;
}

void ModuleOneGetText(char buf[16])
{
    if (buf == NULL)
        return;
    
    strcpy(buf, "Hello");
}
