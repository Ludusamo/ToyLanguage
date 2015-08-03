#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Statement.h"
#include "Token.h"
#include "Memory.h"
#include "ErrorHandler.h"

class Parser {
public:
	Parser() {
		parsingIndex = -1;	
	};
	~Parser() {};
	bool parse(std::vector<Statement> &statements, Memory &mem);
private:	
	int statementIndex;
	int parsingIndex;

	// Statement type check
	bool isDeclaration(Statement &statement, Memory &mem);
	bool isIfStatement(Statement &statement, Memory &mem);
	
	// Statement component type check
	bool isIntValue(Statement &statement, Memory &mem);
	bool isBoolValue(Statement &statement, Memory &mem);

	// Statement token type check
	bool isTokenType(Statement &statement, Token::TOKEN_TYPE type);	
	bool isSubtype(Token token, int subtype);
	bool variableExists(const char *id, Memory &mem);
	bool isVariableType(const char *id, int type, Memory &mem);

	bool endOfStatement(Statement &statement);
};

#endif // PARSER_H
