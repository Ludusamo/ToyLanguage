#ifndef BYTECODE_H
#define BYTECODE_H

typedef struct {
	const char *name;
	int numOps;
} Operation;

Operation new_op(const char *name, int numOps);

typedef enum {
	HALT,
	PUSH,
	POP,
	ADDI,
	SUBI,
	MULI,
	DIVI,
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
	PRINTC,
} Opcodes;

static Operation OPERATIONS[] = {
	new_op("HALT", 0),
	new_op("PUSH", 1),
	new_op("POP", 0),
	new_op("ADDI", 0),
	new_op("SUBI", 0),
	new_op("MULI", 0),
	new_op("DIVI", 0),
	new_op("GSTORE", 1),
	new_op("GLOAD", 1),
	new_op("BR", 1),
	new_op("BRT", 1),
	new_op("BRF", 1),
	new_op("LOAD", 1),
	new_op("STORE", 1),
	new_op("CALL", 2),
	new_op("RET", 0),
	new_op("PRINTI", 0),
	new_op("PRINTC", 0)
};

#endif // BYTECODE_H
