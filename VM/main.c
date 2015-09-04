#include "Bytecode.h"
#include "VirtualMachine.h"

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
	GLOAD, 0,
	BRF, 13,
	PUSH, 0,
	GSTORE, 0,
	CALL, 0, 0,
	GLOAD, 0,
	RET,
	PUSH, 1,
	GSTORE, 0,
	CALL, 0, 0,
	GSTORE, 1,
	HALT
};

int main() {
	//runProgram(program, 18, 0);
	runProgram(program, 14, 3);
	return 0;
}
