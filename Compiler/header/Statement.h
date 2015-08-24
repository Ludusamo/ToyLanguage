#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>

#include "Token.h"

#define WHITESPACE_FLAG 0
#define STRING_FLAG 1
#define	DELIM_FLAG 2  

class Statement {
public:
	enum TYPE { DECL, IF, FUNC, RET, FUNC_CALL };

	Statement() { };

	Statement(const Statement &obj) {
		statement = new char(*obj.statement);
		type = obj.type;
		int depth = obj.depth;
		tokens = obj.tokens;
	};

	~Statement() { };

	int depth;
	const char *statement;
	std::vector<Token> tokens;
	TYPE type;

	void tagType(TYPE type) {this->type = type;};

	void setStatement(const char *statement) { this->statement = statement; };
	void tokenizeStatement();
private:
	int calculateDepth();
	char peekNextChar(int currIndex);
	void recordToken(const char *token, Token::TOKEN_TYPE type);
};

#endif // STATEMENT_H
