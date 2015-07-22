#include "Parser.h"

#include <stdio.h>

std::vector<int> Parser::parse(Statement &statement) {
	if (isDeclaration(statement)) {
		printf("Is Declaration\n");
	} else printf("Is not Declaration\n");
	if (isIfStatement(statement)) {
		printf("Is If Statement\n");	
	} else printf("Is not if statement\n");
	return bytecode;
}

bool Parser::isIfStatement(Statement &statement) {
	statementIndex = -1;
	if (isTokenType(statement, Token::CONTROL) 
		&& isSubtype(statement.getToken(statementIndex), Token::IF)) {
		if (isTokenType(statement, Token::PAREN) 
			&& isSubtype(statement.getToken(statementIndex), Token::LPAREN)) {
			if (isBoolValue(statement)) {
				if (isTokenType(statement, Token::PAREN)
					&& isSubtype(statement.getToken(statementIndex), Token::RPAREN)) {
					return true;	
				}
			}
		}
	}
	return false;
}

bool Parser::isDeclaration(Statement &statement) {
	statementIndex = -1;
	int datatype = statement.getToken(0).subtype;
	if (isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER)) {
		if (isTokenType(statement, Token::ARTH_OPERATOR) 
				&& isSubtype(statement.getToken(statementIndex), (int) Token::ASSIGNMENT)) {
			switch(datatype) {
			case Token::INT:
				if (isIntValue(statement)) return true;
				break;
			case Token::BOOLEAN:
				if (isBoolValue(statement)) return true;
				break;
			}
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

bool Parser::isIntValue(Statement &statement) {
	//VALUE
	if (isTokenType(statement, Token::NUMBER)) {
		if (isTokenType(statement, Token::ARTH_OPERATOR)) {
			if (isIntValue(statement)) return true;
			else return false;
		} 
		return true;
	}

	//(VALUE)
	if (isTokenType(statement, Token::PAREN) 
		&& isSubtype(statement.getToken(statementIndex), (int) Token::LPAREN)) {
		if (isIntValue(statement)) {
			if (isTokenType(statement, Token::PAREN)
				&& isSubtype(statement.getToken(statementIndex), (int) Token::RPAREN)) {
				if (isTokenType(statement, Token::ARTH_OPERATOR)) {
					if (isIntValue(statement)) return true;
					else return false;
				}
				return true;
			}
		}
	}

	return false;
}

bool Parser::isBoolValue(Statement &statement) {
	//VALUE
	if (isIntValue(statement)) {
		if (isTokenType(statement, Token::BOOL_OPERATOR)) {
			if (isIntValue(statement)) return true;
			return false;
		}
		return true;
	}

	if (isTokenType(statement, Token::BOOL)) {
		if (isTokenType(statement, Token::BOOL_OPERATOR)) {
			if (isBoolValue(statement)) return true;
			else return false;
		} 
		return true;
	}

	//(VALUE)
	if (isTokenType(statement, Token::PAREN) 
		&& isSubtype(statement.getToken(statementIndex), (int) Token::LPAREN)) {
		if (isBoolValue(statement)) {
			if (isTokenType(statement, Token::PAREN)
				&& isSubtype(statement.getToken(statementIndex), (int) Token::RPAREN)) {
				if (isTokenType(statement, Token::BOOL_OPERATOR)) {
					if (isBoolValue(statement)) return true;
					else return false;
				}
				return true;
			}
		}
	}

	return false;
}

bool Parser::endOfStatement(Statement &statement) {
	return (statement.tokens.size() == statementIndex + 1);	
}

