#include <parser.h>

ASTNode *parse(Statement *statements) {
	ASTNode *program = create_program_ast(num_lines);
	in_function = 0;;
	for (int i = 0; i < num_lines; i++) {
		lineno = i + 1;
		ASTNode *node = parse_line(&statements[i]);
		if (node) {
			// TODO: Successful Code
			SUB_NODE(program, i) = node;
		} else {
			// TODO: Failure Code
			printf("Line %i is not a statement.\n", i + 1);
		}
	}
	return program;
}

ASTNode *parse_line(Statement *statement) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node = parse_declaration(statement);
	if (statement->depth < function_depth + 1) in_function = 0;
	if (node = parse_declaration(statement)) {
		return node;
	} else if (node = parse_assignment(statement)) {
		return node;
	} else if (node = parse_if(statement)) {
		return node;
	} else if (node = parse_function(statement)) {
		in_function = 1;
		function_depth = statement->depth;
		function_return_type = &statement->tokens[0].subtype;
		return node;
	} else if (node = parse_return(statement)) {
		return node;
	}
	return 0;
}

ASTNode *parse_declaration(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], DATATYPE) && is_type(tokens[1], IDENTIFIER)) {
		ASTNode *rhs = 0;
		int zero = 0;
		if (is_type(tokens[2], ASSIGNMENT)) {
			rhs = parse_rhs(statement, 3);
		}
		else if (is_type(tokens[2], EOS)) rhs = create_const_ast((void*) &zero);
		else return 0;
		return create_decl_ast(&GET_DATATYPE(statement), GET_DECL_ID(statement), rhs, statement->depth);
	}
	return 0;
}

ASTNode *parse_assignment(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], IDENTIFIER) && is_type(tokens[1], ASSIGNMENT)) {
		ASTNode *rhs = parse_rhs(statement, 2);
		if (rhs)
			return create_assignment_ast(tokens[0].token_str, rhs, statement->depth);	
	}
	return 0;
}

ASTNode *parse_if(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], CONTROL) && is_subtype(tokens[0], IF)) {
		ASTNode *rhs = parse_rhs(statement, 1);
		if (rhs)
			return create_if_ast(rhs, statement->depth);
	}
	return 0;
}

ASTNode *parse_function(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], DATATYPE) && is_type(tokens[1], IDENTIFIER)) {
		if (is_type(tokens[2], PAREN) && is_subtype(tokens[2], LPAREN)) {
			ASTNode *arg_list = parse_parameter_list(statement, 3);
			if (arg_list) {
				return create_func_ast(&GET_DATATYPE(statement), GET_DECL_ID(statement), arg_list, statement->depth);
			}
		}
	}
	return 0;
}

ASTNode *parse_return(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], RETURN)) {
		if (!in_function) throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, str_add("Unexpected token ", tokens[0].token_str));
		ASTNode *rhs = parse_rhs(statement, 1);
		return create_return_ast(function_return_type, rhs, statement->depth);
	}
	return 0;
}

ASTNode *parse_parameter_list(Statement *statement, int rhs_index) {
	statement_index = rhs_index;
	Token *tokens = statement->tokens;
	int num_param = 0;
	ASTNode *var_stack[255];
	int expecting_param = 1;
	for (int i = statement_index; i < statement->num_tokens; i++) {
		if (is_type(tokens[i], DATATYPE) && is_type(tokens[i + 1], IDENTIFIER)) {
			if (expecting_param) {
				expecting_param = 0;
				var_stack[num_param++] = create_decl_ast(&tokens[i].subtype, tokens[i + 1].token_str, 0, statement->depth + 1);
				i++;
			} else {
				throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, str_add("Unexpected token ", tokens[i].token_str));
			}
		} else if (is_type(tokens[i], COMMA)) {
			if (!expecting_param) {
				expecting_param = 1;	
			} else {
				throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, str_add("Unexpected token ", tokens[i].token_str));
			}
		} else if (is_type(tokens[i], PAREN) && is_subtype(tokens[i], RPAREN)) {
			if (is_type(tokens[i + 1], EOS)) {
				ASTNode *arg_list = create_varlist_ast(num_param);
				for (int i = 0; i < num_param; i++) {
					SUB_NODE(arg_list, i) = var_stack[i];
				}
				return arg_list;
			} else {
				throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, str_add("Unexpected token ", tokens[i].token_str));
			}
		} else {
			throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, str_add("Unexpected token ", tokens[i].token_str));
		}
	}
	return 0;
}

