#include <statement.h>

Statement *create_statement(const char *str) {
	Statement *statement = malloc(sizeof(Statement));
	statement->tokens = malloc(sizeof(Token) * MAX_TOKENS);

	statement->depth = 0;
	int i = 0;
	while (is_whitespace(str[i])) {
		statement->depth++;
		i++;
	}
	char *buffer = malloc(sizeof(char) * strlen(str) - i + 1);	
	int si = 0;
	while (i < strlen(str)) buffer[si++] = str[i++];
	buffer[si++] = '\0';
	statement->statement_str = str_copy(buffer);

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
	int mode = 1;
	char *buffer = malloc(sizeof(char) * strlen(s) + 1);
	for (int i = 0; i < strlen(s) + 1; i++) {
		if (mode == 0) { // Reading whitespace
			if (!is_whitespace(s[i])) {
				buffer[bi++] = '\0';
				bi = 0;
				add_token(statement, buffer);
				mode = isalnum(s[i]) ? 1 : 2;
			}
		} else if (mode == 1) { // Reading alnum
			if (!isalnum(s[i])) {
				buffer[bi++] = '\0';
				bi = 0;
				add_token(statement, buffer);
				mode = is_whitespace(s[i]) ? 0 : 2;
			}
		} else if (mode == 2) { // Other
			if (isalnum(s[i]) || is_whitespace(s[i])) {
				buffer[bi++] = '\0';
				bi = 0;
				add_token(statement, buffer);
				mode = is_whitespace(s[i]) ? 0 : 1;
			}
		}
		buffer[bi++] = s[i];
	}
}

int is_whitespace(char c) {
	return c <= 32;
}
