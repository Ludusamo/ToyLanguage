#include "Token.h"

#include <ctype.h>

const static char *KEYWORD_BUFFER[] = { "IF", "ELSE", "INT" };
const char** Token::KEYWORDS = KEYWORD_BUFFER;

void Token::setToken(char *token) {
	this->token = token;
}

void Token::setType(TOKEN_TYPE type) {
	this->type = type;
}

char *Token::getType() {
	switch (type) {
	case WHITESPACE:
		return (char*) "WHITESPACE";
	case KEYWORD:
		return (char*) "KEYWORD";
	case IDENTIFIER:
		return (char*) "IDENTIFIER";
	case NUMBER:
		return (char*) "NUMBER";
	case ASSIGN_OP:
		return (char*) "ASSIGNMENT OPERATOR";
	case LPAREN:
		return (char*) "LEFT PARENTHESIS";
	case RPAREN:
		return (char*) "RIGHT PARENTHESIS";
	}
}

Token::TOKEN_TYPE Token::identifyTokenType(char *token) {
	if (token[0] == '\t' || token[0] == '\n' || token[0] == ' ') // Checks for whitespace
		return WHITESPACE;

	// Checks for keywords and special characters
	for (int i = 0; i < sizeof(KEYWORDS); i++) {
		if (token == KEYWORDS[i]) return KEYWORD;
	}
	
	if (token == "=")
		return ASSIGN_OP;
	if (token == "(")
		return LPAREN;
	if (token == ")")
		return RPAREN;
	
	if (isnum(token)) return NUMBER;
	return IDENTIFIER;	
}

bool Token::isnum(char *token) {
	for (int i = 0; i < sizeof(token); i++) {
		if (!isdigit(token[i])) return false;
		return true;
	}
}
