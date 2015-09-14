#include "Statement/Token.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// DEFINITIONS
const static char *DATATYPE_BUFFER[] = { "void", "int", "bool"};
const char** Token::DATATYPES = DATATYPE_BUFFER;

const static char *CONTROL_BUFFER[] = { "if", "else", "while" };
const char** Token::CONTROLS = CONTROL_BUFFER;

const static char *ARTH_OPERATORS_BUFFER[] = { "=", "+", "-", "*", "/" };
const char** Token::ARTH_OPERATORS = ARTH_OPERATORS_BUFFER;

const static char *BOOL_OPERATORS_BUFFER[] = { "==", "!=", "<", ">", "<=", ">=" };
const char** Token::BOOL_OPERATORS = BOOL_OPERATORS_BUFFER;
//////////////

char *Token::getType() {
	switch (type) { 
	case WHITESPACE:
		return (char*) "WHITESPACE";
	case DATATYPE:
		return (char*) "DATATYPE";
	case CONTROL:
		return (char*) "CONTROL";
	case IDENTIFIER:
		return (char*) "IDENTIFIER";
	case NUMBER:
		return (char*) "NUMBER";
	case BOOL:
		return (char*) "BOOL";
	case ARTH_OPERATOR:
		return (char*) "ARTH_OPERATOR";
	case BOOL_OPERATOR:
		return (char*) "BOOL_OPERATOR";
	case PAREN:
		return (char*) "PAREN";
	case COMMA:
		return (char*) "COMMA";
	case RETURN:
		return (char*) "RETURN";
	}
}

void Token::determineSubtype() {
	switch (type) {
	case DATATYPE:
		for (int i = 0; i < NUM_DATATYPES; i++)
			if (StringUtil::equal(DATATYPES[i], token)) subtype = i;
		break;
	case CONTROL:
		for (int i = 0; i < NUM_CONTROLS; i++) 
			if (StringUtil::equal(CONTROLS[i], token)) subtype = i;
		break;
	case ARTH_OPERATOR:
		for (int i = 0; i < NUM_ARTH_OPERATORS; i++)
			if (StringUtil::equal(ARTH_OPERATORS[i], token)) subtype = i;
		break;
	case BOOL_OPERATOR:
		for (int i = 0; i < NUM_BOOL_OPERATORS; i++)
			if (StringUtil::equal(BOOL_OPERATORS[i], token)) subtype = i;
		break;
	case PAREN:	
		if (token[0] == '(') subtype = 0;
		if (token[0] == ')') subtype = 1;
		break;
	default:
		subtype = -1;
	}
}

Token::TOKEN_TYPE Token::identifyTokenType(const char *token) {
	if (iscomma(token[0])) return COMMA;
	if (iswhitespace(token[0])) return WHITESPACE;
	if (isdatatype(token)) return DATATYPE;
	if (iscontrol(token)) return CONTROL;
	if (isbooloperator(token)) return BOOL_OPERATOR;
	if (isarthoperator(token)) return ARTH_OPERATOR;
	if (token[0] == '(' || token[0] == ')') return PAREN;
	if (isnum(token)) return NUMBER;
	if (isbool(token)) return BOOL;
	if (isreturn(token)) return RETURN;
	return IDENTIFIER;	
}

bool Token::iscomma(char c) {
	return (c == ',');
}

bool Token::iswhitespace(char c) {
	return (c <= 32);
}

bool Token::isdatatype(const char *token) {
	for (int i = 0; i < NUM_DATATYPES; i++) {
		if (StringUtil::equal(DATATYPES[i], token)) return true;
	}
	return false;
}

bool Token::iscontrol(const char *token) {
	for (int i = 0; i < NUM_CONTROLS; i++) {
		if (StringUtil::equal(CONTROLS[i], token)) return true;
	}
	return false;
}

bool Token::isarthoperator(const char *token) {
	for (int i = 0; i < NUM_ARTH_OPERATORS; i++) {
		if (StringUtil::equal(ARTH_OPERATORS[i], token)) return true;
	}
	return false;
}

bool Token::isbooloperator(const char *token) {
	for (int i = 0; i < NUM_BOOL_OPERATORS; i++) {
		if (StringUtil::equal(BOOL_OPERATORS[i], token)) return true;
	}
	return false;
}

bool Token::isnum(const char *token) {
	for (int i = 0; i < sizeof(token); i++) {
		if (!isdigit(token[i])) return false;
		return true;
	}
}

bool Token::isbool(const char *token) {
	return (StringUtil::equal("true", token) || StringUtil::equal("false", token));
}

bool Token::isreturn(const char *token) {
	return (StringUtil::equal("return", token));
}
