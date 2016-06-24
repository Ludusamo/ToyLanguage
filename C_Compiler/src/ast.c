#include "ast.h"

ASTNode *create_program_ast(int num_lines) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = PROG_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * num_lines);
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

ASTNode *create_const_ast(void *data) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = CONST_NODE;
	node->data = data;
	node->num_sub = 0;
	return node;
}

ASTNode *create_id_ast(const char *id) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = ID_NODE;
	node->data = (void*) id;
	node->num_sub = 0;
	return node;
}

ASTNode *create_decl_ast(int *datatype, const char *id, ASTNode *rhs) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = DECL_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode) * 3);
	SUB_NODE(node, 0) = create_datatype_ast(datatype);
	SUB_NODE(node, 1) = create_id_ast(id);
	SUB_NODE(node, 2) = rhs;
	node->num_sub = 3;
	return node;
}

ASTNode *create_arithop_ast(int *operation) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = ARITHOP_NODE;
	node->data = (void*) operation;
	node->sub_nodes = malloc(sizeof(ASTNode) * 2);
	node->num_sub = 2;
	return node;
}

ASTNode *create_boolop_ast(int *operation) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = BOOLOP_NODE;
	node->data = (void*) operation;
	node->sub_nodes = malloc(sizeof(ASTNode) * 2);
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
