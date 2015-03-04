#include "Token.h"

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
		break;
	case KEYWORD:
		return (char*) "KEYWORD";
		break;
	case IDENTIFIER:
		return (char*) "IDENTIFIER";
		break;
	case NUMBER:
		return (char*) "NUMBER";
		break;
	case ASSIGN_OP:
		return (char*) "ASSIGNMENT OPERATOR";
		break;
	case LPAREN:
		return (char*) "LEFT PARENTHESIS";
		break;
	case RPAREN:
		return (char*) "RIGHT PARENTHESIS";
		break;
	}
}
