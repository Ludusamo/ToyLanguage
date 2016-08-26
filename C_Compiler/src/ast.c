#include "ast.h"

ASTNode *create_program_ast(int num_lines) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = PROG_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * num_lines);
	for (int i = 0; i < num_lines; i++) {
		SUB_NODE(node, i) = NULL;
	}
	node->num_sub = num_lines;
	return node;
}

ASTNode *create_datatype_ast(int *datatype) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = DATATYPE_NODE;
	node->data = (void*) datatype;
	node->num_sub = 0;
	return node;
}

ASTNode *create_const_ast(int *datatype, void *data) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = CONST_NODE;
	node->data = data;
	node->sub_nodes = malloc(sizeof(ASTNode));
	SUB_NODE(node, 0) = create_datatype_ast(datatype);
	node->num_sub = 1;
	return node;
}

ASTNode *create_id_ast(const char *id) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = ID_NODE;
	node->data = (void*) id;
	node->num_sub = 0;
	return node;
}

ASTNode *create_decl_ast(int *datatype, const char *id, ASTNode *rhs, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = DECL_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * 3);
	node->depth = depth;
	SUB_NODE(node, 0) = create_datatype_ast(datatype);
	SUB_NODE(node, 1) = create_id_ast(id);
	SUB_NODE(node, 2) = rhs;
	node->num_sub = 3;
	return node;
}

ASTNode *create_assignment_ast(const char *id, ASTNode *rhs, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = ASSIGN_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * 2);
	node->depth = depth;
	SUB_NODE(node, 0) = create_id_ast(id);
	SUB_NODE(node, 1) = rhs;
	node->num_sub = 2;
	return node;
}

ASTNode *create_if_ast(ASTNode *rhs, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = IF_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * 1);
	node->depth = depth;
	SUB_NODE(node, 0) = rhs;
	node->num_sub = 1;
	return node;
}

ASTNode *create_func_ast(int *datatype, const char *id, ASTNode *varlist, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = FUNC_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * 3);
	node->depth = depth;
	SUB_NODE(node, 0) = create_datatype_ast(datatype);
	SUB_NODE(node, 1) = create_id_ast(id);
	SUB_NODE(node, 2) = varlist;
	node->num_sub = 3;
	return node;
}

ASTNode *create_return_ast(int *return_type, ASTNode *rhs, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = RETURN_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * 2);
	node->depth = depth;
	SUB_NODE(node, 0) = create_datatype_ast(return_type);
	SUB_NODE(node, 1) = rhs;
	node->num_sub = 2;
	return node;
}

ASTNode *create_varlist_ast(int num_var) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = VARLIST_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * num_var);
	for (int i = 0; i < num_var; i++) {
		SUB_NODE(node, i) = NULL;
	}
	node->num_sub = num_var;
	return node;
}

ASTNode *create_operator_ast(int *operation) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = OPERATOR_NODE;
	node->data = (void*) operation;
	node->sub_nodes = malloc(sizeof(ASTNode) * 2);
	SUB_NODE(node, 0) = NULL;
	SUB_NODE(node, 1) = NULL;
	node->num_sub = 2;
	return node;
}

ASTNode *create_var_ast(const char *id) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = VAR_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * 1);
	SUB_NODE(node, 0) = create_id_ast(id);
	node->num_sub = 1;
	return node;
}
