#ifndef ERROR_H
#define ERROR_H

typedef enum {
	INVALID_CHARACTER_EXCEPTION	
} Error;

static char *ERRORS[] = {
	"Invalid Character Exception: The specified character is not a standard ascii character."
};

static void ThrowError(const int errorCode) {
	fprintf(stderr, "%s\n", ERRORS[errorCode]);	
}

#endif // ERROR_H
