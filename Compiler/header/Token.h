#ifndef TOKEN_H
#define TOKEN_H

#include "StringUtil.h"
#include <stdio.h>

class Token {
public:
	// Token type declaration
	enum TOKEN_TYPE { WHITESPACE, DATATYPE, CONTROL, IDENTIFIER, NUMBER, BOOL, OPERATOR, PAREN };
	enum SUB_DATATYPE { INT, BOOLEAN, NUM_DATATYPES};
	enum SUB_CONTROL { IF, ELSE , NUM_CONTROLS};
	enum SUB_OPERATOR { ASSIGNMENT, ADD, SUB, MUL, DIV, EQ, NEQ, LT, GT, LTEQ, GTEQ, NUM_OPERATORS };
	enum SUB_PAREN { LPAREN, RPAREN };

	// Token Attributes
	char *token;
	TOKEN_TYPE type;
	int subtype;

	void setToken(char *token) { this->token = StringUtil::copy(token); };
	char *getToken() { return token; };
	void setType(TOKEN_TYPE type) { this->type = type; };
	char *getType();
	void determineSubtype();
		
	// Functions for determining token type
	static TOKEN_TYPE identifyTokenType(char *token);
	
	static bool isdatatype(char *token);
	static bool iswhitespace(char c);
	static bool iscontrol(char *token);
	static bool isoperator(char *token);
	static bool isnum(char *token);
	static bool isbool(char *token);
private:	
	const static char **DATATYPES;
	const static char **SUBTYPE;
	const static char **CONTROLS;
	const static char **OPERATORS;
};

#endif // TOKEN_H
