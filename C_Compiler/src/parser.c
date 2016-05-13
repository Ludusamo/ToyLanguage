#include <parser.h>

int parse(Statement *statements) {
	for (int i = 0; i < num_lines; i++) {
		int successful = parse_line(&statements[i]);
		if (successful) {
			// TODO: Successful Code
		} else {
			// TODO: Failure Code
		}
	}
}

int parse_line(Statement *statement) {
	if (is_declaration(statement)) {
		statement->type = DECL;
		return 1;
	}
	return 0;
}

int is_declaration(Statement *statement) {
	Token *tokens = statement->tokens;
	return (is_type(tokens[0], DATATYPE) && is_type(tokens[1], IDENTIFIER));
}
