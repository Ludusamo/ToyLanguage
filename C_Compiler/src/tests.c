#include "tests.h"

void create_test(const char *name, int (*test_func)()) {
	if (num_tests < MAX_TESTS) {
		tests[num_tests++] = (Unit_Test) {name, test_func};
	}
}

void run_tests() {
	for (int i = 0; i < num_tests; i++) {
		run_test(tests[i]);
		printf("\n");
	}
}

int test_str_equal() {
	int test_a = str_equal("hello", "hello");
	int test_b = str_equal("i am not the same", "as you");
	int test_c = str_equal("blah blah \nblah", "blah blah \nblah");
	if (test_a && !test_b && test_c) return SUCCESS;
	return FAILURE;
}

int test_str_add() {
	char *c = str_add("Hello ", "World!");
	if (str_equal(c, "Hello World!")) return SUCCESS;
	return FAILURE;
}

int test_atoi() {
	int i = atoi("53");
	if (i == 53) return SUCCESS;
	return FAILURE;
}

int test_itoa() {
	char *a = itoa(10);
	if (str_equal(a, "10")) return SUCCESS;
	return FAILURE;
}

int test_str_copy() {
	char *copy = str_copy("Test 123");
	if (str_equal(copy, "Test 123")) return SUCCESS;
	return FAILURE;
}

int test_str_lt() {
	if (str_lt("a", "b") && str_lt("aa", "ab")) return SUCCESS;
	return FAILURE;
}

int test_create_map() {
	Map *m = create_map();
	return SUCCESS;
}

int test_map_add() {
	Map *m = create_map();
	int c = 1, b = 3, a = 2, d = 5, b2 = 6;
	rbt_insert(m, "c", (void*) &c);
	rbt_insert(m, "b", (void*) &b);
	rbt_insert(m, "a", (void*) &a);
	if (!str_equal(m->root->key, "b")) return FAILURE;
	rbt_insert(m, "d", (void*) &d);
	if (!str_equal(m->root->link[1]->link[1]->key, "d")) return FAILURE;
	rbt_insert(m, "b", (void*) &b2);
	if (*(int*)m->root->data == 6) return FAILURE;
	if (m->num_values != 5) return FAILURE;
	return SUCCESS;
}

int test_map_rem() {
	Map *m = create_map();
	int d = 5, c = 4, b = 3, a = 2;
	rbt_insert(m, "d", (void*) &d);
	rbt_insert(m, "c", (void*) &c);
	rbt_insert(m, "b", (void*) &b);
	rbt_insert(m, "a", (void*) &a);
	rbt_remove(m, "b");
	if (m->num_values != 3) return FAILURE;
	if (!str_equal(m->root->key, "c")) return FAILURE;
	rbt_remove(m, "a");
	if (m->root->link[0]) return FAILURE;
	rbt_remove(m, "a");
	return SUCCESS;
}

int test_map_find() {
	Map *m = create_map();
	int d = 1, c = 2, a = 3, b = 4, l = 5;
	rbt_insert(m, "d", (void*) &d);
	rbt_insert(m, "c", (void*) &c);
	rbt_insert(m, "a", (void*) &a);
	rbt_insert(m, "b", (void*) &b);
	rbt_insert(m, "l", (void*) &l);
	Map_Item *i = rbt_find(m, "b");	
	if (i != m->root->link[0]->link[1]) return FAILURE;
	i = rbt_find(m, "k");
	if (i) return FAILURE;
	return SUCCESS;
}

int test_destroy_map() {
	Map *m = create_map();
	int d = 1, c = 2, a = 3, b = 4, l = 5;
	rbt_insert(m, "d", (void*) &d);
	rbt_insert(m, "c", (void*) &c);
	rbt_insert(m, "a", (void*) &a);
	rbt_insert(m, "b", (void*) &b);
	rbt_insert(m, "l", (void*) &l);
	destroy_map(m);
	return SUCCESS;
}

int test_create_linked_list() {
	Linked_List *list = create_linked_list();
	if (!list) return FAILURE;
	return SUCCESS;
}

int test_add_link() {
	Linked_List *list = create_linked_list();
	if (!add_link(list, 10)) return FAILURE;
	if (!add_link(list, 20)) return FAILURE;
	if (list->head->val != 10) return FAILURE;
	if (list->head->next->val != 20) return FAILURE;
	if (list->tail->val != 20) return FAILURE;
	return SUCCESS;
}

int test_remove_link() {
	Linked_List *list = create_linked_list();
	if (!add_link(list, 10)) return FAILURE;
	if (!add_link(list, 20)) return FAILURE;
	if (list->tail->val != 20) return FAILURE;
	if (!remove_link(list, 20)) return FAILURE;
	if (list->tail->val != 10) return FAILURE;
	return SUCCESS;
}

int test_destroy_linked_list() {
	Linked_List *list = create_linked_list();
	Link *head = list->head;
	if (!add_link(list, 10)) return FAILURE;
	if (!add_link(list, 20)) return FAILURE;
	destroy_linked_list(list);
	if (head) return FAILURE;
	return SUCCESS;
}

int test_fileio_read() {
	FILE *in = fopen("res/test.in", "r");
	char *line1 = read_line(in);
	char *line2 = read_line(in);
	char *line3 = read_line(in);
	if (!str_equal(line1, "Hello I am a test.\n") || !str_equal("I am the second line", line2) || line3) {
		fclose(in);	
		return FAILURE;
	}
	fclose(in);	
	return SUCCESS;
}

