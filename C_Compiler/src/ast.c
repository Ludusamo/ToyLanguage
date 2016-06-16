#include "ast.h"

ASTNode *create_program_ast(int num_lines) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = PROG_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode*) * num_lines);
	return node;
}

ASTNode *create_datatype_ast(int *datatype) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = DATATYPE_NODE;
	node->data = (void*) datatype;
	return node;
}

ASTNode *create_const_ast(void *data) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = CONST_NODE;
	node->data = data;
	return node;
}

ASTNode *create_id_ast(const char *id) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = ID_NODE;
	node->data = (void*) id;
	return node;
}

ASTNode *create_decl_ast(int *datatype, const char *id, void *data) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = DECL_NODE;
	node->sub_nodes = malloc(sizeof(ASTNode*) * 3);
	node->sub_nodes[0] = create_datatype_ast(datatype);
	node->sub_nodes[1] = create_id_ast(id);
	node->sub_nodes[2] = create_const_ast(data);
	return node;
}
