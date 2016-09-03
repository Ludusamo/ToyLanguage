#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "statement.h"
#include "ast.h"
#include "memory.h"
#include "shared_values.h"
#include "error.h"

int statement_index;
int lineno;
int in_function, function_depth, *function_return_type;

ASTNode *parse(Statement *statements);
ASTNode *parse_line(Statement *statement);
ASTNode *parse_declaration(Statement *statement);
ASTNode *parse_assignment(Statement *statement);
ASTNode *parse_if(Statement *statement);
ASTNode *parse_while(Statement *statement);
ASTNode *parse_function(Statement *statement);
ASTNode *parse_return(Statement *statement);
ASTNode *parse_func_call(Statement *statement, int index);

ASTNode *parse_parameter_list();
ASTNode *parse_rhs(Statement *statement, int rhs_index);
ASTNode *shift_op(ASTNode *rhs);
int is_const(Token token);
int *determine_const_type(int type);
ASTNode *append_to_leftmost(ASTNode *lhs, ASTNode *rhs);

#endif // PARSER_H
