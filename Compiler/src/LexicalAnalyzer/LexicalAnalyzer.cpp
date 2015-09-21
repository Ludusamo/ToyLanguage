#include "LexicalAnalyzer/LexicalAnalyzer.h"

std::vector<Token> LexicalAnalyzer::tokenize(const char *statement) {
	this->statement = StringUtil::copy(statement);
	tokens.clear();	
	char currTokenType = 0;
	char *buffer = (char*) malloc(sizeof(this->statement));
	int i = 0, currIndex = 0;

	while (i != strlen(this->statement)) {
		buffer[currIndex] = this->statement[i];	
		if (currTokenType == 0) {
			if (Token::iswhitespace(this->statement[i])) {
				currTokenType = WHITESPACE;
			} else if (isalnum(this->statement[i])) {
				currTokenType = STRING;
			} else {
				currTokenType = DELIM;
			}
		}	

		if (currTokenType == WHITESPACE) {
			if (!Token::iswhitespace(peekNextChar(i))) {
				buffer[currIndex + 1] = '\0';
				currTokenType = 0;
				currIndex = -1;
				memset(buffer, ' ', sizeof(buffer));
			}	
		} else if (currTokenType == STRING) {
			if (!isalnum(peekNextChar(i))) {
				buffer[currIndex + 1] = '\0';
				recordToken(buffer, Token::identifyTokenType(buffer));
				currTokenType = 0;
				currIndex = -1;
				memset(buffer, ' ', sizeof(buffer));
			}
		} else if (currTokenType == DELIM) {
			if (Token::iswhitespace(peekNextChar(i)) || isalnum(peekNextChar(i)) || peekNextChar(i) == '(' || peekNextChar(i) == ')') {
				buffer[currIndex + 1] = '\0';
				recordToken(buffer, Token::identifyTokenType(buffer));
				currTokenType = 0;
				currIndex = -1;
				memset(buffer, ' ', sizeof(buffer));
			}
		}

		i++;
		currIndex++;
	}
	return tokens;
}

char LexicalAnalyzer::peekNextChar(int currIndex) {
	return statement[currIndex + 1];
}

void LexicalAnalyzer::recordToken(const char *token, Token::TOKEN_TYPE type) {
	Token t;

	t.setToken(token);	
	t.setType(type);
	t.determineSubtype();

	printf("Token: %s\n", t.token);
	printf("Token Type: %s\n", t.getType());

	tokens.push_back(t);
}
