#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>

#include "Token.h"

#define WHITESPACE_FLAG 0
#define STRING_FLAG 1
#define	DELIM_FLAG 2  

class Statement {
public:
	int depth;
	char *statement;
	std::vector<Token> tokens;

	void setStatement(char *statement);
	void tokenizeStatement();
private:
	int calculateDepth();
	char peekNextChar(int currIndex);
	void recordToken(char *token, Token::TOKEN_TYPE type);
	bool iswhitespace(char c);
};

#endif // STATEMENT_H
