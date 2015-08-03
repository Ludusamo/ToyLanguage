#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <stdio.h>

class UndeclaredVariableError {
public:
	static void throwError(int lineno) {
		printf("Variable was not declared on line %i.\n", lineno);
	};
};

class TypeMismatchError {
public:
	static void throwError(int lineno) {
		printf("Type Mismatch Error on line %i.\n", lineno);
	};
};

class ErrorHandler {
public:
	typedef enum {
		UndeclaredVariable,
		TypeMismatch
	} ERRORS;

	static void throwError(int lineno, int errorType) {
		switch (errorType) {
		case UndeclaredVariable:
			UndeclaredVariableError::throwError(lineno);
			break;
		case TypeMismatch:
			TypeMismatchError::throwError(lineno);
			break;
		}	
	}
};
#endif // ERRORHANDLER_H
