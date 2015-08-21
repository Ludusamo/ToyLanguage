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
	bool parse(std::vector<Statement> &statements);
private:	
	Memory mem;
	int statementIndex;
	int parsingIndex;
	int currentDepth;

	// Statement type check
	bool isDeclaration(Statement &statement);
	bool isFunctionDeclaration(Statement &statement);
	bool isFunctionCall(Statement &statement);
	bool isReturnStatement(Statement &statement);
	bool isIfStatement(Statement &statement);
	
	// Statement component type check
	bool isIntValue(Statement &statement);
	bool isBoolValue(Statement &statement);

	// Statement token type check
	bool isTokenType(Statement &statement, Token::TOKEN_TYPE type);	
	bool isSubtype(Token token, int subtype);
	bool variableExists(const char *id);
	bool isVariableType(const char *id, int type);
	bool functionExists(const char *id);

	bool endOfStatement(Statement &statement);
};

#endif // PARSER_H
