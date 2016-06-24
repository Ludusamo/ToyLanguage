#include "semantic.h"

int semantic_analysis(ASTNode *prog) {
	init_mem();
	if (NODE_TYPE(prog) != PROG_NODE) return 0;
	int status = 1;
	for (int i = 0; i < num_lines; i++) {
		switch (NODE_TYPE(SUB_NODE(prog, i))) {
		case DECL_NODE:
			status = status && analyze_decl(SUB_NODE(prog, i), 0);
			break;
		}
	}
	return status;
}

int analyze_decl(ASTNode *decl, int depth) {
	char *id = GET_AST_DECL_ID(decl);
	if (depth == 0) {
		if (get_global_addr(id)) {
			// TODO: Error Checking
			printf("ERROR: VARIABLE \"%s\" EXISTS\n", id);
		} else {
			Memory_Address *addr = create_mem_addr(1, NUM_GLOBAL, GET_AST_DATATYPE(decl));
			int status = create_global_variable(id, addr);
			ASTNode *rhs = SUB_NODE(decl, 2);
			status = status && analyze_rhs(rhs, GET_AST_DATATYPE(decl));
			if (status) return 1;
		}
	}
	return 0;
}

int analyze_rhs(ASTNode *rhs, int datatype) {
	int sp = 0;
	ASTNode **stack = malloc(sizeof(rhs) * 255);
	stack[sp++] = rhs;
	
	ASTNode *cur_node;
	while (sp > 0) {
		cur_node = stack[--sp];
		switch (NODE_TYPE(cur_node)) {
		case CONST_NODE:
			sp--;
			break;
		case ARITHOP_NODE:
			stack[sp++] = SUB_NODE(cur_node, 1);
			stack[sp++] = SUB_NODE(cur_node, 0);
			break;
		case BOOLOP_NODE:
			stack[sp++] = SUB_NODE(cur_node, 1);
			stack[sp++] = SUB_NODE(cur_node, 0);
			break;
		case VAR_NODE:	
			if (GET_AST_DATATYPE(cur_node) == datatype) sp--;
			else return 0;
			break;
		}
	}
	return 1;	
}
