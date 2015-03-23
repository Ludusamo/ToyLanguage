#ifndef TOKEN_H
#define TOKEN_H

class Token {
public:
	enum TOKEN_TYPE { WHITESPACE, KEYWORD, IDENTIFIER, NUMBER, OPERATOR, PAREN };
	char *token;
	
	void setToken(char *token) { this->token = token; };
	void setType(TOKEN_TYPE type) { this->type = type; };
	char *getType();
	void determineSubtype(){};

	static TOKEN_TYPE identifyTokenType(char *token);

	TOKEN_TYPE type;
	
	static bool iswhitespace(char c);
	static bool iskeyword(char *token);
	static bool isoperator(char *token);
	static bool isnum(char *token);
private:	
	const static char **KEYWORDS;
	const static int numKeywords;
	const static char **OPERATORS;
	const static int numOperators;
};

#endif // TOKEN_H
