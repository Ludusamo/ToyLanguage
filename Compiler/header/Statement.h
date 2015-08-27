#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>

#include "Token.h"

#define WHITESPACE 0
#define STRING 1
#define	DELIM 2  

class Statement {
public:
	enum TYPE { DECL, ASSIGN, IF, FUNC, RET, FUNC_CALL };

	Statement() { };
	~Statement() { };
	Statement(const Statement &obj);


	int depth;
	std::vector<Token> tokens;
	TYPE type;

	void tagType(TYPE type) {this->type = type;};

	void calculateDepth(const char *statement);
};

#endif // STATEMENT_H
