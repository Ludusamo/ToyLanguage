#include "compiler.h"

Linked_List *compile(ASTNode *program) {
	clear_mem();
	func_depth = -1;
	Linked_List *instructions = create_linked_list();
	instruction_sp = 0;
	prev_depth = 0;
	for (int i = 0; i < num_lines; i++) {
		ASTNode *node = SUB_NODE(program, i);
		if (func_depth != -1) {
			if (node->depth < func_depth) {
				func_depth = -1;
				add_link(instructions, PUSH_OP);
				add_link(instructions, 0);
				add_link(instructions, RET_OP);
			}
		}

		if (instruction_sp != 0) {
			if (node->depth < prev_depth) {
				for (int i = 0; i < prev_depth - node->depth; i++) {
					for (int j = 0; j < local_memory[prev_depth - i - 1]->num_values; j++)
						add_link(instructions, POP_OP);
					exit_depth(prev_depth - i);
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
		case FUNC_NODE:
			compile_func_decl(instructions, node);
			break;
		case RETURN_NODE:
			compile_return(instructions, node);
			break;
		}
		prev_depth = node->depth;
	}
	add_link(instructions, HALT_OP);
	return instructions;
}

void compile_decl(Linked_List *instructions, ASTNode *decl, int depth) {
	Memory_Address *addr;
	if (depth == 0) {
		addr = create_mem_addr(1, NUM_GLOBAL, GET_AST_DATATYPE(decl));
		create_global_variable(GET_AST_DECL_ID(decl), addr);
	} else {
		add_link(instructions, PUSH_OP);
		add_link(instructions, 0);
		addr = create_mem_addr(1, NUM_LOCAL + 1, GET_AST_DATATYPE(decl));
		create_local_variable(GET_AST_DECL_ID(decl), addr, depth);
	}
	compile_rhs(instructions, SUB_NODE(decl, 2), depth);

	if (depth == 0) add_link(instructions, GSTORE_OP);
	else add_link(instructions, STORE_OP);
	add_link(instructions, addr->addr);
}

void compile_assign(Linked_List *instructions, ASTNode *assign, int depth) {
	Memory_Address *addr = 0;
	char *id = GET_AST_STR_DATA(SUB_NODE(assign, 0));
	compile_rhs(instructions, SUB_NODE(assign, 1), depth);
	if (depth > 0) {
		addr = get_local_addr(id, depth);
	}
	if (!addr) {
		add_link(instructions, GSTORE_OP);
		addr = get_global_addr(id);
	} else {
		add_link(instructions, STORE_OP);
	}

	add_link(instructions, addr->addr);
}

void compile_if(Linked_List *instructions, ASTNode *if_node, int depth) {
	compile_rhs(instructions, SUB_NODE(if_node, 0), depth);	
	add_link(instructions, BRF_OP);
	add_link(instructions, 0);
	unknown_instruction_stack[instruction_sp++] = instructions->tail;
}

void compile_func_decl(Linked_List *instructions, ASTNode *func_node) {
	add_link(instructions, BR_OP);
	add_link(instructions, 0);
	unknown_instruction_stack[instruction_sp++] = instructions->tail;
	char *id = GET_AST_STR_DATA(SUB_NODE(func_node, 1));
	Memory_Address *addr = create_mem_addr(1, instructions->length, 0);
	create_function(id, addr);
	func_depth = func_node->depth;
}

void compile_return(Linked_List *instructions, ASTNode *return_node) {
	if (GET_AST_DATATYPE(return_node) != 0) {
		compile_rhs(instructions, SUB_NODE(return_node, 1), 0);
	}
	add_link(instructions, RET_OP);
}

void compile_rhs(Linked_List *instructions, ASTNode *rhs, int depth) {
	switch (NODE_TYPE(rhs)) {
	case CONST_NODE:
		compile_const(instructions, rhs);
		break;
	case OPERATOR_NODE:
		compile_rhs(instructions, SUB_NODE(rhs, 1), depth);
		compile_rhs(instructions, SUB_NODE(rhs, 2), depth);
		compile_operator(instructions, rhs);
		break;
	case VAR_NODE:
		compile_var(instructions, rhs, depth);
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

void compile_var(Linked_List *instructions, ASTNode *var_node, int depth) {
	char *id = GET_AST_STR_DATA(SUB_NODE(var_node, 0));
	Memory_Address *addr = 0;
	while (!addr && depth > 0) {
		addr = get_local_addr(id, depth--);
	}
	if (!addr) {
		add_link(instructions, GLOAD_OP);	
		addr = get_global_addr(id);
	} else {
		add_link(instructions, LOAD_OP);
	}
	add_link(instructions, addr->addr);
}
