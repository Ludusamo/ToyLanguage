#ifndef STATEMENT_H
#define STATEMENT_H

#include <token.h>
#include <ctype.h>

#define MAX_TOKENS 50

#define GET_DATATYPE(statement) statement->tokens[0].subtype
#define GET_DECL_ID(statement) statement->tokens[1].token_str

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
