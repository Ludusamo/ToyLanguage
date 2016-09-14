#include "semantic.h"

int semantic_analysis(ASTNode *prog) {
	if (NODE_TYPE(prog) != PROG_NODE) return 0;
	int status = 1;
	lineno = 0;
	prev_depth = 0;
	for (int i = 0; i < num_lines + 1; i++) {
		lineno = i + 1;
		ASTNode *node = SUB_NODE(prog, i);

		if (NODE_TYPE(node) == BLANK_NODE) {
			continue; // Skip blank nodes
		}
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
		case WHILE_NODE:
			status = status && analyze_while(node, node->depth);
			break;
		case FUNC_NODE:
			status = status && analyze_func_decl(node);
			break;
		case RETURN_NODE:
			status = status && analyze_return(node);
			break;
		case FUNC_CALL_NODE:
			status = status && analyze_func_call(node);
			break;
		case PRINT_NODE:
			status = status && analyze_print(node, node->depth);
			break;
		default:
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
			if (rhs) {
				analyze_rhs(rhs, depth);
				status = status && check_datatype(rhs, GET_AST_DATATYPE(decl));
			}
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
			if (rhs) {
					analyze_rhs(rhs, depth);
					status = status && check_datatype(rhs, GET_AST_DATATYPE(decl));
			}
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
			if (rhs) {
				analyze_rhs(SUB_NODE(assign, 1), depth);
				status = check_datatype(rhs, get_global_addr(id)->type);
			}
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
			if (rhs) {
				analyze_rhs(rhs, depth);
				status = check_datatype(rhs, addr->type);
			}
			if (status) return 1;
		}
	}
	return 0;
}

int analyze_if(ASTNode *if_node, int depth) {
	analyze_rhs(SUB_NODE(if_node, 0), depth);
	return check_datatype(SUB_NODE(if_node, 0), BOOL);
}

int analyze_while(ASTNode *while_node, int depth) {
	analyze_rhs(SUB_NODE(while_node, 0), depth);
	return check_datatype(SUB_NODE(while_node, 0), BOOL);
}

int analyze_func_decl(ASTNode *func_decl) {
	char *id = GET_AST_STR_DATA(SUB_NODE(func_decl, 1));
	int status = 1;
	if (get_function(id)) {
		throw_error(FUNCTION_EXISTS, "Unknown", lineno, NULL);
	} else {
		ASTNode *arg_list = SUB_NODE(func_decl, 2);
		for (int i = 0; i < arg_list->num_sub; i++) {
			ASTNode *arg = SUB_NODE(arg_list, i);
			status = status && analyze_decl(arg, -1);
		}
		Function *func = create_function(-1, arg_list, GET_AST_DATATYPE(func_decl));
		status = status && add_function(id, func);
	}
	return status;
}

int analyze_return(ASTNode *return_node) {
	if (SUB_NODE(return_node, 1)) {
		analyze_rhs(SUB_NODE(return_node, 1), return_node->depth);
		if (check_datatype(SUB_NODE(return_node, 1), GET_AST_DATATYPE(return_node))) {
			return 1;
		}
	} else if (GET_AST_DATATYPE(return_node) == 0) {
		return 1;
	}
	return 0;
}

int analyze_func_call(ASTNode *func_call) {
	char *id = GET_AST_STR_DATA(SUB_NODE(func_call, 1));
	Function *func = get_function(id);
	if (!func) {
		throw_error(UNKNOWN_REFERENCE, "Unknown", lineno, "");
	}
	int *return_type = malloc(sizeof(int));
	*return_type = func->return_type;
	SUB_NODE(func_call, 0) = create_datatype_ast(return_type);
	
	ASTNode *rhs_list = SUB_NODE(func_call, 2);
	ASTNode *arg_list = func->arg_list;	
	int num_args = arg_list->num_sub;
	if (rhs_list->num_sub != arg_list->num_sub) {
		throw_error(INSUFFICIENT_ARGS, "Unknown", lineno, "");
	}
	for (int i = 0; i < num_args; i++) {
		analyze_rhs(SUB_NODE(rhs_list, i), func_call->depth);
		if (!check_datatype(SUB_NODE(rhs_list, i), GET_AST_DATATYPE(SUB_NODE(arg_list, i)))) {
			return 0;
		}
	}
	return 1;
}

int analyze_rhs(ASTNode *rhs, int depth) {
	if (NODE_TYPE(rhs) == OPERATOR_NODE) {
		analyze_rhs(SUB_NODE(rhs, 1), depth);
		analyze_rhs(SUB_NODE(rhs, 2), depth);

		int *resulting_datatype = malloc(sizeof(int));
		*resulting_datatype = determine_resulting_datatype(rhs);
		if (*resulting_datatype == -1) {
			throw_error(INVALID_OPERANDS, "Unknown", lineno, "");
		} else {
			SUB_NODE(rhs, 0) = create_datatype_ast(resulting_datatype);
		}
	} else if (NODE_TYPE(rhs) == VAR_NODE) {
		Memory_Address *var = 0;
		char *id = GET_AST_STR_DATA(SUB_NODE(rhs, 1));
		int search_depth = depth;
		while (!var && search_depth > 0) {
			var = get_local_addr(id, search_depth--);
		}
		if (!var) var = get_global_addr(id);
		if (!var) {
			throw_error(UNKNOWN_REFERENCE, "Unknown", lineno, "");
		}

		int *var_type = malloc(sizeof(int));
		*var_type = var->type;
		SUB_NODE(rhs, 0) = create_datatype_ast(var_type);
	} else if (NODE_TYPE(rhs) == FUNC_CALL_NODE) {
		analyze_func_call(rhs);
	}
	return 1;	
}

// TODO: REMOVE
int analyze_print(ASTNode *print_node, int depth) {
	analyze_rhs(SUB_NODE(print_node, 0), depth);
	return check_datatype(SUB_NODE(print_node, 0), INT);
}

int determine_resulting_datatype(ASTNode *op_node) {
	int op = GET_OP_TYPE(op_node);
	int l_datatype = GET_AST_DATATYPE(SUB_NODE(op_node, 1));
	int r_datatype = GET_AST_DATATYPE(SUB_NODE(op_node, 2));

	int return_op = -1;

	if (l_datatype <= 5 && r_datatype <= 5) {
		if (op == AND || op == OR || op == EQ || op == NEQ 
			|| op == LTE || op == GTE || op == LT || op == GT) {
			return_op = BOOL;
		} else {
			return_op =  INT;
		}
	}
	return return_op;
}

int check_datatype(ASTNode *node, int datatype) {
	int node_datatype = GET_AST_DATATYPE(node);
	if (node_datatype == 0) return 1;
	if (node_datatype == datatype) {
		return 1;
	} else {
		const char *additional = "";
		throw_error(TYPE_MISMATCH, "Unknown", lineno, additional);
	}
	return 0;
}
