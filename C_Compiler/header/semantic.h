#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "memory.h"
#include "shared_values.h"
#include "error.h"
#include "token.h"

int lineno;
int prev_depth;

int semantic_analysis(ASTNode *prog);
int analyze_decl(ASTNode *decl, int depth);
int analyze_assignment(ASTNode *assign, int depth);
int analyze_if(ASTNode *if_node, int depth);
int analyze_while(ASTNode *while_node, int depth);
int analyze_func_decl(ASTNode *func_decl);
int analyze_return(ASTNode *return_node);
int analyze_func_call(ASTNode *func_call);
int analyze_rhs(ASTNode *rhs, int depth);

int analyze_print(ASTNode *print_node, int depth); // TODO: REMOVE

int determine_resulting_datatype(ASTNode *op_node);
int check_datatype(ASTNode *node, int datatype);

#endif // SEMANTIC_H
