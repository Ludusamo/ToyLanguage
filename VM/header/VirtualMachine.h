#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

static int stack[256]; // VM's stack array.
static int *gmem;

static bool running = true; // Boolean value indicating whether the program is currently running.
static bool trace = true; // Boolean value indicating whether the stack is being traced.

static const int *PROGRAM;

void push(int val); // Adds an item to the top of the stack.
int pop(); // Pops off the top-most item on the stack.
int getNextOperand();

void eval(int op); // Evaluates an individual operation based on the stack.
int fetch(); // Returns the current operation being evaluated.
void printStackTrace(int op);

void runProgram(const int *program, const int mainIndex, const int gMemSize);

typedef enum {
	A, B, C, D, IP, SP, FP, NUM_OF_REGISTERS
} Registers;
static int registers[NUM_OF_REGISTERS];

#endif // VIRTUALMACHINE_H
