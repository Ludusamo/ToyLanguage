#ifndef STATEMENT_H
#define STATEMENT_H

#include <token.h>
#include <ctype.h>

#define MAX_TOKENS 50

typedef enum {
	DECL
} Statement_Type;

typedef struct {
	const char *statement_str;
	int num_tokens;
	Token *tokens;
	int depth;
	Statement_Type type;
} Statement;

Statement *create_statement(const char *str);

void add_token(Statement *statement, const char *str);
void tokenize_statement(Statement *statement);
int is_whitespace(char c);

#endif // STATEMENT_H