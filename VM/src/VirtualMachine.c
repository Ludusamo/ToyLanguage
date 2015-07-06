#include "VirtualMachine.h"

#include <stdio.h>
#include <string.h>

#include "Bytecode.h"

void push(int val) {
	stack[++sp] = val;
}

int pop() {
	return stack[sp--];
}

void eval(int op) {
	switch(op) {
		case PUSH: {
			push(PROGRAM[++ip]);
			break;
		}
		case ADD: {
			int a = pop(); // Pops off the top value from the stack.
			int b = pop(); // Pops off the next value from the stack.

			int result = a + b;
			// Push the result on to the stack.
			push(result);
			break;
		}
		case POP: {
			int val_popped = pop();
			printf("Popped %d\n", val_popped);
			break;
		}
		case HALT: {
			running = false;
			break;
		}
	}
}

int fetch() {
	return PROGRAM[ip];
}

void printStackTrace(int ip, int op) {
	printf("%04d: %s %*s", ip, OPCODES[op], (int) (10 - strlen(OPCODES[op])), "[ ");
	for (int i = 0; i < sp + 1; i++) {
		printf("%d ", stack[i]);
	}
	printf("]\n");
}

void runProgram(const int *program) {
	PROGRAM = program;	
	while (running) {
		int op = fetch();
		eval(op);
		if (trace) printStackTrace(ip, op);
		ip++;
	}	
}
