#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define NUM_ERROR_TYPES 1

typedef enum {
	UNKNOWN_REFERENCE	
} Error_Type;

const char *ErrorNames[NUM_ERROR_TYPES];

void throw_error(Error_Type type, const char *filename, int lineno);

#endif // ERROR_H
