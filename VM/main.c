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
	19, -3,
	20, 1,
	19, 1,
	22,
	1, 0,
	1, 3,
	20, 1,
	21, 0, 1,
	HALT
};

int main() {
	//runProgram(program, 18, 0);
	runProgram(program, 9, 3);
	return 0;
}
