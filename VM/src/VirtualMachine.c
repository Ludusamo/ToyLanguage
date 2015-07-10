#include "VirtualMachine.h"

#include <stdio.h>
#include <string.h>

#include "Bytecode.h"

#define ip registers[IP]
#define sp registers[SP]
#define fp registers[FP]

void push(int val) {
	stack[++sp] = val;
}

int pop() {
	return stack[sp--];
}

int getNextOperand() {
	return PROGRAM[++ip];
}

void eval(int op) {
	switch(op) {
		case HALT: {
			running = false;
			break;
		}
		case PUSH: {
			push(getNextOperand());
			break;
		}
		case POP: {
			pop();
			break;
		}
		case ADD: {
			registers[A] = pop();
			registers[B] = pop();
			registers[C] = registers[A] + registers[B];
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
		case GSTORE: {
			registers[A] = getNextOperand();		
			gmem[registers[A]] = pop();
			break;
		}	     
		case GLOAD: {
			registers[A] = getNextOperand();
			push(gmem[registers[A]]);
			break;
		}
		case BR: {
			ip = getNextOperand() - 1;
			break;
		}
		case BRT: {
			registers[A] = getNextOperand() - 1;
			if (pop() == 1) ip = registers[A];
			break;
		}
		case BRF: {
			registers[A] = getNextOperand() - 1;
			if (pop() == 0) ip = registers[A];
			break;
		}
		case LOAD: {
			registers[A] = getNextOperand(); // Offset
			push(stack[fp + registers[A]]);
			break;
		}
		case STORE: {
			registers[A] = getNextOperand(); // Offset
			registers[B] = pop(); // Value to Store
			stack[fp + registers[A]] = registers[B];
			break;
		}
		case CALL: {
			registers[A] = getNextOperand() - 1; // Address
			registers[B] = getNextOperand(); // Num Args
			push(registers[B]);
			push(fp);
			push(ip);
			fp = sp;
			ip = registers[A];
			break;
		}
		case RET: {
			registers[A] = pop(); // Return Value
			sp = fp;
			ip = pop();
			fp = pop();
			registers[B] = pop(); // Num Args
			sp -= registers[B];
			push(registers[A]);
			break;
		}
		case PRINT: {
			int val = pop();
			printf("%d\n", val);
			break;
		}	
	}
}

int fetch() {
	return PROGRAM[ip];
}

void printStackTrace(int op) {
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

void printGlobalMemory(int gMemSize) {
	printf("\n[ ");	
	for (int i = 0; i < gMemSize; i++) {
		printf("%i ", gmem[i]);
	}
	printf("]\n");
}

void runProgram(const int *program, const int mainIndex, const int gMemSize) {
	ip = mainIndex;
	sp = -1;
	PROGRAM = program;	
	gmem = new int[gMemSize];
	while (running) {
		int op = fetch();
		if (trace) printStackTrace(op);
		eval(op);
		ip++;
	}	
	printGlobalMemory(gMemSize);
}
