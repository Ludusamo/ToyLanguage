#include "Bytecode.h"
#include "VirtualMachine.h"
#include <stdio.h>
#include <stdlib.h>

/*const int program[23] {
	// FUNCTION A()
	PUSH, 0,  // int B

	PUSH, 0,  // int C

	PUSH, 2,  //| B = 2
	STORE, 1, //|

	PUSH, 3,  //| C = 3
	STORE, 2, //| 

	LOAD, 1,  //| return B + C
	LOAD, 2,  //|
	ADDI,     //|
	RET,      //|

	// MAIN FUNCTION
	CALL, 0, 0,
	PRINTI,
	HALT 
};*/

const int program[] = {
	PUSH, 1,
	GSTORE, 0,
	GLOAD, 0,
	PUSH, 1,
	EQ,
	BRF, 17,
	PUSH, 0,
	PUSH, 0,
	STORE, 1,
	POP,
	PUSH, 0,
	GSTORE, 1,
	HALT
};

int *program1;

int main() {
	//runProgram(program, 18, 0);
	FILE *bytecode;

	int mainMethod;
	fscanf(bytecode, "%d", &mainMethod);

	int programIndex = 0;
	int byte;
	while (fscanf(bytecode, "%d", &byte) != -1) {
		program1[programIndex] = byte;
		programIndex++;
	}

	runProgram(program1, mainMethod, 3);
	return 0;
}
