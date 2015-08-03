#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>

#include "Token.h"

#define WHITESPACE_FLAG 0
#define STRING_FLAG 1
#define	DELIM_FLAG 2  

class Statement {
public:
	enum TYPE { DECL, IF };
	int depth;
	char *statement;
	std::vector<Token> tokens;
	TYPE type;

	void tagType(TYPE type) {this->type = type;};

	Token getToken(int index);
	void setStatement(char *statement) { this->statement = statement; };
	void tokenizeStatement();
private:
	int calculateDepth();
	char peekNextChar(int currIndex);
	void recordToken(char *token, Token::TOKEN_TYPE type);
};

#endif // STATEMENT_H
