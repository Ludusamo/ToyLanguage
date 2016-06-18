#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct ASTNode ASTNode;

typedef enum {
	PROG_NODE,
	DECL_NODE,
	CONST_NODE,
	ID_NODE,
	DATATYPE_NODE,
	ARITHOP_NODE,
	BOOLOP_NODE
} AST_TYPE;

struct ASTNode {
	AST_TYPE type;
	void *data;
	ASTNode **sub_nodes;
};

ASTNode *create_program_ast(int num_lines);

ASTNode *create_datatype_ast(int *datatype);

ASTNode *create_const_ast(void *data);

ASTNode *create_id_ast(const char *id);

ASTNode *create_decl_ast(int *datatype, const char *id, ASTNode *rhs);

ASTNode *create_arithop_ast(int *operation);
ASTNode *create_boolop_ast(int *operation);

#endif // AST_H
