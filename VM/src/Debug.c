#include "Debug.h"

int numDigits(int num) {
	int count = 1;
	while (num >= 10) {
		num /= 10;
		count++;
	}
	return count;
}

void printStackTrace(int ip, int sp, int op, const int *PROGRAM, int *stack) {
	int lenOffset = 20 - strlen(OPERATIONS[op].name) - OPERATIONS[op].numOps; // Length necessary to offset stack print.
	fprintf(stderr, "%04d: %s ", ip, OPERATIONS[op].name);
	for (int i = 0; i < OPERATIONS[op].numOps; i++) {
		fprintf(stderr, "%i ", PROGRAM[ip+i+1]);
		lenOffset -= numDigits(PROGRAM[ip+i+1]);
	}
	fprintf(stderr, "%*s", lenOffset, "[ ");
	for (int i = 0; i < sp + 1; i++) {
		fprintf(stderr, "%d ", stack[i]);
	}
	fprintf(stderr, "]\n");
}

void dumpMemory(int gMemSize, int *gmem) {
	fprintf(stderr, "[ ");	
	for (int i = 0; i < gMemSize; i++) {
		fprintf(stderr, "%i ", gmem[i]);
	}
	fprintf(stderr, "]\n");
}
