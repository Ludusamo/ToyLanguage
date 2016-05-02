#include "tests.h"
#include "unit_test.h"
#include "string_util.h"
#include "map.h"

void initialize() {
	num_tests = 0;
	create_test("String Equality", &test_str_equal);
	create_test("String Add", &test_str_add);
	create_test("ATOI", &test_atoi);
	create_test("ITOA", &test_itoa);
	create_test("String Copy", &test_str_copy);
	create_test("String Less Than", &test_str_lt);
	create_test("Create Map", &test_create_map);
	create_test("Map Insert", &test_map_add);
	create_test("Map Remove", &test_map_rem);
	create_test("Map Find", &test_map_find);
	create_test("Destroy Map", &test_destroy_map);
	create_test("File Input", &test_fileio_read);
	create_test("File Output", &test_fileio_write);	
}

int main() {
	initialize();
	
	run_tests();
	return 0;
}
