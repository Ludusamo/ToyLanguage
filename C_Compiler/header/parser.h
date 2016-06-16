#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "statement.h"
#include "ast.h"
#include "shared_values.h"

ASTNode *parse(Statement *statements);
ASTNode *parse_line(Statement *statement);
int is_declaration(Statement *statement);

#endif // PARSER_H
