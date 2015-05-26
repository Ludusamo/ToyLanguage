#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <stdio.h>

class ErrorHandler {
public:
	
};

class Error {
public:
	Error() {};
	virtual ~Error() {};
	virtual void throwError(int lineno) = 0;
};

class TypeMismatchError extends Error {
public:
	void throwError(int lineno) {
		printf("Type Mismatch Error on line %i.", lineno);
	};
};

#endif // ERRORHANDLER_H
