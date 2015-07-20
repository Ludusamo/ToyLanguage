#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <stdio.h>
#include "Statement.h"
#include "Memory.h"
#include "Token.h"
#include "StringUtil.h"

typedef enum {
	HALT,
	PUSH,
	POP,
	ADDI,
	SUBI,
	MULI,
	DIVI,
	EQ,
	LT,
	GT,
	LTE,
	GTE,
	AND,
	OR,
	GSTORE,
	GLOAD,
	BR,
	BRT,
	BRF,
	LOAD,
	STORE,
	CALL,
	RET,
	PRINTI,
	PRINTC
} Opcodes;

class Compiler {
public:
	std::vector<int> compileDeclaration(Statement &statement);
private:
	std::vector<int> bytecode;
	Memory mem;

	void compileValue(Statement &statement, int index);
};

#endif // COMPILER_H
