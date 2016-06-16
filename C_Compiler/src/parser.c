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
	if (is_declaration(statement)) {
		statement->type = DECL;
		return create_decl_ast(&GET_DATATYPE(statement), GET_DECL_ID(statement), 0);
	}
	return 0;
}

int is_declaration(Statement *statement) {
	Token *tokens = statement->tokens;
	return (is_type(tokens[0], DATATYPE) && is_type(tokens[1], IDENTIFIER));
}
