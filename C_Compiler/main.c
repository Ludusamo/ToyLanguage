#include "tests.h"
#include "unit_test.h"
#include "string_util.h"
#include "file_io.h"

void initialize() {
	num_tests = 0;
}

int main() {
	initialize();
	create_test("String Equality", &test_str_equal);
	run_tests();
	return 0;
}
