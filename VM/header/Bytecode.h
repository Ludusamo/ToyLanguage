#ifndef BYTECODE_H
#define BYTECODE_H

typedef enum {
	PUSH,
	ADD,
	SUB,
	MUL,
	DIV,
	POP,
	SET,
	PRINT,
	HALT
} Opcodes;

static char *OPCODES[] = {
	"PUSH",
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"POP",
	"SET",
	"PRINT",
	"HALT"
};

#endif // BYTECODE_H
