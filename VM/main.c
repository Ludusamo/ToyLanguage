#include "Bytecode.h"
#include "VirtualMachine.h"

const int program[] {
	PUSH, 2,
	PUSH, 0, //0
	BRT, 8,
	GSTORE, 0,
	PRINT,//6
	HALT
};

int main() {
	runProgram(program, 0, 1);
	return 0;
}
