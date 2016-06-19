#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>

#define SUB_NODE(ast, num) ast->sub_nodes[num]
#define GET_OP_TYPE(op_ast) *(int*)op_ast->data
#define GET_CONST_INT(op_ast) *(int*)op_ast->data
#define GET_AST_DECL_ID(ast) (char*) ast->sub_nodes[1]->data
#define NODE_TYPE(ast) ast->type
#define GET_AST_DATATYPE(ast) *(int*) ast->sub_nodes[0]->data

typedef struct ASTNode ASTNode;

typedef enum {
	PROG_NODE,
	DECL_NODE,
	CONST_NODE,
	ID_NODE,
	DATATYPE_NODE,
	ARITHOP_NODE,
	BOOLOP_NODE,
	VAR_NODE
} AST_TYPE;

struct ASTNode {
	AST_TYPE type;
	void *data;
	ASTNode **sub_nodes;
	int num_sub;
};

ASTNode *create_program_ast(int num_lines);

ASTNode *create_datatype_ast(int *datatype);

ASTNode *create_const_ast(void *data);

ASTNode *create_id_ast(const char *id);

ASTNode *create_decl_ast(int *datatype, const char *id, ASTNode *rhs);

ASTNode *create_arithop_ast(int *operation);
ASTNode *create_boolop_ast(int *operation);

ASTNode *create_var_ast(int *datatype, const char *id);

#endif // AST_H
