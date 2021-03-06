#ifndef BYTECODE_H
#define BYTECODE_H

typedef struct {
	const char *name;
	int numOps;
} Operation;

typedef enum {
	HALT,
	PUSH,
	POP,
	LSHIFT,
	RSHIFT,
	ADDI,
	SUBI,
	MULI,
	DIVI,
	MODI,
	BAND,
	BOR,
	BXOR,
	EQ,
	NEQ,
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
	PRINTC,
	NUM_OP_CODES
} Opcodes;

static Operation OPERATIONS[NUM_OP_CODES] = {
	{"HALT", 0},
	{"PUSH", 1},
	{"POP", 0},
	{"LSHIFT", 0},
	{"RSHIFT", 0},
	{"ADDI", 0},
	{"SUBI", 0},
	{"MULI", 0},
	{"DIVI", 0},
	{"MODI", 0},
	{"BAND", 0},
	{"BOR", 0},
	{"BXOR", 0},
	{"EQ", 0},
	{"NEQ", 0},
	{"LT", 0},
	{"GT", 0},
	{"LTE", 0},
	{"GTE", 0},
	{"AND", 0},
	{"OR", 0},
	{"GSTORE", 1},
	{"GLOAD", 1},
	{"BR", 1},
	{"BRT", 1},
	{"BRF", 1},
	{"LOAD", 1},
	{"STORE", 1},
	{"CALL", 2},
	{"RET", 0},
	{"PRINTI", 0},
	{"PRINTC", 0}
};

#endif // BYTECODE_H
