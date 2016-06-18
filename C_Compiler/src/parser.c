#include <parser.h>

ASTNode *parse(Statement *statements) {
	ASTNode *program = create_program_ast(num_lines);
	for (int i = 0; i < num_lines; i++) {
		ASTNode *node = parse_line(&statements[i]);
		if (node) {
			// TODO: Successful Code
			program->sub_nodes[i] = node;
		} else {
			// TODO: Failure Code
		}
	}
	return program;
}

ASTNode *parse_line(Statement *statement) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node = parse_declaration(statement);
	if (node) {
		statement->type = DECL;
		return node;
	}
	return 0;
}

ASTNode *parse_declaration(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], DATATYPE) && is_type(tokens[1], IDENTIFIER)) {
		return create_decl_ast(&GET_DATATYPE(statement), GET_DECL_ID(statement), 0);
	}
	return 0;
}

ASTNode *parse_rhs(Statement *statement, int rhs_index) {
	ASTNode *node;
	Token *tokens = statement->tokens;
	printf("Current Token: %s\n", tokens[rhs_index].token_str);
	if (is_const(tokens[rhs_index])) {
		ASTNode *lhs = create_const_ast(create_data_packet(tokens[rhs_index]));
		ASTNode *op = parse_rhs(statement, rhs_index + 1);
		if (op) {
			op->sub_nodes[0] = lhs;
			return op;
		}
		return lhs;
	} else if (is_type(tokens[rhs_index], ARITHOP)) {
		ASTNode *op = create_arithop_ast(&tokens[rhs_index].subtype);
		op->sub_nodes[1] = parse_rhs(statement, rhs_index + 1);
		if (op->sub_nodes[1]) return op;
	}
	return 0;
}

int is_const(Token token) {
	return is_type(token, NUM) || is_type(token, BOOLVAL);
}
