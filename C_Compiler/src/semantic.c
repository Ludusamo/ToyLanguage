#include "semantic.h"

int semantic_analysis(ASTNode *prog) {
	init_mem();
	if (prog->type != PROG_NODE) return 0;
	int status = 1;
	for (int i = 0; i < num_lines; i++) {
		switch (prog->sub_nodes[i]->type) {
		case DECL_NODE:
			status = status && analyze_decl(prog->sub_nodes[i], 0);
			break;
		}
	}
	return status;
}

int analyze_decl(ASTNode *decl, int depth) {
	char *id = (char*) decl->sub_nodes[1]->data;
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
