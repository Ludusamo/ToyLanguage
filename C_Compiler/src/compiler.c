#include "compiler.h"

Linked_List *compile(ASTNode *program) {
	Linked_List *instructions = create_linked_list();
	for (int i = 0; i < num_lines; i++) {
		switch (NODE_TYPE(SUB_NODE(program, i))) {
		case DECL_NODE:
			compile_decl(instructions, SUB_NODE(program,i), 0);
			break;
		}
	}
	add_link(instructions, HALT_OP);
	return instructions;
}

void compile_decl(Linked_List *instructions, ASTNode *decl, int depth) {
	Memory_Address *addr;
	if (depth == 0) addr = get_global_addr(GET_AST_DECL_ID(decl));
	else addr = get_local_addr(GET_AST_DECL_ID(decl));
	compile_rhs(instructions, SUB_NODE(decl, 2), depth);

	if (depth == 0) add_link(instructions, GSTORE_OP);
	else add_link(instructions, STORE_OP);
	add_link(instructions, addr->addr);
}

void compile_rhs(Linked_List *instructions, ASTNode *rhs, int depth) {
	switch (NODE_TYPE(rhs)) {
	case CONST_NODE:
		compile_const(instructions, rhs);
		break;
	case ARITHOP_NODE:
		compile_rhs(instructions, SUB_NODE(rhs, 0), depth);
		compile_rhs(instructions, SUB_NODE(rhs, 1), depth);
		compile_arithop(instructions, rhs);
		break;
	case BOOLOP_NODE:
		compile_rhs(instructions, SUB_NODE(rhs, 0), depth);
		compile_rhs(instructions, SUB_NODE(rhs, 1), depth);
		compile_boolop(instructions, rhs);
		break;
	case VAR_NODE:
		if (depth == 0) compile_global_var(instructions, rhs);
		else {
			// TODO
		}
		break;
	}
}

void compile_arithop(Linked_List *instructions, ASTNode *arithop) {
	int type = GET_OP_TYPE(arithop);
	int op;
	if (type == PLUS) op = ADDI_OP;
	if (type == MINUS) op = SUBI_OP;
	if (type == MULTIPLY) op = MULI_OP;
	if (type == DIVIDE) op = DIVI_OP;
	add_link(instructions, op);
}

void compile_boolop(Linked_List *instructions, ASTNode *boolop) {
	int type = GET_OP_TYPE(boolop);
	int op;
	if (type == EQ) op = EQ_OP;
	if (type == NEQ) op = NEQ_OP;
	if (type == LT) op = LT_OP;
	if (type == GT) op = GT_OP;
	if (type == LTE) op = LTE_OP;
	if (type == GTE) op = GTE_OP;
	add_link(instructions, op);
}

void compile_const(Linked_List *instructions, ASTNode *const_node) {
	add_link(instructions, PUSH_OP);
	add_link(instructions, GET_CONST_INT(const_node));
}

void compile_global_var(Linked_List *instructions, ASTNode *var_node) {
	add_link(instructions, GLOAD_OP);	
	add_link(instructions, get_global_addr(GET_AST_STR_DATA(SUB_NODE(var_node, 0)))->addr);
}
