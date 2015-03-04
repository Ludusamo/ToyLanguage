#include "Statement.h"

#include <stdlib.h>

void Statement::setStatement(char *statement) {
	this->statement = statement;
}

void Statement::tokenizeStatement() {
	char *buffer = (char*) malloc(sizeof(statement));
	int i = 0, currIndex = 0;
					
	while (i != sizeof(statement)) {
		buffer[currIndex] = statement[i];	
		i++;
		currIndex++;
	}
}
