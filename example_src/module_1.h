#ifndef _MODULE_1_H_
#define _MODULE_1_H_

#include <stdbool.h>

#define MOD_1_VAL       42

void ModuleOneInit();
void ModuleOneChangeState(int new_state);
int  ModuleOneGetState(void);
bool ModuleOneIsZero(void);
void ModuleOneGetText(char buf[16]);

#endif /* _MODULE_1_H_ */
