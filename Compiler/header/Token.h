#ifndef TOKEN_H
#define TOKEN_H

class Token {
public:
	// Token type declaration
	enum TOKEN_TYPE { WHITESPACE, DATATYPE, KEYWORD, IDENTIFIER, NUMBER, OPERATOR, PAREN };
	enum SUB_DATATYPE { INT, NUM_DATATYPES};
	enum SUB_KEYWORD { IF, ELSE , NUM_KEYWORDS};
	enum SUB_OPERATOR { ASSIGNMENT, ADD, SUB, MUL, DIV, EQ, NEQ, LT, GT, LTEQ, GTEQ, NUM_OPERATORS };
	enum SUB_PAREN { LPAREN, RPAREN };

	// Token Attributes
	char *token;
	TOKEN_TYPE type;
	int subtype;

	void setToken(char *token) { this->token = token; };
	void setType(TOKEN_TYPE type) { this->type = type; };
	char *getType();
	void determineSubtype();
		
	// Functions for determining token type
	static TOKEN_TYPE identifyTokenType(char *token);	
	
	static bool isdatatype(char *token);
	static bool iswhitespace(char c);
	static bool iskeyword(char *token);
	static bool isoperator(char *token);
	static bool isnum(char *token);
private:	
	const static char **DATATYPES;
	const static char **SUBTYPE;
	const static char **KEYWORDS;
	const static char **OPERATORS;
};

#endif // TOKEN_H
