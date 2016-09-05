#include "Bytecode.h"
#include "VirtualMachine.h"
#include <stdio.h>
#include <stdlib.h>

int *program;
int num_global = 256;

int main(int argc, const char* argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Insufficient Arguments\n");
	} else if (argc == 3) {
		FILE *bytecode = fopen(argv[1], "r");
		if (!bytecode) {
			fprintf(stderr, "File %s Does Not Exist\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		trace = atoi(argv[2]);

		int mainMethod;
		fscanf(bytecode, "%d", &mainMethod);

		int num_bytecode;
		fscanf(bytecode, "%d", &num_bytecode);
		program = calloc(sizeof(int), num_bytecode);

		int programIndex = 0;
		int byte;
		while (fscanf(bytecode, "%d", &byte) != -1) {
			program[programIndex++] = byte;
		}

		runProgram(program, mainMethod, num_global);
	} else {
		fprintf(stderr, "Too Many Arguments\n");
	}
	return 0;
}
