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
	19, -4,
	19, -3,
	3,
	20, 1,
	19, 1,
	22,
	1, 3,
	1, 4,
	21, 0, 2,
	HALT
};

int main() {
	//runProgram(program, 18, 0);
	runProgram(program, 12, 3);
	return 0;
}
