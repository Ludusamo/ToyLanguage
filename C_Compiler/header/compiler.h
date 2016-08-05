#ifndef COMPILER_H
#define COMPILER_H

#include "ast.h"
#include "memory.h"
#include "linked_list.h"
#include "shared_values.h"
#include "token.h"

typedef enum {
	HALT_OP,
	PUSH_OP,
	POP_OP,
	ADDI_OP,
	SUBI_OP,
	MULI_OP,
	DIVI_OP,
	EQ_OP,
	NEQ_OP,
	LT_OP,
	GT_OP,
	LTE_OP,
	GTE_OP,
	AND_OP,
	OR_OP,
	GSTORE_OP,
	GLOAD_OP,
	BR_OP,
	BRT_OP,
	BRF_OP,
	LOAD_OP,
	STORE_OP,
	CALL_OP,
	RET_OP,
	PRINTI_OP,
	PRINTC_OP,
	NUM_OP_CODES
} Opcodes;


Linked_List *compile(ASTNode *program);
void compile_decl(Linked_List *instructions, ASTNode *decl, int depth);
void compile_assign(Linked_List *instructions, ASTNode *decl, int depth);
void compile_rhs(Linked_List *instructions, ASTNode *rhs, int depth);
void compile_operator(Linked_List *instructions, ASTNode *arithop);
void compile_const(Linked_List *instructions, ASTNode *const_node);
void compile_global_var(Linked_List *instructions, ASTNode *var_node);

#endif // COMPILER_H
