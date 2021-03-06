#include "ast.h"

int delete_ast(ASTNode *ast) {
	for (int i = 0; i < ast->num_sub; i++) {
		delete_ast(ast->sub_nodes[i]);
	}
	ast->data = 0;
	free(ast->data);
	ast->sub_nodes = 0;
	free(ast->sub_nodes);
	ast = 0;
	free(ast);
	return 0;
}

ASTNode *create_program_ast(int num_lines) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = PROG_NODE;
	node->num_sub = num_lines;
	node->sub_nodes = calloc(sizeof(ASTNode), num_lines);
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
	node->num_sub = 1;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	SUB_NODE(node, 0) = create_datatype_ast(datatype);
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
	node->num_sub = 3;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	node->depth = depth;
	SUB_NODE(node, 0) = create_datatype_ast(datatype);
	SUB_NODE(node, 1) = create_id_ast(id);
	SUB_NODE(node, 2) = rhs;
	return node;
}

ASTNode *create_assignment_ast(const char *id, ASTNode *rhs, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = ASSIGN_NODE;
	node->num_sub = 2;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	node->depth = depth;
	SUB_NODE(node, 0) = create_id_ast(id);
	SUB_NODE(node, 1) = rhs;
	return node;
}

ASTNode *create_if_ast(ASTNode *rhs, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = IF_NODE;
	node->num_sub = 1;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	node->depth = depth;
	SUB_NODE(node, 0) = rhs;
	return node;
}

ASTNode *create_while_ast(ASTNode *rhs, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = WHILE_NODE;
	node->num_sub = 1;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	node->depth = depth;
	SUB_NODE(node, 0) = rhs;
	return node;
}

ASTNode *create_func_ast(int *datatype, const char *id, ASTNode *varlist, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = FUNC_NODE;
	node->num_sub = 3;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	node->depth = depth;
	SUB_NODE(node, 0) = create_datatype_ast(datatype);
	SUB_NODE(node, 1) = create_id_ast(id);
	SUB_NODE(node, 2) = varlist;
	return node;
}

ASTNode *create_return_ast(int *return_type, ASTNode *rhs, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = RETURN_NODE;
	node->num_sub = 2;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	node->depth = depth;
	SUB_NODE(node, 0) = create_datatype_ast(return_type);
	SUB_NODE(node, 1) = rhs;
	return node;
}

ASTNode *create_varlist_ast(int num_var) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = VARLIST_NODE;
	node->num_sub = num_var;
	node->sub_nodes = calloc(sizeof(ASTNode), num_var);
	return node;
}

ASTNode *create_func_call_ast(int *datatype, const char *id, ASTNode *varlist, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = FUNC_CALL_NODE;
	node->num_sub = 3;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	node->depth = depth;
	SUB_NODE(node, 0) = create_datatype_ast(datatype);
	SUB_NODE(node, 1) = create_id_ast(id);
	SUB_NODE(node, 2) = varlist;
	return node;
}


ASTNode *create_operator_ast(int *operation) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = OPERATOR_NODE;
	node->data = (void*) operation;
	node->num_sub = 3;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	return node;
}

ASTNode *create_var_ast(const char *id) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = VAR_NODE;
	node->num_sub = 2;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	SUB_NODE(node, 1) = create_id_ast(id);
	return node;
}

// TODO: REMOVE
ASTNode *create_print_ast(ASTNode *rhs, int depth) {
	ASTNode *node = malloc(sizeof(ASTNode));
	node->type = PRINT_NODE;
	node->num_sub = 1;
	node->sub_nodes = calloc(sizeof(ASTNode), node->num_sub);
	node->depth = depth;
	SUB_NODE(node, 0) = rhs;
	return node;
}
