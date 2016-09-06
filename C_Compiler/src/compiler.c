#include "compiler.h"

Linked_List *compile(ASTNode *program) {
	clear_mem();
	func_depth = -1;
	Linked_List *instructions = create_linked_list();
	pda_sp = 0;
	prev_depth = 0;
	for (int i = 0; i < num_lines + 1; i++) {
		ASTNode *node = SUB_NODE(program, i);

		if (pda_sp != 0) {
			if (node->depth < prev_depth) {
				for (int i = 0; i < prev_depth - node->depth; i++) {
					for (int j = 0; j < local_memory[prev_depth - i - 1]->num_values; j++)
						add_link(instructions, POP_OP);
					exit_depth(prev_depth - i);
					PDA *pda = pda_stack[--pda_sp];
					pda->execute(pda);
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
		case WHILE_NODE:
			compile_while(instructions, node, node->depth);
			break;
		case FUNC_NODE:
			compile_func_decl(instructions, node);
			break;
		case RETURN_NODE:
			compile_return(instructions, node);
			break;
		case FUNC_CALL_NODE:
			compile_func_call(instructions, node);
			break;
		case PRINT_NODE:
			compile_print(instructions, node);
			break;
		default:
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
	pda_stack[pda_sp++] = create_if_pda(instructions, instructions->tail);
}

void compile_while(Linked_List *instructions, ASTNode *while_node, int depth) {
	int *beg_branch_index = malloc(sizeof(int));
	*beg_branch_index = instructions->length;
	compile_rhs(instructions, SUB_NODE(while_node, 0), depth);
	add_link(instructions, BRF_OP);
	add_link(instructions, 0);
	pda_stack[pda_sp++] = create_while_pda(instructions, instructions->tail, beg_branch_index);
}

void compile_func_decl(Linked_List *instructions, ASTNode *func_node) {
	ASTNode *arg_list = SUB_NODE(func_node, 2);
	for (int i = 0; i < arg_list->num_sub; i++) {
		char *id = GET_AST_DECL_ID(SUB_NODE(arg_list, i));
		Memory_Address *addr = create_mem_addr(1, -3 - i, GET_AST_DATATYPE(SUB_NODE(arg_list, i)));
		create_local_variable(id, addr, func_node->depth + 1);
	}
	add_link(instructions, BR_OP);
	add_link(instructions, 0);
	pda_stack[pda_sp++] = create_func_pda(instructions, instructions->tail);
	char *id = GET_AST_STR_DATA(SUB_NODE(func_node, 1));
	Function *func = create_function(instructions->length, SUB_NODE(func_node, 2), GET_AST_DATATYPE(func_node));
	add_function(id, func);
	func_depth = func_node->depth + 1;
}

void compile_return(Linked_List *instructions, ASTNode *return_node) {
	if (GET_AST_DATATYPE(return_node) != 0) {
		compile_rhs(instructions, SUB_NODE(return_node, 1), return_node->depth);
	}
	add_link(instructions, RET_OP);
}

void compile_func_call(Linked_List *instructions, ASTNode *func_call) {
	Function *func = get_function(GET_AST_STR_DATA(SUB_NODE(func_call,1)));
	ASTNode *var_list = SUB_NODE(func_call, 2);
	int num_args = var_list->num_sub;
	for (int i = num_args - 1; i >= 0 ; i--) {
		compile_rhs(instructions, SUB_NODE(var_list, i), func_call->depth);
	}
	add_link(instructions, CALL_OP);
	add_link(instructions, func->addr);
	add_link(instructions, num_args);
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
	case FUNC_CALL_NODE:
		compile_func_call(instructions, rhs);
		break;
	default:
		break;
	}
}

void compile_operator(Linked_List *instructions, ASTNode *op_node) {
	int type = GET_OP_TYPE(op_node);
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
	if (type == MODULO) op = MODI_OP;
	if (type == BITAND) op = BAND_OP;
	if (type == BITXOR) op = BXOR_OP;
	if (type == BITOR) op = BOR_OP;
	if (type == LSHIFT) op = LSHIFT_OP;
	if (type == RSHIFT) op = RSHIFT_OP;
	add_link(instructions, op);
}

void compile_const(Linked_List *instructions, ASTNode *const_node) {
	add_link(instructions, PUSH_OP);
	add_link(instructions, GET_CONST_INT(const_node));
}

void compile_var(Linked_List *instructions, ASTNode *var_node, int depth) {
	char *id = GET_AST_STR_DATA(SUB_NODE(var_node, 1));
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

void compile_print(Linked_List *instructions, ASTNode *print_node) {
	compile_rhs(instructions, SUB_NODE(print_node, 0), print_node->depth);
	add_link(instructions, PRINTI_OP);
}
