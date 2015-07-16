#include "VirtualMachine.h"

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
		case ADDI: {
			registers[A] = pop();
			registers[B] = pop();
			registers[C] = registers[A] + registers[B];
			push(registers[C]);
			break;
		}
		case SUBI: {
			registers[A] = pop();
			registers[B] = pop();
			registers[C] = registers[B] - registers[A];
			push(registers[C]);
			break;
		}
		case MULI: {
			registers[A] = pop();
			registers[B] = pop();
			registers[C] = registers[A] * registers[B];
			push(registers[C]);
			break;
		}
		case DIVI: {
			registers[A] = pop();
			registers[B] = pop();
			registers[C] = registers[B] / registers[A];
			push(registers[C]);
			break;
		}
		case EQ: {
			registers[A] = pop();
			registers[B] = pop();
			push(registers[A] == registers[B]);
			break;
		}
		case LT: {
			registers[A] = pop();
			registers[B] = pop();
			push(registers[B] < registers[A]);
			break;
		}
		case GT: {
			registers[A] = pop();
			registers[B] = pop();
			push(registers[B] > registers[A]);
			break;
		}
		case LTE: {
			registers[A] = pop();
			registers[B] = pop();
			push(registers[B] <= registers[A]);
			break;
		}
		case GTE: {
			registers[A] = pop();
			registers[B] = pop();
			push(registers[B] >= registers[A]);
			break;
		}
		case AND: {
			registers[A] = pop();
			registers[B] = pop();
			push(registers[B] && registers[A]);
			break;
		}
		case OR: {
			registers[A] = pop();
			registers[B] = pop();
			push(registers[B] || registers[A]);
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
		case PRINTI: {
			registers[A] = pop();
			printf("%d\n", registers[A]);
			break;
		}	
		case PRINTC: {
			registers[A] = pop();
			printf("%c", registers[A]);
			break;
		}
	}
}

int fetch() {
	return PROGRAM[ip];
}

void runProgram(const int *program, const int mainIndex, const int gMemSize) {
	running = true;
	trace = true;
	ip = mainIndex;
	sp = -1;
	PROGRAM = program;	
	gmem = new int[gMemSize];
	while (running) {
		int op = fetch();
		if (trace) printStackTrace(ip, sp, op, PROGRAM, stack);
		eval(op);
		ip++;
	}	
	if (trace) dumpMemory(gMemSize, gmem);
}
