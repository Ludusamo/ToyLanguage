#include "tests.h"
#include "unit_test.h"
#include "string_util.h"
#include "file_io.h"

void initialize() {
	num_tests = 0;
}

int test_str_equal() {
	int test_a = str_equal("hello", "hello");
	int test_b = str_equal("i am not the same", "as you");
	int test_c = str_equal("blah blah \nblah", "blah blah \nblah");
	if (test_a && !test_b && test_c) return SUCCESS;
	else return FAILURE;
}

int main() {
	initialize();
	create_test("String Equality", &test_str_equal);
	run_tests();
	return 0;
}
