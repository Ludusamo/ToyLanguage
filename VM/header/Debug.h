#ifndef DEBUG_H
#define DEBUG_H

#include "Bytecode.h"
#include <stdio.h>
#include <string.h>

void printStackTrace(int ip, int sp, int op, const int *PROGRAM, int *stack);
void dumpMemory(int gMemSize, int *gmem);

#endif // DEBUG_H
