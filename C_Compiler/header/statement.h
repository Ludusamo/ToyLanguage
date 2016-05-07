#ifndef STATEMENT_H
#define STATEMENT_H

#include <token.h>

#define MAX_TOKENS 50

typedef struct {
	const char *statement_str;
	int num_tokens;
	Token *tokens;
} Statement;

Statement *create_statement(const char *str);

void tokenize_statement(Statement *statement);
int is_whitespace(char c);

#endif // STATEMENT_H
