#include "error.h"

const char *ErrorNames[] = {
	"Unknown Reference Exception",
	"Variable Exists",
	"Function Exists",
	"Unexpected Token",
	"Type Mismatch",
	"Invalid Operands",
	"Insufficient Arguments"
};

void throw_error(Error_Type type, const char *filename, int lineno, const char *additional) {
	fprintf(stderr, "Error in file %s: %s on line %d\n", filename, ErrorNames[type], lineno);
	if (additional) fprintf(stderr, "%s\n", additional);
	fprintf(stderr, "Compilation failed.\n");

	exit(EXIT_FAILURE);
}
