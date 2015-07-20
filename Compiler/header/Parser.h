#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Node.h"
#include "Statement.h"
#include "Token.h"

class Parser {
public:
	std::vector<int> parse(Statement &statement);
private:	
	std::vector<int> bytecode;
	int statementIndex;

	// Statement type check
	bool isDeclaration(Statement &statement);
	
	// Statement component type check
	bool isValue(Statement &statement);

	// Statement token type check
	bool isTokenType(Statement &statement, Token::TOKEN_TYPE type);	
	bool isSubtype(Token token, int subtype);

	bool endOfStatement(Statement &statement);
};

#endif // PARSER_H
