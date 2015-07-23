#include "Parser.h"

#include <stdio.h>

std::vector<int> Parser::parse(Statement &statement, Memory &mem) {
	if (isDeclaration(statement, mem)) {
		printf("Is Declaration\n");
	} else printf("Is not Declaration\n");
	if (isIfStatement(statement, mem)) {
		printf("Is If Statement\n");	
	} else printf("Is not if statement\n");
	return bytecode;
}

bool Parser::isIfStatement(Statement &statement, Memory &mem) {
	statementIndex = -1;
	if (isTokenType(statement, Token::CONTROL) 
		&& isSubtype(statement.getToken(statementIndex), Token::IF)) {
		if (isTokenType(statement, Token::PAREN) 
			&& isSubtype(statement.getToken(statementIndex), Token::LPAREN)) {
			if (isBoolValue(statement, mem)) {
				if (isTokenType(statement, Token::PAREN)
					&& isSubtype(statement.getToken(statementIndex), Token::RPAREN)) {
					return true;	
				}
			}
		}
	}
	return false;
}

bool Parser::isDeclaration(Statement &statement, Memory &mem) {
	statementIndex = -1;
	int datatype = statement.getToken(0).subtype;
	if (isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER)) {
		if (isTokenType(statement, Token::ARTH_OPERATOR) 
				&& isSubtype(statement.getToken(statementIndex), (int) Token::ASSIGNMENT)) {
			switch(datatype) {
			case Token::INT:
				if (isIntValue(statement, mem)) return true;
				break;
			case Token::BOOLEAN:
				if (isBoolValue(statement, mem)) return true;
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

bool Parser::variableExists(const char *id, Memory &mem) {
	int varIndex = mem.getVariable(id); 
	if (varIndex == -1) {
		ErrorHandler::throwError(0, 0);
		return false;
	}
	return true;
}

bool Parser::isVariableType(const char *id, int type, Memory &mem) {
	return (mem.variables[mem.getVariable(id)].type == type);
}

bool Parser::isIntValue(Statement &statement, Memory &mem) {
	//VALUE
	if (isTokenType(statement, Token::NUMBER) ||
		isTokenType(statement, Token::IDENTIFIER) 
		&& variableExists(statement.getToken(statementIndex).token, mem)
		&& isVariableType(statement.getToken(statementIndex).token, Token::INT, mem)) {
		if (isTokenType(statement, Token::ARTH_OPERATOR)) {
			if (isIntValue(statement, mem)) return true;
			else return false;
		} 
		return true;
	}

	//(VALUE)
	if (isTokenType(statement, Token::PAREN) 
		&& isSubtype(statement.getToken(statementIndex), (int) Token::LPAREN)) {
		if (isIntValue(statement, mem)) {
			if (isTokenType(statement, Token::PAREN)
				&& isSubtype(statement.getToken(statementIndex), (int) Token::RPAREN)) {
				if (isTokenType(statement, Token::ARTH_OPERATOR)) {
					if (isIntValue(statement, mem)) return true;
					else return false;
				}
				return true;
			}
		}
	}

	return false;
}

bool Parser::isBoolValue(Statement &statement, Memory &mem) {
	//VALUE
	if (isIntValue(statement, mem)) {
		if (isTokenType(statement, Token::BOOL_OPERATOR)) {
			if (isIntValue(statement, mem)) return true;
			return false;
		}
		return true;
	}

	if (isTokenType(statement, Token::BOOL)) {
		if (isTokenType(statement, Token::BOOL_OPERATOR)) {
			if (isBoolValue(statement, mem)) return true;
			else return false;
		} 
		return true;
	}

	//(VALUE)
	if (isTokenType(statement, Token::PAREN) 
		&& isSubtype(statement.getToken(statementIndex), (int) Token::LPAREN)) {
		if (isBoolValue(statement, mem)) {
			if (isTokenType(statement, Token::PAREN)
				&& isSubtype(statement.getToken(statementIndex), (int) Token::RPAREN)) {
				if (isTokenType(statement, Token::BOOL_OPERATOR)) {
					if (isBoolValue(statement, mem)) return true;
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