int test_fileio_write() {
	FILE *out = fopen("res/test.out", "w");
	write_line(out, "Hello World!");
	fclose(out);	
	out = fopen("res/test.out", "r");
	char *line = read_line(out);
	if (!str_equal(line, "Hello World!\n")) {
		fclose(out);
		return FAILURE;
	}
	return SUCCESS;
}

int test_create_token() {
	Token *token = create_token("test");
	if (!str_equal(token->token_str, "test")) return FAILURE;
	return SUCCESS;
}

int test_identify_token() {
	Token *token = malloc(sizeof(Token));
	token->token_str = " ";
	identify_token_type(token);
	if (!is_type(*token, WHITESPACE)) return FAILURE;
	token->token_str = "int";
	identify_token_type(token);
	if (!is_type(*token, DATATYPE) || !is_subtype(*token, INT)) return FAILURE;
	return SUCCESS;
}

int test_create_statement() {
	Statement *statement = create_statement("int a");	
	return SUCCESS;
}

int test_tokenize_statement() {
	Statement *statement = create_statement("int a");
	tokenize_statement(statement);
	if (statement->num_tokens < 2) return FAILURE;
	if (!is_type(statement->tokens[0], DATATYPE)) return FAILURE;
	if (!is_type(statement->tokens[1], IDENTIFIER)) return FAILURE;
	return SUCCESS;
}

int test_lex() {
	FILE *file = fopen("res/lex_test.in", "r");	
	Statement *statements = lex(file);
	fclose(file);
	if (!statements) return FAILURE;
	Statement s1 = statements[0];
	Statement s3 = statements[2];
	Statement s4 = statements[3];
	if (!is_type(s1.tokens[0], DATATYPE) || !is_type(s1.tokens[1], IDENTIFIER))
		return FAILURE;
	if (!is_subtype(s3.tokens[0], BOOL)) return FAILURE;
	if (!is_type(s4.tokens[1], ARITHOP)) return FAILURE;

	return SUCCESS;
}

int test_parse() {
	FILE *file = fopen("res/parse_test.in", "r");	
	Statement *statements = lex(file);
	fclose(file);
	ASTNode *prog = parse(statements);
	if (statements[0].type != DECL || statements[1].type != DECL) return FAILURE;
	if (NODE_TYPE(prog) != 0) return FAILURE;
	if (NODE_TYPE(SUB_NODE(prog, 0)) != 1) return FAILURE;
	return SUCCESS;
}

int test_rhs() {
	Statement *statement = create_statement("int a = b * (300 + 200)");
	tokenize_statement(statement);
	
	ASTNode *rhs = parse_rhs(statement, 3);
	if (!rhs) return FAILURE;
	if (NODE_TYPE(rhs) != ARITHOP_NODE || GET_OP_TYPE(rhs) != MULTIPLY) return FAILURE;
	if (NODE_TYPE(SUB_NODE(rhs, 1)) != ARITHOP_NODE || GET_OP_TYPE(SUB_NODE(rhs, 1)) != PLUS) return FAILURE;
	if (NODE_TYPE(SUB_NODE(rhs, 0)) != VAR_NODE) return FAILURE;
	if (GET_CONST_INT(SUB_NODE(SUB_NODE(rhs, 1), 0)) != 300) return FAILURE;
	if (GET_CONST_INT(SUB_NODE(SUB_NODE(rhs, 1), 1)) != 200) return FAILURE;
	return SUCCESS;
}

int test_ast() {
	int a = 1;
	int b = 20;
	ASTNode *rhs = create_const_ast(&b);
	ASTNode *node = create_decl_ast(&a, "test", rhs);
	if (NODE_TYPE(SUB_NODE(node, 0)) != DATATYPE_NODE) return FAILURE;
	if (!str_equal(GET_AST_DECL_ID(node), "test")) return FAILURE;
	if (GET_CONST_INT(SUB_NODE(node, 2)) != 20) return FAILURE;
	return SUCCESS;
}

int test_semantic_analysis() {
	num_lines = 2;

	Statement *statements = malloc(sizeof(Statement) * 2);
	Statement *statement1 = create_statement("int a = 100 * (300 + 200)\n");
	Statement *statement2 = create_statement("int b = a\n");
	tokenize_statement(statement1);
	tokenize_statement(statement2);
	statements[0] = *statement1;
	statements[1] = *statement2;

	ASTNode *prog = parse(statements);
	int status = semantic_analysis(prog);
	if (!status) return FAILURE;	
	return SUCCESS;
}

int test_compile() {
	clear_mem();
	num_lines = 2;
	Statement *statements = malloc(sizeof(Statement) * 2);
	Statement *statement1 = create_statement("int a = 100 * (300 + 200)\n");
	Statement *statement2 = create_statement("int b = a\n");
	tokenize_statement(statement1);
	tokenize_statement(statement2);
	statements[0] = *statement1;
	statements[1] = *statement2;

	ASTNode *prog = parse(statements);
	int status = semantic_analysis(prog);
	if (!status) return FAILURE;

	Linked_List *instructions = compile(prog);

	Link *head = instructions->head;
	printf("\nInstructions\n");
	while (head) {
		printf("%i\n", head->val);
		head = head->next;
	}

	return SUCCESS;
}
