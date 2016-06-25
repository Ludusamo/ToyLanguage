#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "memory.h"
#include "shared_values.h"

int semantic_analysis(ASTNode *prog);
int analyze_decl(ASTNode *decl, int depth);
int analyze_assignment(ASTNode *assign, int depth);
int analyze_rhs(ASTNode *rhs, int datatype);

#endif // SEMANTIC_H
