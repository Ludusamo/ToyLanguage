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
	printf("%s", statement->statement_str);
	node = parse_declaration(statement);
	if (node) {
		printf("Identified as a declaration.\n");
		statement->type = DECL;
		return node;
	}
	return 0;
}

ASTNode *parse_declaration(Statement *statement) {
	Token *tokens = statement->tokens;
	if (is_type(tokens[0], DATATYPE) && is_type(tokens[1], IDENTIFIER)) {
		ASTNode *rhs = 0;
		if (is_type(tokens[2], ASSIGNMENT)) rhs = parse_rhs(statement, 3);
		return create_decl_ast(&GET_DATATYPE(statement), GET_DECL_ID(statement), rhs);
	}
	return 0;
}

ASTNode *parse_rhs(Statement *statement, int rhs_index) {
	statement_index = rhs_index;
	Token *tokens = statement->tokens;
	if (is_const(tokens[rhs_index])) {
		ASTNode *lhs = create_const_ast(create_data_packet(tokens[rhs_index]));
		ASTNode *op = parse_rhs(statement, rhs_index + 1);
		if (op) {
			if (!op->sub_nodes[0]) op->sub_nodes[0] = lhs;
			else {
				ASTNode *leftmost = op;
				while (leftmost->sub_nodes[0]) leftmost = leftmost->sub_nodes[0];
				leftmost->sub_nodes[0] = lhs;
			}
			return op;
		}
		return lhs;
	} else if (is_type(tokens[rhs_index], ARITHOP)) {
		ASTNode *op = create_arithop_ast(&tokens[rhs_index].subtype);
		op->sub_nodes[1] = parse_rhs(statement, rhs_index + 1);
		if (op->sub_nodes[1]) {
			if (!is_type(tokens[rhs_index + 1], PAREN) && op->sub_nodes[1]->type == ARITHOP_NODE && *(int*)op->sub_nodes[1]->data < *(int*)op->data) {
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
					op->sub_nodes[0] = lhs;
					return op;
				}
				return lhs;
			}
		}
	}
	return 0;
}

ASTNode *shift_op(ASTNode *rhs) {
	ASTNode *p = rhs;
	ASTNode *r = rhs->sub_nodes[1];
	p->sub_nodes[1] = r->sub_nodes[0];
	r->sub_nodes[0] = p;
	return r;
}

int is_const(Token token) {
	return is_type(token, NUM) || is_type(token, BOOLVAL);
}
