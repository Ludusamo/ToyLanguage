#include "Bytecode.h"
#include "VirtualMachine.h"

const int program[] {
	PUSH, 5,
	PUSH, 5,
	DIV,
	PRINT,
	HALT
};

int main() {
	runProgram(program, 0);
	return 0;
}
