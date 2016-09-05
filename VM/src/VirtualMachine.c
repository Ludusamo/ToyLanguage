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

void popIntoRegister(int numToPop) {
	for (int i = 0; i < numToPop; i++) {
		registers[i] = pop();
	}
}

void eval(int op) {
	switch(op) {
		case HALT: 
			running = 0;
			break;
		case PUSH: 
			push(getNextOperand());
			break;
		case POP: 
			pop();
			break;
		case LSHIFT:
			popIntoRegister(2);
			push(registers[B] << registers[A]);
			break;
		case RSHIFT:
			popIntoRegister(2);
			push(registers[B] >> registers[A]);
			break;
		case ADDI: 
			popIntoRegister(2);
			push(registers[A] + registers[B]);
			break;
		case SUBI: 
			popIntoRegister(2);
			push(registers[B] - registers[A]);
			break;
		case MULI: 
			popIntoRegister(2);
			push(registers[A] * registers[B]);
			break;
		case DIVI: 
			popIntoRegister(2);
			push(registers[B] / registers[A]);
			break;
		case MODI:
			popIntoRegister(2);
			push(registers[B] % registers[A]);
			break;
		case BAND:
			popIntoRegister(2);
			push(registers[B] & registers[A]);
			break;
		case BOR:
			popIntoRegister(2);
			push(registers[B] | registers[A]);
			break;
		case BXOR:
			popIntoRegister(2);
			push(registers[B] ^ registers[A]);
			break;
		case EQ: 
			popIntoRegister(2);
			push(registers[A] == registers[B]);
			break;
		case NEQ:
			popIntoRegister(2);
			push(registers[A] != registers[B]);
			break;
		case LT: 
			popIntoRegister(2);
			push(registers[B] < registers[A]);
			break;
		case GT:
			popIntoRegister(2);
			push(registers[B] > registers[A]);
			break;
		case LTE:
			popIntoRegister(2);
			push(registers[B] <= registers[A]);
			break;
		case GTE:
			popIntoRegister(2);
			push(registers[B] >= registers[A]);
			break;
		case AND:
			popIntoRegister(2);
			push(registers[B] && registers[A]);
			break;
		case OR:
			popIntoRegister(2);
			push(registers[B] || registers[A]);
			break;
		case GSTORE:
			registers[A] = getNextOperand();		
			gmem[registers[A]] = pop();
			break;
		case GLOAD:
			registers[A] = getNextOperand();
			push(gmem[registers[A]]);
			break;
		case BR:
			ip = getNextOperand() - 1;
			break;
		case BRT: 
			registers[A] = getNextOperand() - 1;
			if (pop() == 1) ip = registers[A];
			break;
		case BRF:
			registers[A] = getNextOperand() - 1;
			if (pop() == 0) ip = registers[A];
			break;
		case LOAD:
			registers[A] = getNextOperand(); // Offset
			push(stack[fp + registers[A]]);
			break;
		case STORE:
			registers[A] = getNextOperand(); // Offset
			registers[B] = pop(); // Value to Store
			stack[fp + registers[A]] = registers[B];
			break;
		case CALL:
			registers[A] = getNextOperand() - 1; // Address
			registers[B] = getNextOperand(); // Num Args
			push(registers[B]);
			push(fp);
			push(ip);
			fp = sp;
			ip = registers[A];
			break;
		case RET:
			registers[A] = pop(); // Return Value
			sp = fp;
			ip = pop();
			fp = pop();
			registers[B] = pop(); // Num Args
			sp -= registers[B];
			push(registers[A]);
			break;
		case PRINTI:
			registers[A] = pop();
			printf("%d\n", registers[A]);
			break;
		case PRINTC: 
			registers[A] = pop();
			if (registers[A] > 127) {
				running = 0;
				ThrowError(INVALID_CHARACTER_EXCEPTION);	
				break;
			}
			printf("%c", registers[A]);
			break;
	}
}

int fetch() {
	return PROGRAM[ip];
}

void runProgram(const int *program, const int mainIndex, const int gMemSize) {
	running = 1;
	ip = mainIndex;
	sp = -1;
	fp = -1;
	PROGRAM = program;	
	gmem = (int *) malloc(sizeof(int) * gMemSize);
	while (running) {
		int op = fetch();
		if (trace) printStackTrace(ip, sp, op, PROGRAM, stack);
		eval(op);
		ip++;
	}	
	if (trace) dumpMemory(gMemSize, gmem);
}
