#include "Statement.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "BitUtil.h"

void Statement::setStatement(char *statement) {
	this->statement = statement;
}

void Statement::tokenizeStatement() {
	depth = calculateDepth();
	char currTokenType = 0;
	char *buffer = (char*) malloc(sizeof(statement));
	int i = 0, currIndex = 0;
					
	while (i != strlen(statement)) {
		buffer[currIndex] = statement[i];	
		if (currTokenType == 0) { // If no flags are set
			if (iswhitespace(statement[i])) {
				BitUtil::turnOnBit(currTokenType, WHITESPACE_FLAG);
			} else if (isalnum(statement[i])) {
				BitUtil::turnOnBit(currTokenType, STRING_FLAG);
			} else {
				BitUtil::turnOnBit(currTokenType, DELIM_FLAG);
			}
		}	

		if (BitUtil::checkBit(currTokenType, WHITESPACE_FLAG)) {
			if (!iswhitespace(peekNextChar(i))) {
				buffer[currIndex + 1] = '\0'; // Terminates the string
				recordToken(buffer, Token::WHITESPACE);
				currTokenType = 0;
				currIndex = -1;
				memset(buffer, ' ', sizeof(buffer));
			}	
		} else if (BitUtil::checkBit(currTokenType, STRING_FLAG)) {
			if (!isalnum(peekNextChar(i))) {
				buffer[currIndex + 1] = '\0'; // Terminates the string
				recordToken(buffer, Token::identifyTokenType(buffer));
				currTokenType = 0;
				currIndex = -1;
				memset(buffer, ' ', sizeof(buffer));
			}
		} else if (BitUtil::checkBit(currTokenType, DELIM_FLAG)) {
			if (iswhitespace(peekNextChar(i)) || isalnum(peekNextChar(i))) {
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
		if (!iswhitespace(statement[i])) break;
		count++;		
	}	
	return count;
}

char Statement::peekNextChar(int currIndex) {
	return statement[currIndex + 1];
}

void Statement::recordToken(char *token, Token::TOKEN_TYPE type) {
	Token t;
	t.setToken(token);
	t.setType(type);

	printf("Token: %s\n", token);

	tokens.push_back(t);
}

bool Statement::iswhitespace(char c) {
	return (c == ' ') || (c == '\t') || (c == '\n');
}
