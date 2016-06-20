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
	return instructions;
}

void compile_decl(Linked_List *instructions, ASTNode *decl, int depth) {
	int addr;
	if (depth == 0) addr = get_global_addr(GET_AST_DECL_ID(decl));
	else addr = get_local_offset(GET_AST_DECL_ID(decl));
	compile_rhs(instructions, SUB_NODE(decl, 2));

	if (depth == 0) add_link(instructions, GSTORE_OP);
	else add_link(instructions, STORE_OP);
	add_link(instructions, addr);
}

void compile_rhs(Linked_List *instructions, ASTNode *rhs) {
	switch (NODE_TYPE(rhs)) {
	case CONST_NODE:
		compile_const(instructions, rhs);
		break;
	case ARITHOP_NODE:
		compile_rhs(instructions, SUB_NODE(rhs, 0));
		compile_rhs(instructions, SUB_NODE(rhs, 1));
		compile_arithop(instructions, rhs);
		break;
	case BOOLOP_NODE:
		compile_rhs(instructions, SUB_NODE(rhs, 0));
		compile_rhs(instructions, SUB_NODE(rhs, 1));
		compile_boolop(instructions, rhs);
		break;
	case VAR_NODE:
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

void compile_boolop(Linked_List *instructions, ASTNode *arithop) {

}

void compile_const(Linked_List *instructions, ASTNode *const_node) {
	add_link(instructions, PUSH_OP);
	add_link(instructions, GET_CONST_INT(const_node));
}
