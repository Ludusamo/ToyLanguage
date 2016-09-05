#ifndef COMPILER_H
#define COMPILER_H

#include "pda.h"
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
	MODI_OP,
	BAND_OP,
	BOR_OP,
	BXOR_OP,
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

int pda_sp;
struct PDA *pda_stack[255];
int prev_depth;
int func_depth;

Linked_List *compile(ASTNode *program);
void compile_decl(Linked_List *instructions, ASTNode *decl, int depth);
void compile_assign(Linked_List *instructions, ASTNode *assign, int depth);
void compile_if(Linked_List *instructions, ASTNode *if_node, int depth);
void compile_while(Linked_List *instructions, ASTNode *while_node, int depth);
void compile_func_decl(Linked_List *instructions, ASTNode *func_node);
void compile_return(Linked_List *instructions, ASTNode *return_node);
void compile_func_call(Linked_List *instructions, ASTNode *func_call);
void compile_rhs(Linked_List *instructions, ASTNode *rhs, int depth);
void compile_operator(Linked_List *instructions, ASTNode *op_node);
void compile_const(Linked_List *instructions, ASTNode *const_node);
void compile_var(Linked_List *instructions, ASTNode *var_node, int depth);

void compile_print(Linked_List *instructions, ASTNode *print_node); //TODO: REMOVE

#endif // COMPILER_H
