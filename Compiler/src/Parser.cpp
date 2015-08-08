#include "Parser.h"

#include <stdio.h>

bool Parser::parse(std::vector<Statement> &statements, Memory &mem) {
	parsingIndex++;
	if (parsingIndex == statements.size()) return true;
	statementIndex = -1;
	if (isDeclaration(statements[parsingIndex], mem)) {
		mem.createVariable(statements[parsingIndex].tokens[1].token, statements[parsingIndex].tokens[0].subtype);
		statements[parsingIndex].tagType(Statement::DECL);
		if (parse(statements, mem)) return true;
	}
	statementIndex = -1;
	if (isFunctionDeclaration(statements[parsingIndex], mem)) {
		mem.createFunction(statements[parsingIndex].tokens[1].token, argNumBuffer, statements[parsingIndex].tokens[0].subtype);
		if (parse(statements, mem)) return true;
	}
	statementIndex = -1;
	if (isIfStatement(statements[parsingIndex], mem)) {
		statements[parsingIndex].tagType(Statement::IF);
		if (parse(statements, mem)) return true;
	}
	return false;
}

bool Parser::isIfStatement(Statement &statement, Memory &mem) {
	if (isTokenType(statement, Token::CONTROL) 
		&& isSubtype(statement.tokens[statementIndex], Token::IF)) {
		if (isTokenType(statement, Token::PAREN) 
			&& isSubtype(statement.tokens[statementIndex], Token::LPAREN)) {
			if (isBoolValue(statement, mem)) {
				if (isTokenType(statement, Token::PAREN)
					&& isSubtype(statement.tokens[statementIndex], Token::RPAREN)) {
					return true;	
				}
			}
		}
	}
	return false;
}

bool Parser::isDeclaration(Statement &statement, Memory &mem) {
	int datatype = statement.tokens[0].subtype;
	if (isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER)) {
		if (isTokenType(statement, Token::ARTH_OPERATOR) 
				&& isSubtype(statement.tokens[statementIndex], (int) Token::ASSIGNMENT)) {
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

bool Parser::isFunctionDeclaration(Statement &statement, Memory &mem) {
	int datatype = statement.tokens[0].subtype;
	if (isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER)) {
		if (isTokenType(statement, Token::PAREN) && isSubtype(statement.tokens[statementIndex], (int) Token::LPAREN)) {
			bool hasArgs = isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER);
			argNumBuffer = hasArgs ? 1 : 0;
			while (hasArgs) {
				hasArgs = false;
				if (isTokenType(statement, Token::COMMA)) {
					if (isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER)) {
						argNumBuffer++;
						hasArgs = true;
					} 
				}
			}
			if (isTokenType(statement, Token::PAREN) && isSubtype(statement.tokens[statementIndex], (int) Token::RPAREN)) return true;
		}
	}
	return false;
}

bool Parser::isFunctionCall(Statement &statement, Memory &mem) {
	if (isTokenType(statement, Token::IDENTIFIER) 
		&& functionExists(statement.tokens[statementIndex].token, mem)) {
		if (isTokenType(statement, Token::PAREN) && isSubtype(statement.tokens[statementIndex], (int) Token::LPAREN)) {
			
		}
	}
}

bool Parser::isTokenType(Statement &statement, Token::TOKEN_TYPE type) {
	if (statementIndex + 1 == statement.tokens.size()) return false;
	statementIndex++;
	if (statement.tokens[statementIndex].type == type) return true;
	statementIndex--;
	return false;
}

bool Parser::isSubtype(Token token, int subtype) {
	return token.subtype == subtype;
}

bool Parser::variableExists(const char *id, Memory &mem) {
	int varIndex = mem.getVariable(id); 
	if (varIndex == -1) {
		ErrorHandler::throwError(parsingIndex, ErrorHandler::UndeclaredVariable);
		return false;
	}
	return true;
}

bool Parser::functionExists(const char *id, Memory &mem) {
	int functionIndex = mem.getFunction(id); 
	if (functionIndex == -1) {
		ErrorHandler::throwError(parsingIndex, ErrorHandler::UndeclaredFunction);
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
	   	(isTokenType(statement, Token::IDENTIFIER) 
		&& variableExists(statement.tokens[statementIndex].token, mem)
		&& isVariableType(statement.tokens[statementIndex].token, Token::INT, mem))) {
		if (isTokenType(statement, Token::ARTH_OPERATOR)) {
			if (isIntValue(statement, mem)) return true;
			else return false;
		} 
		return true;
	}

	//(VALUE)
	if (isTokenType(statement, Token::PAREN) 
		&& isSubtype(statement.tokens[statementIndex], (int) Token::LPAREN)) {
		if (isIntValue(statement, mem)) {
			if (isTokenType(statement, Token::PAREN)
				&& isSubtype(statement.tokens[statementIndex], (int) Token::RPAREN)) {
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
		&& isSubtype(statement.tokens[statementIndex], (int) Token::LPAREN)) {
		if (isBoolValue(statement, mem)) {
			if (isTokenType(statement, Token::PAREN)
				&& isSubtype(statement.tokens[statementIndex], (int) Token::RPAREN)) {
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

