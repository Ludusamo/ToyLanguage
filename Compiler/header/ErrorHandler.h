#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <stdio.h>

class ErrorHandler {
public:
	typedef enum {
		UndeclaredVariable,
		UndeclaredFunction,
		TypeMismatch
	} ERRORS;

	static void throwError(int lineno, int errorType) {
		switch (errorType) {
		case UndeclaredVariable:
			printf("Variable was not declared on line %i.\n", lineno);
			break;
		case UndeclaredFunction:
			printf("Function was not declared on line %i.\n", lineno);
			break;
		case TypeMismatch:
			printf("Type Mismatch Error on line %i.\n", lineno);
			break;
		}	
	}
};
#endif // ERRORHANDLER_H
