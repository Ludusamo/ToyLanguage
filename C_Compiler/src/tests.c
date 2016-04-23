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
	Map m = create_map();
	return SUCCESS;
}
