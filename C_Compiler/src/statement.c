#include <statement.h>

Statement *create_statement(const char *str) {
	Statement *statement = malloc(sizeof(Statement));
	statement->tokens = malloc(sizeof(Token) * MAX_TOKENS);
	statement->statement_str = str;
	statement->num_tokens = 0;

	return statement;
}

void tokenize_statement(Statement *statement) {
	const char *s = statement->statement_str;
	int bi = 0;
	char *buffer = malloc(sizeof(char) * strlen(s));
	for (int i = 0; i < strlen(s); i++) {
		buffer[bi++] = s[i];
		if (is_whitespace(s[i])) {
			
		}
	}
}

int is_whitespace(char c) {
	return c <= 32;
}
