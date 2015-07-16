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

const int program[] {
	PUSH, 10,  // 0, 1
	GSTORE, 0, // 2, 3
	PUSH, 10,  // 4, 5
	GSTORE, 1, // 6, 7
	GLOAD, 0,  // 8, 9
	GLOAD, 1,  // 10, 11
	EQ,        // 12
	BRF, 21,   // 13, 14
	PUSH, 104, // 15, 16
	PRINTC,    // 17
	PUSH, 105, // 18, 19
	PRINTC,    // 20
	HALT       // 21
};

int main() {
	//runProgram(program, 18, 0);
	runProgram(program, 0, 0);
	return 0;
}
