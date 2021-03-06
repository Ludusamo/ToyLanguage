#include <parser.h>

ASTNode *parse(Statement *statements) {
	ASTNode *program = create_program_ast(num_lines + 1);
	in_function = 0;
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
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = END_OF_FILE_NODE;
	node->depth = 0;
	SUB_NODE(program, num_lines) = node;
	return program;
}

ASTNode *parse_line(Statement *statement) {
	ASTNode *node = malloc(sizeof(ASTNode));
	if ((node = parse_declaration(statement))) {
	} else if ((node = parse_assignment(statement))) {
	} else if ((node = parse_if(statement))) {
	} else if ((node = parse_while(statement))) {
	} else if ((node = parse_function(statement))) {
		in_function = 1;
		function_depth = statement->depth;
		function_return_type = &statement->tokens[0].subtype;
	} else if ((node = parse_return(statement))) {
	} else if ((node = parse_func_call(statement, 0))) {
	} else if (is_type(statement->tokens[1], EOS)) {
		node = malloc(sizeof(ASTNode));
		node->type = BLANK_NODE;
		return node;
	} else if ((node = parse_print(statement))) { // TODO: REMOVE
	}
	if (statement->depth < function_depth) {
		in_function = 0;
	}
	return node;
}

ASTNode *parse_declaration(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], DATATYPE) && is_type(tokens[1], IDENTIFIER)) {
		ASTNode *rhs = 0;
		int *zero = malloc(sizeof(int));
		*zero = 0;
		if (is_type(tokens[2], ASSIGNMENT)) {
			rhs = parse_rhs(statement, 3);
		}
		else if (is_type(tokens[2], EOS)) rhs = create_const_ast(zero, zero);
		else return 0;
		return create_decl_ast(&GET_DATATYPE(statement), GET_DECL_ID(statement), rhs, statement->depth);
	}
	return 0;
}

ASTNode *parse_assignment(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], IDENTIFIER) && is_type(tokens[1], ASSIGNMENT)) {
		ASTNode *rhs = parse_rhs(statement, 2);
		if (rhs) {
			return create_assignment_ast(tokens[0].token_str, rhs, statement->depth);	
		}
	}
	return 0;
}

ASTNode *parse_if(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], CONTROL) && is_subtype(tokens[0], IF)) {
		ASTNode *rhs = parse_rhs(statement, 1); if (rhs) {
			return create_if_ast(rhs, statement->depth);
		}
	}
	return 0;
}

ASTNode *parse_while(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], CONTROL) && is_subtype(tokens[0], WHILE)) {
		ASTNode *rhs = parse_rhs(statement, 1);
		if (rhs) {
			return create_while_ast(rhs, statement->depth);
		}
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

ASTNode *parse_func_call(Statement *statement, int index) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[index], IDENTIFIER)) {
		if (is_type(tokens[index + 1], PAREN) && is_subtype(tokens[index + 1], LPAREN)) {
			int num_param = 0;
			ASTNode *var_stack[255];
			var_stack[num_param++] = parse_rhs(statement, index + 2);
			if (!var_stack[num_param - 1]) {
				if (is_type(tokens[index + 2], PAREN) && is_subtype(tokens[index + 2], RPAREN)) {
					ASTNode *arg_list = create_varlist_ast(0);
					return create_func_call_ast(NULL, tokens[0].token_str, arg_list, statement->depth);
				} else {
					printf("Incorrect rhs\n");
					// TODO: throw_error();
				}
			} else {
				int paren_count = 1; for (int i = statement_index; paren_count > 0; i++) {
					if (is_type(tokens[i], PAREN)) {
						if (is_subtype(tokens[i], LPAREN)) {
							paren_count++;
						} else {
							paren_count--;
							if (paren_count == 0) {
								ASTNode *arg_list = create_varlist_ast(num_param);
								for (int i = 0; i < num_param; i++) {
									SUB_NODE(arg_list, i) = var_stack[i];
								}
								return create_func_call_ast(NULL, tokens[index].token_str, arg_list, statement->depth);	
							}
						}
					} else if (is_type(tokens[i], COMMA)) {
						var_stack[num_param++] = parse_rhs(statement, i + 1);
						i = statement_index - 1;
						if (!var_stack[num_param - 1]) {
							// TODO: throw_error();
						}
					}
				}
			}
		}
	}
	return 0;
}

ASTNode *parse_print(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], PRINT)) {
		ASTNode *rhs = parse_rhs(statement, 1);
		return create_print_ast(rhs, statement->depth);
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

		int *const_type = determine_const_type(tokens[rhs_index].type);

		ASTNode *lhs = create_const_ast(const_type, create_data_packet(tokens[rhs_index]));
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
		SUB_NODE(op, 2) = parse_rhs(statement, rhs_index + 1);
		if (SUB_NODE(op, 2)) {
			if (!is_type(tokens[rhs_index + 1], PAREN) && (NODE_TYPE(SUB_NODE(op, 2)) == OPERATOR_NODE && GET_OP_TYPE(SUB_NODE(op, 2)) < GET_OP_TYPE(op))) {
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
					SUB_NODE(op, 1) = lhs;
					return op;
				}
				return lhs;
			} else {
				throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, str_add("Unexpected token ", tokens[statement_index].token_str));	
			}
		}
	} else if (is_type(tokens[rhs_index], IDENTIFIER)) {
		ASTNode *lhs = 0;
		if (is_type(tokens[rhs_index + 1], PAREN) && is_subtype(tokens[rhs_index + 1], LPAREN)) {
			int i = rhs_index + 2;
			int paren_count = 1;
			for (i = rhs_index + 2; paren_count > 0; i++) {
				if (is_type(tokens[i], EOS)) {
					throw_error(UNEXPECTED_TOKEN, "Unknown", lineno, "");
				} else if (is_type(tokens[i], PAREN)) {
					if (is_subtype(tokens[i], LPAREN)) {
						paren_count++;	
					} else {
						paren_count--;	
					}	
				}
				
			}
			lhs = parse_func_call(statement, rhs_index);
			rhs_index = i - 1;
		} else {
			lhs = create_var_ast(tokens[rhs_index].token_str);
		}
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
	ASTNode *r = SUB_NODE(rhs, 2);
	SUB_NODE(p, 2) = SUB_NODE(r, 1);
	SUB_NODE(r, 1) = p;
	return r;
}

int is_const(Token token) {
	return is_type(token, NUM) || is_type(token, BOOLVAL) || is_type(token, CHAR_LITERAL);
}

int *determine_const_type(int type) {
	int *const_type = malloc(sizeof(int));
	if (type == NUM) *const_type = INT;
	if (type == BOOLVAL) *const_type = BOOL;
	if (type == CHAR_LITERAL) *const_type = CHAR;
	return const_type;
}

ASTNode *append_to_leftmost(ASTNode *lhs, ASTNode *rhs) {
	ASTNode *leftmost = rhs;
	while (SUB_NODE(leftmost, 1)) leftmost = SUB_NODE(leftmost, 1);
	SUB_NODE(leftmost, 1) = lhs;
	return rhs;
}
