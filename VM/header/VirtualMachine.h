#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

static int ip = 0; // Instruction Pointer: Points to the current operation being evaluated in the program.
static int sp = -1; // Stack Pointer: Points to the top value of the stack.
static int stack[256]; // VM's stack array.

static bool running = true; // Boolean value indicating whether the program is currently running.
static bool trace = true; // Boolean value indicating whether the stack is being traced.

static const int *PROGRAM;

void push(int val); // Adds an item to the top of the stack.
int pop(); // Pops off the top-most item on the stack.

void eval(int op); // Evaluates an individual operation based on the stack.
int fetch(); // Returns the current operation being evaluated.
void printStackTrace(int ip, int op);

void runProgram(const int *program);

#endif // VIRTUALMACHINE_H
