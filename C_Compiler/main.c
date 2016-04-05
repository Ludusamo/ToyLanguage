#include "unit_test.h"
#include "file_io.h"

int ex_test() {
	printf("I am an example test.\n");
	return 0;
}

int main() {
	Unit_Test test;
	test.run = &ex_test;
	test.name = "Example Test";
	run_test(test);
	return 0;
}
