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
	Compiler() {lineno = -1;};

	std::vector<int> compile(std::vector<Statement> &statements, Memory &mem);
	void compileGlobalDeclaration(Statement &statement, Memory &mem);
	void compileIfStatement(Statement &statement, Memory &mem);
	void compileWhileStatement(Statement &statement, Memory &mem);
private:
	int statementIndex;
	int lineno;
	std::vector<int> placeholderIndex; // In case I need to update a value to branch/jump to
	int previousDepth; // Check if we have changed depths

	std::vector<int> bytecode;

	void compileIntValue(Statement &statement, Memory &mem);
	void compileBoolValue(Statement &statement, Memory &mem);
};

#endif // COMPILER_H
