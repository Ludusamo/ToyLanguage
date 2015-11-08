#ifndef COMPILER_H
#define COMPILER_H

#include "Memory/Memory.h"

typedef enum {
	HALT, //0
	PUSH, //1
	POP, //2
	ADDI, //3
	SUBI, //4
	MULI, //5
	DIVI, //6
	EQ, //7
	NEQ, //8
	LT, //9
	GT, //10
	LTE, //11
	GTE, //12
	AND, //13
	OR, //14
	GSTORE, // 15
	GLOAD, //16
	BR, //17
	BRT, //18
	BRF, //19
	LOAD, //20
	STORE, //21
	CALL, //22
	RET, //23
	PRINTI, //24
	PRINTC //25
} Opcodes;

class Compiler {
public:
	Compiler() {lineno = -1; currentDepth = -1;};

	std::vector< std::vector<int> > compile(std::vector<Statement> &statements);
	void compileDeclaration(Statement &statement);
	void compileAssignment(Statement &statement);
	void compileGlobalFunction(Statement &statement);
	void compileReturnStatement(Statement &statement, int returnType);
	void compileFunctionCall(Statement &statement);
	void compileIfStatement(Statement &statement);
	void compileElseStatement(Statement &statement);
	void compileWhileStatement(Statement &statement);

	Memory::Function getMainFunction();
private:
	int statementIndex;
	int lineno;
	int currentDepth;
	int bufferIndex;
	int previousDepth; // Check if we have changed depths
	int mainIP;
	Memory mem;

	std::vector<int> bytecode;
	std::vector<int> globalBytecode;

	void compileIntValue(Statement &statement);
	void compileBoolValue(Statement &statement);
};

#endif // COMPILER_H