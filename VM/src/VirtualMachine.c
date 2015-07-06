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
			registers[A] = pop(); // Pops off the top value from the stack.
			registers[B] = pop(); // Pops off the next value from the stack.

			registers[C] = registers[A] + registers[B];
			// Push the result on to the stack.
			push(registers[C]);
			break;
		}
		case SUB: {
			registers[A] = pop();
			registers[B] = pop();
			registers[C] = registers[B] - registers[A];
			push(registers[C]);
			break;
		}
		case MUL: {
			registers[A] = pop();
			registers[B] = pop();
			registers[C] = registers[A] * registers[B];
			push(registers[C]);
			break;
		}
		case DIV: {
			registers[A] = pop();
			registers[B] = pop();
			registers[C] = registers[B] / registers[A];
			push(registers[C]);
			break;
		}
		case POP: {
			pop();
			break;
		}
		case PRINT: {
			int val = pop();
			printf("%d\n", val);
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

void runProgram(const int *program, const int mainIndex) {
	ip = mainIndex;
	PROGRAM = program;	
	while (running) {
		int op = fetch();
		eval(op);
		if (trace) printStackTrace(ip, op);
		ip++;
	}	
}
