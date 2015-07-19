#include "Token.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "StringUtil.h"

// DEFINITIONS
const static char *DATATYPE_BUFFER[] = { "int" };
const char** Token::DATATYPES = DATATYPE_BUFFER;

const static char *KEYWORD_BUFFER[] = { "if", "else" };
const char** Token::KEYWORDS = KEYWORD_BUFFER;

const static char *OPERATORS_BUFFER[] = { "=", "+", "-", "*", "/", "==", "!=" "<", ">", "<=", ">=" };
const char** Token::OPERATORS = OPERATORS_BUFFER;
//////////////

char *Token::getType() {
	switch (type) {
	case WHITESPACE:
		return (char*) "WHITESPACE";
	case DATATYPE:
		return (char*) "DATATYPE";
	case KEYWORD:
		return (char*) "KEYWORD";
	case IDENTIFIER:
		return (char*) "IDENTIFIER";
	case NUMBER:
		return (char*) "NUMBER";
	case OPERATOR:
		return (char*) "OPERATOR";
	case PAREN:
		return (char*) "PAREN";
	}
}

void Token::determineSubtype() {
	switch (type) {
	case DATATYPE:
		for (int i = 0; i < NUM_DATATYPES; i++)
			if (StringUtil::equal(DATATYPES[i], token)) subtype = i;
		break;
	case KEYWORD:
		for (int i = 0; i < NUM_KEYWORDS; i++) 
			if (StringUtil::equal(KEYWORDS[i], token)) subtype = i;
		break;
	case OPERATOR:
		for (int i = 0; i < NUM_OPERATORS; i++)
			if (StringUtil::equal(OPERATORS[i], token)) subtype = i;
		break;
	case PAREN:	
		if (token[0] == '(') subtype = 0;
		if (token[0] == ')') subtype = 1;
		break;
	default:
		subtype = -1;
	}
}

Token::TOKEN_TYPE Token::identifyTokenType(char *token) {
	if (iswhitespace(token[0])) return WHITESPACE;
	if (isdatatype(token)) return DATATYPE;
	if (iskeyword(token)) return KEYWORD;
	if (isoperator(token)) return OPERATOR;
	if (token[0] == '(' || token[0] == ')') return PAREN;
	if (isnum(token)) return NUMBER;
	return IDENTIFIER;	
}

bool Token::iswhitespace(char c) {
	return (c == ' ') || (c == '\t') || (c == '\n');
}

bool Token::isdatatype(char *token) {
	for (int i = 0; i < NUM_DATATYPES; i++) {
		if (StringUtil::equal(DATATYPES[i], token)) return true;
	}
	return false;
}

bool Token::iskeyword(char *token) {
	for (int i = 0; i < NUM_KEYWORDS; i++) {
		if (StringUtil::equal(KEYWORDS[i], token)) return true;
	}
	return false;
}

bool Token::isoperator(char *token) {
	for (int i = 0; i < NUM_OPERATORS; i++) {
		if (StringUtil::equal(OPERATORS[i], token)) return true;
	}
	return false;
}

bool Token::isnum(char *token) {
	for (int i = 0; i < sizeof(token); i++) {
		if (!isdigit(token[i])) return false;
		return true;
	}
}
