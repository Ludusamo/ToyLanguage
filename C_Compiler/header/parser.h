#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "statement.h"
#include "ast.h"
#include "shared_values.h"

int statement_index;

ASTNode *parse(Statement *statements);
ASTNode *parse_line(Statement *statement);
ASTNode *parse_declaration(Statement *statement);
ASTNode *parse_rhs(Statement *statement, int rhs_index);
int is_const(Token token);

#endif // PARSER_H
