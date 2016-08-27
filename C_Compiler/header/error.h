#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define NUM_ERROR_TYPES 7

typedef enum {
	UNKNOWN_REFERENCE,
	VARIABLE_EXISTS,
	FUNCTION_EXISTS,
	UNEXPECTED_TOKEN,
	TYPE_MISMATCH,
	INVALID_OPERANDS,
	INSUFFICIENT_ARGS
} Error_Type;

const char *ErrorNames[NUM_ERROR_TYPES];

void throw_error(Error_Type type, const char *filename, int lineno, const char *additional);

#endif // ERROR_H
