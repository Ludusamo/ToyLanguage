#include "tests.h"

void create_test(const char *name, int (*test_func)()) {
	if (num_tests < MAX_TESTS) {
		tests[num_tests++] = (Unit_Test) {name, test_func};
	}
}

void run_tests() {
	for (int i = 0; i < num_tests; i++) {
		run_test(tests[i]);
	}
}
