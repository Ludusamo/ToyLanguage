#include "Bytecode.h"
#include "VirtualMachine.h"

const int program[] {
	// FUNCTION A()
	PUSH, 0,  // int B

	PUSH, 0,  // int C

	PUSH, 2,  //| B = 2
	STORE, 1, //|

	PUSH, 3,  //| C = 3
	STORE, 2, //| 

	LOAD, 1,  //| return B + C
	LOAD, 2,  //|
	ADD,      //|
	RET,      //|

	// MAIN FUNCTION
	CALL, 0, 0,
	PRINT,
	HALT 
};

int main() {
	runProgram(program, 18, 0);
	return 0;
}
