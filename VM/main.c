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
	1, 0,
	14, 0,
	1, 1,
	1, 1,
	7,
	18, 23,
	1, 1,
	14, 0,
	1, 2,
	14, 0,
	1, 3,
	14, 0,
	1, 1,
	14, 1,
	HALT
};

int main() {
	//runProgram(program, 18, 0);
	runProgram(program, 0, 3);
	return 0;
}
