#ifndef BYTECODE_H
#define BYTECODE_H

typedef enum {
	PUSH,
	ADD,
	POP,
	SET,
	PRINT,
	HALT
} Opcodes;

static char *OPCODES[] = {
	"PUSH",
	"ADD",
	"POP",
	"SET",
	"PRINT",
	"HALT"
};

#endif // BYTECODE_H
