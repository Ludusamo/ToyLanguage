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
	PUSH, 104,
	PRINTC,
	PUSH, 101,
	PRINTC,
	PUSH, 108,
	PRINTC,
	PUSH, 108,
	PRINTC,
	PUSH, 111,
	PRINTC,
	PUSH, 44,
	PRINTC,
	PUSH, 32,
	PRINTC,
	PUSH, 119,
	PRINTC,
	PUSH, 111,
	PRINTC,
	PUSH, 114,
	PRINTC,
	PUSH, 108,
	PRINTC,
	PUSH, 100,
	PRINTC,
	PUSH, 10,
	PRINTC,

	HALT
};

int main() {
	//runProgram(program, 18, 0);
	runProgram(program, 0, 0);
	return 0;
}
