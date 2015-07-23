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
	std::vector<int> compileDeclaration(Statement &statement, Memory &mem);
	std::vector<int> compileIfStatement(Statement &statement);
	std::vector<int> compileWhileStatement(Statement &statement);
private:
	std::vector<int> bytecode;

	void compileIntValue(Statement &statement, int index);
	void compileBoolValue(Statement &statement, int index);
};

#endif // COMPILER_H
