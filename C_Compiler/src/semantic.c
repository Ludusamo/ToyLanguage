#include "semantic.h"

int semantic_analysis(ASTNode *prog) {
	if (NODE_TYPE(prog) != PROG_NODE) return 0;
	int status = 1;
	lineno = 0;
	prev_depth = 0;
	for (int i = 0; i < num_lines; i++) {
		lineno = i + 1;
		ASTNode *node = SUB_NODE(prog, i);
		if (node->depth < prev_depth) {
			exit_depth(prev_depth);
		}
		switch (NODE_TYPE(node)) {
		case DECL_NODE:
			status = status && analyze_decl(node, node->depth);
			break;
		case ASSIGN_NODE:
			status = status && analyze_assignment(node, node->depth);
			break;
		case IF_NODE:
			status = status && analyze_if(node, node->depth);
			break;
		case FUNC_NODE:
			status = status && analyze_func_decl(node);
			break;
		}
		prev_depth = node->depth;
	}
	return status;
}

int analyze_decl(ASTNode *decl, int depth) {
	char *id = GET_AST_DECL_ID(decl);
	if (depth == 0) {
		if (get_global_addr(id)) {
			throw_error(VARIABLE_EXISTS, "Unknown", lineno, NULL);
		} else {
			Memory_Address *addr = create_mem_addr(1, NUM_GLOBAL, GET_AST_DATATYPE(decl));
			int status = create_global_variable(id, addr);
			ASTNode *rhs = SUB_NODE(decl, 2);
			status = status && analyze_rhs(rhs, GET_AST_DATATYPE(decl));
			if (status) return 1;
		}	
	} else if (depth == -1) { // FUNCTION ARGS}
		if (get_local_addr(id, 1)) { // TODO
			throw_error(VARIABLE_EXISTS, "Unknown", lineno, NULL);
		} else {
			Memory_Address *addr = create_mem_addr(1, -3 - NUM_LOCAL, GET_AST_DATATYPE(decl));
			int status = create_local_variable(id, addr, 1);
			if (status) return 1;
		}
	} else {
		if (get_local_addr(id, depth)) {
			throw_error(VARIABLE_EXISTS, "Unknown", lineno, NULL);
		} else {
			Memory_Address *addr = create_mem_addr(1, NUM_LOCAL + 1, GET_AST_DATATYPE(decl));
			int status = create_local_variable(id, addr, depth);
			ASTNode *rhs = SUB_NODE(decl, 2);
			status = status && analyze_rhs(rhs, GET_AST_DATATYPE(decl));
			if (status) return 1;
		}
	}
	return 0;
}

int analyze_assignment(ASTNode *assign, int depth) {
	char *id = GET_AST_STR_DATA(SUB_NODE(assign, 0));
	if (depth == 0) {
		if (!get_global_addr(id)) {
			throw_error(UNKNOWN_REFERENCE, "Unknown", lineno, NULL);
		} else {
			ASTNode *rhs = SUB_NODE(assign, 1);
			int status = 0;
			if (rhs) status = analyze_rhs(SUB_NODE(assign, 1), get_global_addr(id)->type);
			if (status) return 1;
		}
	} else {
		if (!get_local_addr(id, depth) && !get_global_addr(id)) {
			throw_error(UNKNOWN_REFERENCE, "Unknown", lineno, NULL);
		} else {
			ASTNode *rhs = SUB_NODE(assign, 1);
			int status = 0;
			Memory_Address *addr = get_local_addr(id, depth);
			if (!addr) addr = get_global_addr(id);
			if (rhs) status = analyze_rhs(SUB_NODE(assign, 1), addr->type);
			if (status) return 1;
		}
	}
	return 0;
}

int analyze_if(ASTNode *if_node, int depth) {
	return analyze_rhs(SUB_NODE(if_node, 0), 2); // 2 is BOOL
}

int analyze_func_decl(ASTNode *func_decl) {
	char *id = GET_AST_STR_DATA(SUB_NODE(func_decl, 1));
	int status = 1;
	if (get_function_addr(id)) {
		throw_error(FUNCTION_EXISTS, "Unknown", lineno, NULL);
	} else {
		ASTNode *arg_list = SUB_NODE(func_decl, 2);
		for (int i = 0; i < arg_list->num_sub; i++) {
			ASTNode *arg = SUB_NODE(arg_list, i);
			status = status && analyze_decl(arg, -1);
		}
		Memory_Address *addr = create_mem_addr(1, -1, 1);
		status = status && create_function(id, addr);
	}
	return status;
}

int analyze_rhs(ASTNode *rhs, int datatype) {
	int sp = 0;
	ASTNode **stack = malloc(sizeof(rhs) * 255);
	stack[sp++] = rhs;
	
	ASTNode *cur_node;
	while (sp > 0) {
		cur_node = stack[--sp];
		switch (NODE_TYPE(cur_node)) {
		case CONST_NODE:
			sp--;
			break;
		case OPERATOR_NODE:
			stack[sp++] = SUB_NODE(cur_node, 1);
			stack[sp++] = SUB_NODE(cur_node, 0);
			break;
		case VAR_NODE: {
			Memory_Address *var = get_global_addr(GET_AST_STR_DATA(SUB_NODE(cur_node, 0)));
			if (!var) {
				printf("Variable \"%s\" has not been declared.\n", GET_AST_STR_DATA(SUB_NODE(cur_node, 0)));
				return 0;
			}
			if (var->type == datatype) sp--;
			else return 0;
			break;
		}
		}
	}
	return 1;	
}
