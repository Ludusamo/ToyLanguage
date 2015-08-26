#include "Statement.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void Statement::tokenizeStatement() {
	depth = calculateDepth();
	char currTokenType = 0;
	char *buffer = (char*) malloc(sizeof(statement));
	int i = 0, currIndex = 0;

	while (i != strlen(statement)) {
		buffer[currIndex] = statement[i];	
		if (currTokenType == 0) { // If no flags are set
			if (Token::iswhitespace(statement[i])) {
				currTokenType = WHITESPACE;
			} else if (isalnum(statement[i])) {
				currTokenType = STRING;
			} else {
				currTokenType = DELIM;
			}
		}	

		if (currTokenType == WHITESPACE) { // WHITESPACE
			if (!Token::iswhitespace(peekNextChar(i))) {
				buffer[currIndex + 1] = '\0'; // Terminates the string
				// Not sure if I want to record whitespace tokens
				//recordToken(buffer, Token::WHITESPACE);
				currTokenType = 0;
				currIndex = -1;
				memset(buffer, ' ', sizeof(buffer));
			}	
		} else if (currTokenType == STRING) { // STRINGS
			if (!isalnum(peekNextChar(i))) {
				buffer[currIndex + 1] = '\0'; // Terminates the string
				recordToken(buffer, Token::identifyTokenType(buffer));
				currTokenType = 0;
				currIndex = -1;
				memset(buffer, ' ', sizeof(buffer));
			}
		} else if (currTokenType == DELIM) { // DELIMINATORS
			if (Token::iswhitespace(peekNextChar(i)) || isalnum(peekNextChar(i)) || peekNextChar(i) == '(' || peekNextChar(i) == ')') {
				buffer[currIndex + 1] = '\0'; // Terminates the string
				recordToken(buffer, Token::identifyTokenType(buffer));
				currTokenType = 0;
				currIndex = -1;
				memset(buffer, ' ', sizeof(buffer));
			}
		}

		i++;
		currIndex++;
	}
}

int Statement::calculateDepth() {
	int count = 0;
	for (int i = 0; i < strlen(statement); i++) {
		if (!Token::iswhitespace(statement[i])) break;
		count++;		
	}	
	return count;
}

char Statement::peekNextChar(int currIndex) {
	return statement[currIndex + 1];
}

void Statement::recordToken(const char *token, Token::TOKEN_TYPE type) {
	Token t;

	t.setToken(token);
	t.setType(type);
	t.determineSubtype();

	printf("Token: %s\n", t.token);
	printf("Token Type: %s\n", t.getType());

	tokens.push_back(t);
}
