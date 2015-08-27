#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Token.h"

#define WHITESPACE 0
#define STRING 1
#define	DELIM 2

class LexicalAnalyzer {
public:
	LexicalAnalyzer(){};
	~LexicalAnalyzer(){};
	std::vector<Token> tokenize(const char *statement);
private:
	const char *statement;
	std::vector<Token> tokens;
	int calculateDepth();
	char peekNextChar(int currIndex);
	void recordToken(const char *token, Token::TOKEN_TYPE type);
};

#endif // LEXICALANALYZER_H
