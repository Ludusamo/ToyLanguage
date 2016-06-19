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
		if (get_global_addr(id) != -1) {
			// TODO: Error Checking
			printf("ERROR: VARIABLE \"%s\" EXISTS\n", id);
		} else {
			int status = create_global_variable(id, NUM_GLOBAL);
			if (status) return 1;
		}
	}
	return 0;
}
