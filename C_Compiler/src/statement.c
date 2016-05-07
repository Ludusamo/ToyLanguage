#include <statement.h>

Statement *create_statement(const char *str) {
	Statement *statement = malloc(sizeof(Statement));
	statement->tokens = malloc(sizeof(Token) * MAX_TOKENS);
	statement->statement_str = str_copy(str);
	statement->num_tokens = 0;

	return statement;
}

void add_token(Statement *statement, const char *str) {
	printf("Add Token: %s\n", str);
	Token *t = create_token(str);
	identify_token_type(t);
	statement->tokens[statement->num_tokens++] = *t;
}

void tokenize_statement(Statement *statement) {
	const char *s = statement->statement_str;
	int bi = 0;
	int reading_whitespace = 0;
	char *buffer = malloc(sizeof(char) * strlen(s) + 1);
	for (int i = 0; i < strlen(s) + 1; i++) {
		if (reading_whitespace) {
			if (!is_whitespace(s[i])) {
				buffer[bi++] = '\0';
				bi = 0;
				add_token(statement, buffer);
				reading_whitespace = 0;
			}
		} else {
			if (is_whitespace(s[i])) {
				buffer[bi++] = '\0';
				bi = 0;
				add_token(statement, buffer);
				reading_whitespace = 1;
			}
		}
		buffer[bi++] = s[i];
	}
}

int is_whitespace(char c) {
	return c <= 32;
}
