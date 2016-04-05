#include "tests.h"
#include "unit_test.h"
#include "file_io.h"

int ex_test() {
	printf("I am an example test.\n");
	return 0;
}

void initialize() {
	num_tests = 0;
}

int main() {
	initialize();
	create_test("Example Test", &ex_test);
	run_tests();
	return 0;
}
