#ifndef BYTECODE_H
#define BYTECODE_H

typedef enum {
	PUSH,
	ADD,
	POP,
	SET,
	HALT
} Opcodes;

static char *OPCODES[] = {
	"PUSH",
	"ADD",
	"POP",
	"SET",
	"HALT"
};

#endif // BYTECODE_H
