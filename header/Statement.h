#ifndef STATEMENT_H
#define STATEMENT_H

#include "Token.h"

class Statement {
public:
	char *statement;
	Token *tokens;

	void setStatement(char *statement);
	void tokenizeStatement();
};

#endif // STATEMENT_H
