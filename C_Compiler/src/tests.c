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
	else return FAILURE;
}

int test_create_map() {
	Map m = create_map();
	return SUCCESS;
}
