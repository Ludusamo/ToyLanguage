#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	UNKNOWN_REFERENCE,
	VARIABLE_EXISTS,
	FUNCTION_EXISTS,
	UNEXPECTED_TOKEN,
	TYPE_MISMATCH,
	INVALID_OPERANDS,
	INSUFFICIENT_ARGS,
	MAXIMUM_DEPTH_EXCEEDED,
	INACTIVE_DEPTH,
	NUM_ERROR_TYPES
} Error_Type;

const char *ErrorNames[NUM_ERROR_TYPES];

void throw_error(Error_Type type, const char *filename, int lineno, const char *additional);

#endif // ERROR_H
