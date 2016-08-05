#include "error.h"

const char *ErrorNames[] = {
	"Unknown Reference Exception",
	"Variable Exists"
};

void throw_error(Error_Type type, const char *filename, int lineno) {
	fprintf(stderr, "Error in file %s: %s on line %d\n", filename, ErrorNames[type], lineno);
	fprintf(stderr, "Compilation failed.\n");

	exit(EXIT_FAILURE);
}
