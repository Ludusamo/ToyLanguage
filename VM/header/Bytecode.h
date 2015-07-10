#ifndef BYTECODE_H
#define BYTECODE_H

typedef struct {
	char *name;
	int numOps;
} Operation;

Operation new_op(char *name, int numOps);

typedef enum {
	HALT,
	PUSH,
	POP,
	ADD,
	SUB,
	MUL,
	DIV,
	GSTORE,
	GLOAD,
	BR,
	BRT,
	BRF,
	LOAD,
	STORE,
	CALL,
	RET,
	PRINT
} Opcodes;

static Operation OPERATIONS[] = {
	new_op("HALT", 0),
	new_op("PUSH", 1),
	new_op("POP", 0),
	new_op("ADD", 0),
	new_op("SUB", 0),
	new_op("MUL", 0),
	new_op("DIV", 0),
	new_op("GSTORE", 1),
	new_op("GLOAD", 1),
	new_op("BR", 1),
	new_op("BRT", 1),
	new_op("BRF", 1),
	new_op("LOAD", 1),
	new_op("STORE", 1),
	new_op("CALL", 2),
	new_op("RET", 0),
	new_op("PRINT", 0)
};

#endif // BYTECODE_H
