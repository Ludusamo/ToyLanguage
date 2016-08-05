#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "statement.h"
#include "ast.h"
#include "memory.h"
#include "shared_values.h"

int statement_index;

ASTNode *parse(Statement *statements);
ASTNode *parse_line(Statement *statement);
ASTNode *parse_declaration(Statement *statement);
ASTNode *parse_assignment(Statement *statement);
ASTNode *parse_if(Statement *statement);

ASTNode *parse_rhs(Statement *statement, int rhs_index);
ASTNode *shift_op(ASTNode *rhs);
int is_const(Token token);
ASTNode *append_to_leftmost(ASTNode *lhs, ASTNode *rhs);

#endif // PARSER_H
