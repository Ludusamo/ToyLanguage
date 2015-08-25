#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <stdio.h>
#include "Statement.h"
#include "Memory.h"
#include "Token.h"
#include "StringUtil.h"

typedef enum {
	HALT, //0
	PUSH, //1
	POP, //2
	ADDI, //3
	SUBI, //4
	MULI, //5
	DIVI, //6
	EQ, //7
	LT, //8
	GT, //9
	LTE, //10
	GTE, //11
	AND, //12
	OR, //13
	GSTORE, // 14
	GLOAD, //15
	BR, //16
	BRT, //17
	BRF, //18
	LOAD, //19
	STORE, //20
	CALL, //21
	RET, //22
	PRINTI, //23
	PRINTC //24
} Opcodes;

class Compiler {
public:
	Compiler() {lineno = -1;};

	std::vector<int> compile(std::vector<Statement> &statements);
	void compileDeclaration(Statement &statement);
	void compileAssignment(Statement &statement);
	void compileGlobalFunction(Statement &statement);
	void compileReturnStatement(Statement &statement, int returnType);
	void compileFunctionCall(Statement &statement);
	void compileIfStatement(Statement &statement);
	void compileWhileStatement(Statement &statement);
private:
	int statementIndex;
	int lineno;
	int currentDepth;
	std::vector<int> placeholderIndex; // In case I need to update a value to branch/jump to
	int previousDepth; // Check if we have changed depths
	Memory mem;

	std::vector<int> bytecode;

	void compileIntValue(Statement &statement);
	void compileBoolValue(Statement &statement);
};

#endif // COMPILER_H
