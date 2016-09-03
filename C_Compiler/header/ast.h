#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>

#define SUB_NODE(ast, num) ast->sub_nodes[num]
#define GET_OP_TYPE(op_ast) *(int*)op_ast->data
#define GET_CONST_INT(op_ast) *(int*)op_ast->data
#define GET_AST_DECL_ID(ast) (char*) ast->sub_nodes[1]->data
#define GET_AST_STR_DATA(ast) (char*) ast->data
#define NODE_TYPE(ast) ast->type
#define GET_AST_DATATYPE(ast) *(int*) ast->sub_nodes[0]->data

typedef struct ASTNode ASTNode;
typedef enum {
	PROG_NODE,
	DECL_NODE,
	FUNC_NODE,
	RETURN_NODE,
	FUNC_CALL_NODE,
	ASSIGN_NODE,
	IF_NODE,
	WHILE_NODE,
	CONST_NODE,
	ID_NODE,
	DATATYPE_NODE,
	OPERATOR_NODE,
	VAR_NODE,
	VARLIST_NODE,
	BLANK_NODE,
	PRINT_NODE // TODO: REMOVE
} AST_TYPE;

struct ASTNode {
	AST_TYPE type;
	void *data;
	ASTNode **sub_nodes;
	int num_sub;
	int depth;
};

ASTNode *create_program_ast(int num_lines);

ASTNode *create_datatype_ast(int *datatype);

ASTNode *create_const_ast(int *datatype, void *data);

ASTNode *create_id_ast(const char *id);

ASTNode *create_decl_ast(int *datatype, const char *id, ASTNode *rhs, int depth);
ASTNode *create_assignment_ast(const char *id, ASTNode *rhs, int depth);

ASTNode *create_if_ast(ASTNode *rhs, int depth);
ASTNode *create_while_ast(ASTNode *rhs, int depth);

ASTNode *create_func_ast(int *datatype, const char *id, ASTNode *varlist, int depth);
ASTNode *create_varlist_ast(int num_var);
ASTNode *create_return_ast(int *return_type, ASTNode *rhs, int depth);
ASTNode *create_func_call_ast(int *datatype, const char *id, ASTNode *varlist, int depth);

ASTNode *create_operator_ast(int *operation);

ASTNode *create_var_ast(const char *id);

ASTNode *create_print_ast(ASTNode *rhs); // TODO: REMOVE

#endif // AST_H
