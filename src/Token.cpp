#include "Token.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// DEFINITIONS
const static char *KEYWORD_BUFFER[] = { "if", "else", "int" };
const char** Token::KEYWORDS = KEYWORD_BUFFER;
const int Token::numKeywords = 3;

const static char *OPERATORS_BUFFER[] = { "=", "==", "<", ">", "<=", ">=", "+", "-", "*", "/" };
const char** Token::OPERATORS = OPERATORS_BUFFER;
const int Token::numOperators = 10;

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
	case OPERATOR:
		return (char*) "OPERATOR";
	case PAREN:
		return (char*) "PAREN";
	}
}

Token::TOKEN_TYPE Token::identifyTokenType(char *token) {
	if (iswhitespace(token[0])) return WHITESPACE;
	if (iskeyword(token)) return KEYWORD;
	if (isoperator(token)) return OPERATOR;
	if (token[0] == '(' || token[0] == ')') return PAREN;
	if (isnum(token)) return NUMBER;
	return IDENTIFIER;	
}

bool Token::iswhitespace(char c) {
	return (c == ' ') || (c == '\t') || (c == '\n');
}

bool Token::iskeyword(char *token) {
	for (int i = 0; i < numKeywords; i++) {
		for (int j = 0; j < strlen(KEYWORDS[i]); j++) {
			if (KEYWORDS[i][j] != token[j]) {
				break;
			}
			if (j == strlen(KEYWORDS[i]) - 1) {
				return true;
			}
		}
	}
	return false;
}

bool Token::isoperator(char *token) {
	for (int i = 0; i < numOperators; i++) {
		for (int j = 0; j < strlen(OPERATORS[i]); j++) {
			if (OPERATORS[i][j] != token[j]) {
				break;
			}
			if (j == strlen(OPERATORS[i]) - 1) {
				return true;
			}
		}
	}
	return false;
}

bool Token::isnum(char *token) {
	for (int i = 0; i < sizeof(token); i++) {
		if (!isdigit(token[i])) return false;
		return true;
	}
}
