#ifndef UNITTEST_H
#define UNITTEST_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	SUCCESS,
	FAILURE
} RUN_CODE;

typedef struct {
	const char *name;
	int (*run)();
} Unit_Test;

int run_test(Unit_Test test);

#endif // UNITTEST_H
