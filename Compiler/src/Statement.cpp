#include "Statement.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Statement::Statement(const Statement &obj) {
	type = obj.type;
	int depth = obj.depth;
	tokens = obj.tokens;
}

void Statement::calculateDepth(const char *statement) {
	int count = 0;
	for (int i = 0; i < strlen(statement); i++) {
		if (!Token::iswhitespace(statement[i])) break;
		count++;		
	}	
	depth = count;
}
