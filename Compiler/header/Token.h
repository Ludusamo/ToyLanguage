#ifndef TOKEN_H
#define TOKEN_H

#include "StringUtil.h"
#include <stdio.h>

class Token {
public:
	// Token type declaration
	enum TOKEN_TYPE { WHITESPACE, DATATYPE, CONTROL, IDENTIFIER, NUMBER, BOOL, ARTH_OPERATOR, BOOL_OPERATOR, PAREN };
	enum SUB_DATATYPE { INT, BOOLEAN, NUM_DATATYPES};
	enum SUB_CONTROL { IF, ELSE , NUM_CONTROLS};
	enum SUB_ARTH_OPERATOR { ASSIGNMENT, ADD, SUB, MUL, DIV, NUM_ARTH_OPERATORS };
	enum SUB_BOOL_OPERATOR { EQ, NEQ, LT, GT, LTEQ, GTEQ, NUM_BOOL_OPERATORS };
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
	static bool isarthoperator(char *token);
	static bool isbooloperator(char *token);
	static bool isnum(char *token);
	static bool isbool(char *token);
private:	
	const static char **DATATYPES;
	const static char **SUBTYPE;
	const static char **CONTROLS;
	const static char **ARTH_OPERATORS;
	const static char **BOOL_OPERATORS;
};

#endif // TOKEN_H
