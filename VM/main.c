#include "Bytecode.h"
#include "VirtualMachine.h"
#include <stdio.h>
#include <stdlib.h>

int *program;
int num_global = 256;

int main(int argc, const char* argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Insufficient Arguments\n");
	} else if (argc == 2) {
		FILE *bytecode = fopen(argv[1], "r");
		if (!bytecode) {
			fprintf(stderr, "File %s Does Not Exist\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		int mainMethod;
		fscanf(bytecode, "%d", &mainMethod);
		int programIndex = 0;
		int byte;
		program = calloc(sizeof(int), 1024);
		while (fscanf(bytecode, "%d", &byte) != -1) {
			program[programIndex++] = byte;
		}

		runProgram(program, mainMethod, num_global);
	} else {
		fprintf(stderr, "Too Many Arguments\n");
	}
	return 0;
}
