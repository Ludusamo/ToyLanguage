#ifndef TOKEN_H
#define TOKEN_H

#include "Util/StringUtil.h"
#include <stdio.h>
#include <ctype.h>

class Token {
public:
	// Token type declaration
	enum TOKEN_TYPE { WHITESPACE, DATATYPE, CONTROL, IDENTIFIER, NUMBER, BOOL, ARTH_OPERATOR, BOOL_OPERATOR, PAREN, COMMA, S_QUOTE, D_QUOTE, RETURN };
	enum SUB_DATATYPE { VOID, INT, BOOLEAN, CHAR, NUM_DATATYPES};
	enum SUB_CONTROL { IF, ELSE, WHILE, NUM_CONTROLS};
	enum SUB_ARTH_OPERATOR { ASSIGNMENT, ADD, SUB, MUL, DIV, NUM_ARTH_OPERATORS };
	enum SUB_BOOL_OPERATOR { EQ, NEQ, LT, GT, LTEQ, GTEQ, NUM_BOOL_OPERATORS };
	enum SUB_PAREN { LPAREN, RPAREN };

	Token() {
		token = new char;	
	};
	Token(const Token &obj) {
		token = StringUtil::copy(obj.token);
		type = obj.type;
		subtype = obj.subtype;
	};
	~Token(){
		delete token;
		token = NULL;
	};

	// Token Attributes
	const char *token;
	TOKEN_TYPE type;
	int subtype;

	void setToken(const char *token) { this->token = StringUtil::copy(token); };
	const char *getToken() { return token; };
	void setType(TOKEN_TYPE type) { this->type = type; };
	char *getType();
	void determineSubtype();
		
	// Functions for determining token type
	static TOKEN_TYPE identifyTokenType(const char *token);
	
	static bool iscomma(char c);
	static bool issquote(char c);
	static bool isdquote(char c);
	static bool isdatatype(const char *token);
	static bool iswhitespace(char c);
	static bool iscontrol(const char *token);
	static bool isarthoperator(const char *token);
	static bool isbooloperator(const char *token);
	static bool isnum(const char *token);
	static bool isbool(const char *token);
	static bool isreturn(const char *token);
private:	
	const static char **DATATYPES;
	const static char **SUBTYPE;
	const static char **CONTROLS;
	const static char **ARTH_OPERATORS;
	const static char **BOOL_OPERATORS;
};

#endif // TOKEN_H
