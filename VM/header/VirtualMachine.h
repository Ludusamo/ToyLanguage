#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Bytecode.h"
#include "Debug.h"
#include "Error.h"

int stack[256]; // VM's stack array.
int *gmem;

int running; // Boolean value indicating whether the program is currently running.
int trace; // Boolean value indicating whether the stack is being traced.

const int *PROGRAM;

void eval(int op); // Evaluates an individual operation based on the stack.
int fetch(); // Returns the current operation being evaluated.

void runProgram(const int *program, const int mainIndex, const int gMemSize);

typedef enum {
	A, B, C, D, IP, SP, FP, NUM_OF_REGISTERS
} Registers;
int registers[NUM_OF_REGISTERS];

#endif // VIRTUALMACHINE_H
