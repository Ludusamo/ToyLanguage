#include "Debug.h"

void printStackTrace(int ip, int sp, int op, const int *PROGRAM, int *stack) {
	printf("%04d: %s ", ip, OPERATIONS[op].name);
	for (int i = 0; i < OPERATIONS[op].numOps; i++) {
		printf("%i ", PROGRAM[ip+i+1]);
	}
	printf("%*s", (15 - (strlen(OPERATIONS[op].name) + 2 * OPERATIONS[op].numOps)), "[ ");
	for (int i = 0; i < sp + 1; i++) {
		printf("%d ", stack[i]);
	}
	printf("]\n");
}

void dumpMemory(int gMemSize) {
	printf("\n[ ");	
	for (int i = 0; i < gMemSize; i++) {
		printf("%i ", gmem[i]);
	}
	printf("]\n");
}
