#include "Bytecode.h"
#include "VirtualMachine.h"

const int program[] {
	// FUNCTION A()
	PUSH, 0, // int B
	PUSH, 0, // int C
	PUSH, 2,
	STORE, 1,
	PUSH, 3,
	STORE, 2,
	LOAD, 1,
	LOAD, 2,
	ADD,
	RET, // 2

	// MAIN FUNCTION
	CALL, 0, 0,
	PRINT,
	HALT 
};

int main() {
	runProgram(program, 18, 0);
	return 0;
}
