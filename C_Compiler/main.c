#include "tests.h"
#include "unit_test.h"
#include "string_util.h"
#include "map.h"

void initialize() {
	num_tests = 0;
}

int main() {
	initialize();
	create_test("String Equality", &test_str_equal);
	create_test("Create Map", &test_create_map);
	run_tests();
	return 0;
}
