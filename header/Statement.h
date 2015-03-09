#ifndef STATEMENT_H
#define STATEMENT_H

#include "Node.h"

#include <vector>

#include "Token.h"

#define WHITESPACE_FLAG 0
#define STRING_FLAG 1
#define	DELIM_FLAG 2  

class Statement : public Node {
public:
	int depth;
	char *statement;
	std::vector<Token> tokens;

	void setStatement(char *statement) { this->statement = statement; };
	void tokenizeStatement();
private:
	int calculateDepth();
	char peekNextChar(int currIndex);
	void recordToken(char *token, Token::TOKEN_TYPE type);
};

class IFStatement : public Statement {
public:
	std::vector<Node> childrenStatements;
};

#endif // STATEMENT_H
