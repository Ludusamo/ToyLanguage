#include "Bytecode.h"
#include "VirtualMachine.h"

const int program[] {
	PUSH, 5,
	PUSH, 6,
	ADD,
	PRINT,
	HALT
};

int main() {
	runProgram(program);
	return 0;
}
