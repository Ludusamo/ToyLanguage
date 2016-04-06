#ifndef TESTS_H
#define TESTS_H

#include "unit_test.h"
#include "string_util.h"

#define MAX_TESTS 1000

Unit_Test tests[MAX_TESTS];

int num_tests;

void create_test(const char *name, int (*test_func)());
void run_tests();

int test_str_equal();

#endif // TESTS_H
