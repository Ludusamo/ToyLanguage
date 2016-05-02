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
	rbt_insert(m, "c", 4);
	rbt_insert(m, "b", 3);
	rbt_insert(m, "a", 2);
	if (!str_equal(m->root->key, "b")) return FAILURE;
	rbt_insert(m, "d", 5);
	if (!str_equal(m->root->link[1]->link[1]->key, "d")) return FAILURE;
	rbt_insert(m, "b", 6);
	if (m->root->data == 6) return FAILURE;
	return SUCCESS;
}

int test_map_rem() {
	Map *m = create_map();
	rbt_insert(m, "d", 5);
	rbt_insert(m, "c", 4);
	rbt_insert(m, "b", 3);
	rbt_insert(m, "a", 2);
	rbt_remove(m, "b");
	if (!str_equal(m->root->key, "c")) return FAILURE;
	rbt_remove(m, "a");
	if (m->root->link[0]) return FAILURE;
	rbt_remove(m, "a");
	return SUCCESS;
}

int test_map_find() {
	Map *m = create_map();
	rbt_insert(m, "d", 1);
	rbt_insert(m, "c", 2);
	rbt_insert(m, "a", 3);
	rbt_insert(m, "b", 4);
	rbt_insert(m, "l", 5);
	Map_Item *i = rbt_find(m, "b");	
	if (i != m->root->link[0]->link[1]) return FAILURE;
	i = rbt_find(m, "k");
	if (i) return FAILURE;
	return SUCCESS;
}

int test_destroy_map() {
	Map *m = create_map();
	rbt_insert(m, "d", 1);
	rbt_insert(m, "c", 2);
	rbt_insert(m, "a", 3);
	rbt_insert(m, "b", 4);
	rbt_insert(m, "l", 5);
	destroy_map(m);
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
