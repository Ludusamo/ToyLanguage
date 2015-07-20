#include "Parser.h"

#include <stdio.h>

std::vector<int> Parser::parse(Statement &statement) {
	if (isDeclaration(statement)) {
		printf("TRUE\n");
	} else printf("FALSE\n");
	return bytecode;
}

bool Parser::isDeclaration(Statement &statement) {
	statementIndex = -1;
	if (isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER)) {
		if (isTokenType(statement, Token::OPERATOR) 
				&& isSubtype(statement.getToken(statementIndex), (int) Token::ASSIGNMENT)) {
			if (isValue(statement)) return true;
		} else if (endOfStatement(statement)) {
			return true;
		}
	}
	return false;
}

bool Parser::isTokenType(Statement &statement, Token::TOKEN_TYPE type) {
	statementIndex++;
	if (statement.getToken(statementIndex).type == type) return true;
	statementIndex--;
	return false;
}

bool Parser::isSubtype(Token token, int subtype) {
	return token.subtype == subtype;
}

bool Parser::isValue(Statement &statement) {
	//VALUE
	if (isTokenType(statement, Token::NUMBER)) {
		if (isTokenType(statement, Token::OPERATOR)) {
			if (isValue(statement)) return true;
		} 
		return true;
	}

	//(VALUE)
	if (isTokenType(statement, Token::PAREN) 
		&& isSubtype(statement.getToken(statementIndex), (int) Token::LPAREN)) {
		if (isValue(statement)) {
			if (isTokenType(statement, Token::PAREN)
				&& isSubtype(statement.getToken(statementIndex), (int) Token::RPAREN)) {
				return true;
			}
		}
	}

	return false;
}

bool Parser::endOfStatement(Statement &statement) {
	return (statement.tokens.size() == statementIndex + 1);	
}

