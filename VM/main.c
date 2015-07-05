#include <stdio.h>

#include "Bytecode.h"

int ip = 0; // Instruction Pointer: Points to the current operation being evaluated in the program.
int sp = -1; // Stack Pointer: Points to the top value of the stack.
int stack[256]; // VM's stack array.

bool running = true; // Boolean value indicating whether the program is currently running.
bool trace = false;

const int PROGRAM[] {
	PSH, 5,
	PSH, 6,
	ADD,
	POP,
	HLT
};

// Evaluates an individual operation based on the stack.
void eval(int op) {
	switch(op) {
	case PSH: {
		sp++;
		stack[sp] = PROGRAM[++ip];
		break;
	}
	case ADD: {
		int a = stack[sp--]; // Pops off the top value from the stack.
		int b = stack[sp--]; // Pops off the next value from the stack.

		int result = a + b;
		// Push the result on to the stack.
		sp++;
		stack[sp] = result;
		break;
	}
	case POP: {
		int val_popped = stack[sp--];
		printf("Popped %d\n", val_popped);
		break;
	}
	case HLT: {
		running = false;
		break;
	}
	}
}

// Returns the current operation being evaluated.
int fetch() {
	return PROGRAM[ip];
}

int main() {
	while (running) {
		int op = fetch();
		eval(op);
		ip++;
	}
	return 0;
}
