#ifndef PARSER_H
#define PARSER_H

#include "Memory/Memory.h"
#include "Util/ErrorHandler.h"

class Parser {
public:
	Parser() {
		parsingIndex = -1;	
		currentDepth = 0;
		previousDepth = 0;
		bufferIndex = 0;
		statementIndex = 0;
	};
	~Parser() {};
	bool parse(std::vector<Statement> &statements);
private:	
	Memory mem;
	int statementIndex;
	int parsingIndex;
	int currentDepth, previousDepth;
	int bufferIndex;

	// Statement type check
	bool isDeclaration(Statement &statement);
	bool isAssignment(Statement &statement);
	bool isFunctionDeclaration(Statement &statement);
	bool isFunctionCall(Statement &statement);
	bool isReturnStatement(Statement &statement, int returnType);
	bool isIfStatement(Statement &statement);
	bool isElseStatement(Statement &statement);
	bool isWhileStatement(Statement &statement);
	
	// Statement component type check
	bool isIntValue(Statement &statement);
	bool isBoolValue(Statement &statement);
	bool isCharValue(Statement &statement);

	// Statement token type check
	bool isTokenType(Statement &statement, Token::TOKEN_TYPE type);	
	bool isSubtype(Token token, int subtype);
	bool variableExists(const char *id);
	bool isVariableType(const char *id, int type);
	bool functionExists(const char *id);

	bool endOfStatement(Statement &statement);
};

#endif // PARSER_H
