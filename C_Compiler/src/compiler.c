#include "compiler.h"

Linked_List *compile(ASTNode *program) {
	Linked_List *instructions = create_linked_list();
	instruction_sp = 0;
	prev_depth = 0;
	for (int i = 0; i < num_lines; i++) {
		ASTNode *node = SUB_NODE(program, i);
		if (instruction_sp != 0) {
				printf("%d %d\n", node->depth, prev_depth);
			if (node->depth < prev_depth) {
				for (int i = 0; i < prev_depth - node->depth; i++) {
					Link *unknown = unknown_instruction_stack[--instruction_sp];
					unknown->val = instructions->length;
				}
			}
		}
		switch (NODE_TYPE(node)) {
		case DECL_NODE:
			compile_decl(instructions, node, node->depth);
			break;
		case ASSIGN_NODE:
			compile_assign(instructions, node, node->depth);
			break;
		case IF_NODE:
			compile_if(instructions, node, node->depth);
			break;
		}
		prev_depth = node->depth;
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

void compile_assign(Linked_List *instructions, ASTNode *assign, int depth) {
	Memory_Address *addr;
	char *id = GET_AST_STR_DATA(SUB_NODE(assign, 0));
	if (depth == 0) addr = get_global_addr(id);
	else addr = get_local_addr(id);
	compile_rhs(instructions, SUB_NODE(assign, 1), depth);

	if (depth == 0) add_link(instructions, GSTORE_OP);
	else add_link(instructions, STORE_OP);
	add_link(instructions, addr->addr);
}

void compile_if(Linked_List *instructions, ASTNode *if_node, int depth) {
	compile_rhs(instructions, SUB_NODE(if_node, 0), depth);	
	add_link(instructions, BRF_OP);
	add_link(instructions, 0);
	unknown_instruction_stack[instruction_sp++] = instructions->tail;
}

void compile_rhs(Linked_List *instructions, ASTNode *rhs, int depth) {
	switch (NODE_TYPE(rhs)) {
	case CONST_NODE:
		compile_const(instructions, rhs);
		break;
	case OPERATOR_NODE:
		compile_rhs(instructions, SUB_NODE(rhs, 0), depth);
		compile_rhs(instructions, SUB_NODE(rhs, 1), depth);
		compile_operator(instructions, rhs);
		break;
	case VAR_NODE:
		if (depth == 0) compile_global_var(instructions, rhs);
		else {
			// TODO
		}
		break;
	}
}

void compile_operator(Linked_List *instructions, ASTNode *arithop) {
	int type = GET_OP_TYPE(arithop);
	int op;
	if (type == EQ) op = EQ_OP;
	if (type == NEQ) op = NEQ_OP;
	if (type == LT) op = LT_OP;
	if (type == GT) op = GT_OP;
	if (type == LTE) op = LTE_OP;
	if (type == GTE) op = GTE_OP;
	if (type == OR) op = OR_OP;
	if (type == AND) op = AND_OP;
	if (type == PLUS) op = ADDI_OP;
	if (type == MINUS) op = SUBI_OP;
	if (type == MULTIPLY) op = MULI_OP;
	if (type == DIVIDE) op = DIVI_OP;
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