ASTNode *parse_rhs(Statement *statement, int rhs_index) {
	statement_index = rhs_index;
	Token *tokens = statement->tokens;
	if (is_const(tokens[rhs_index])) {
		if (is_const(tokens[rhs_index + 1])) {
			throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, str_add("Unexpected token ", tokens[statement_index + 1].token_str));	
		}

		ASTNode *lhs = create_const_ast(create_data_packet(tokens[rhs_index]));
		if (!is_type(tokens[rhs_index + 1], EOS)) {
			ASTNode *op = parse_rhs(statement, rhs_index + 1);
			if (op) {
				return append_to_leftmost(lhs, op);
			}
		}	
		return lhs;
	} else if (is_type(tokens[rhs_index], OPERATOR)) {
		if (is_type(tokens[rhs_index + 1], OPERATOR) || is_type(tokens[rhs_index + 1], EOS)) {
			throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, str_add("Unexpected token ", tokens[statement_index + 1].token_str));	
		}

		ASTNode *op = create_operator_ast(&tokens[rhs_index].subtype);
		SUB_NODE(op, 1) = parse_rhs(statement, rhs_index + 1);
		if (SUB_NODE(op, 1)) {
			if (!is_type(tokens[rhs_index + 1], PAREN) && (NODE_TYPE(SUB_NODE(op, 1)) == OPERATOR_NODE && GET_OP_TYPE(SUB_NODE(op, 1)) < GET_OP_TYPE(op))) {
				ASTNode *rhs = shift_op(op);
				return rhs;
			}
			return op;
		}
	} else if (is_type(tokens[rhs_index], PAREN)) {
		if (is_subtype(tokens[rhs_index], LPAREN)) {

			ASTNode *lhs = parse_rhs(statement, rhs_index + 1);	

			if (is_type(tokens[statement_index], PAREN) &&
				is_subtype(tokens[statement_index], RPAREN)) {
				ASTNode *op = parse_rhs(statement, statement_index + 1);

				if (op) {
					SUB_NODE(op, 0) = lhs;
					return op;
				}
				return lhs;
			} else {
				throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, str_add("Unexpected token ", tokens[statement_index].token_str));	
			}
		}
	} else if (is_type(tokens[rhs_index], IDENTIFIER)) {
		ASTNode *lhs = create_var_ast(tokens[rhs_index].token_str);
		ASTNode *op = parse_rhs(statement, rhs_index + 1);
		if (op) {
			return append_to_leftmost(lhs, op);
		}
		return lhs;
	}
		
	return 0;
}

ASTNode *shift_op(ASTNode *rhs) {
	ASTNode *p = rhs;
	ASTNode *r = SUB_NODE(rhs, 1);
	SUB_NODE(p, 1) = SUB_NODE(r, 0);
	SUB_NODE(r, 0) = p;
	return r;
}

int is_const(Token token) {
	return is_type(token, NUM) || is_type(token, BOOLVAL);
}

ASTNode *append_to_leftmost(ASTNode *lhs, ASTNode *rhs) {
	ASTNode *leftmost = rhs;
	while (SUB_NODE(leftmost, 0)) leftmost = SUB_NODE(leftmost, 0);
	SUB_NODE(leftmost, 0) = lhs;
	return rhs;
}
