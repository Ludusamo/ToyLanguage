#include "Parser.h"

#include <stdio.h>

bool Parser::parse(std::vector<Statement> &statements) {
	parsingIndex++;
	if (parsingIndex == statements.size()) return true;
	currentDepth = statements[parsingIndex].depth;

	mem.popVariableLayers(currentDepth, statements[parsingIndex - 1].depth);

	statementIndex = -1;
	if (isDeclaration(statements[parsingIndex])) {
		mem.createVariable(statements[parsingIndex].tokens[1].token, statements[parsingIndex].tokens[0].subtype, currentDepth);
		statements[parsingIndex].tagType(Statement::DECL);
	}
	statementIndex = -1;
	if (isFunctionDeclaration(statements[parsingIndex])) {
		int index = parsingIndex;
		statements[parsingIndex].tagType(Statement::FUNC);
		while (statements[parsingIndex + 1].depth >= currentDepth) {
			parsingIndex++;
			currentDepth = statements[parsingIndex].depth;;
			statementIndex = -1;
			if (isDeclaration(statements[parsingIndex])) {
				mem.createVariable(statements[parsingIndex].tokens[1].token, statements[parsingIndex].tokens[0].subtype, currentDepth);
				statements[parsingIndex].tagType(Statement::DECL);
			}
			statementIndex = -1;
			if (isIfStatement(statements[parsingIndex])) {
				statements[parsingIndex].tagType(Statement::IF);
			}
			statementIndex = -1;
			if (isReturnStatement(statements[parsingIndex], statements[index].tokens[0].subtype)) {
				statements[parsingIndex].tagType(Statement::RET);
			}
		}
		mem.returnVariables(statements[index].tokens[1].token);
	}
	statementIndex = -1;
	if (isFunctionCall(statements[parsingIndex])) {
		statements[parsingIndex].tagType(Statement::FUNC_CALL);
	}
	statementIndex = -1;
	if (isIfStatement(statements[parsingIndex])) {
		statements[parsingIndex].tagType(Statement::IF);
	}
	if (parse(statements)) return true;
	return false;
}

bool Parser::isIfStatement(Statement &statement) {
	if (isTokenType(statement, Token::CONTROL) 
		&& isSubtype(statement.tokens[statementIndex], Token::IF)) {
		if (isTokenType(statement, Token::PAREN) 
			&& isSubtype(statement.tokens[statementIndex], Token::LPAREN)) {
			if (isBoolValue(statement)) {
				if (isTokenType(statement, Token::PAREN)
					&& isSubtype(statement.tokens[statementIndex], Token::RPAREN)) {
					return true;	
				}
			}
		}
	}
	return false;
}

bool Parser::isDeclaration(Statement &statement) {
	int datatype = statement.tokens[0].subtype;
	if (isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER)) {
		if (isTokenType(statement, Token::ARTH_OPERATOR) 
				&& isSubtype(statement.tokens[statementIndex], (int) Token::ASSIGNMENT)) {
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

bool Parser::isFunctionDeclaration(Statement &statement) {
	Memory::Function f;
	f.id = statement.tokens[1].token;
	f.returnType = statement.tokens[0].subtype;
	f.numArgs = 0;
	if (isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER)) {
		if (isTokenType(statement, Token::PAREN) && isSubtype(statement.tokens[statementIndex], (int) Token::LPAREN)) {
			bool hasArgs = isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER);
			if (hasArgs) {
				mem.addArgument(f, statement.tokens[4].token, statement.tokens[3].subtype);
			}
			while (hasArgs) {
				hasArgs = false;
				if (isTokenType(statement, Token::COMMA)) {
					if (isTokenType(statement, Token::DATATYPE) && isTokenType(statement, Token::IDENTIFIER)) {
						mem.addArgument(f, statement.tokens[statementIndex].token, statement.tokens[statementIndex - 1].subtype);

						hasArgs = true;
					} 
				}
			}
			if (isTokenType(statement, Token::PAREN) && isSubtype(statement.tokens[statementIndex], (int) Token::RPAREN)) {
				mem.addGlobalFunction(f);
				return true;
			}
		}
	}
	return false;
}	

bool Parser::isReturnStatement(Statement &statement, int returnType) {
	if (isTokenType(statement, Token::RETURN)) {
		if (returnType == Token::VOID) {
			if (statement.tokens.size() == 1) return true;
		} else if (returnType == Token::INT) {
			if (isIntValue(statement)) return true;
		} else if (returnType == Token::BOOLEAN) {
			if (isBoolValue(statement)) return true;
		}
		ErrorHandler::throwError(parsingIndex + 1, ErrorHandler::InvalidReturnValue);
	}	
	return false;
}

bool Parser::isFunctionCall(Statement &statement) {
	if (isTokenType(statement, Token::IDENTIFIER) 
		&& functionExists(statement.tokens[statementIndex].token)) {
		if (isTokenType(statement, Token::PAREN) && isSubtype(statement.tokens[statementIndex], (int) Token::LPAREN)) {
			Memory::Function f = mem.globalFunctions[mem.getFunction(statement.tokens[0].token)];
			printf("%s %i %i\n", f.id, f.argTypes[1], f.numArgs);
			for (int i = 0; i < f.numArgs; i++) {
				printf("Argument number: %i\n", i);
				if (f.argTypes[i] == Token::INT) {
					printf("Arg: %i\n", statementIndex);
					if (!isIntValue(statement)) {
						printf("Not an int value\n");
						return false;
					}
				} else if (f.argTypes[i] == Token::BOOLEAN) {
					printf("Arg: %i\n", statementIndex);
					if (!isBoolValue(statement)) {
						printf("Not an bool value\n");
						return false;
					}
				}
				printf("Statement Index: %i\n", statementIndex);
				if (!isTokenType(statement, Token::COMMA) && (i != f.numArgs - 1)){
				       	return false;
				}
			}
			if (isTokenType(statement, Token::PAREN) && isSubtype(statement.tokens[statementIndex], (int) Token::RPAREN)) return true;
		}
	}
	return false;
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

bool Parser::variableExists(const char *id) {
	int varIndex = mem.getVariable(id, currentDepth); 
	if (varIndex != -1) return true;		
	ErrorHandler::throwError(parsingIndex + 1, ErrorHandler::UndeclaredVariable);
	return false;
}

bool Parser::functionExists(const char *id) {
	int functionIndex = mem.getFunction(id); 
	if (functionIndex == -1) {
		ErrorHandler::throwError(parsingIndex, ErrorHandler::UndeclaredFunction);
		return false;
	}
	return true;
}

bool Parser::isVariableType(const char *id, int type) {
	statementIndex--;
	return (mem.getVariableType(id, currentDepth) == type);
}

bool Parser::isIntValue(Statement &statement) {
	//VALUE
	if (isTokenType(statement, Token::NUMBER) ||
	   	(isTokenType(statement, Token::IDENTIFIER) 
		&& variableExists(statement.tokens[statementIndex].token)
		&& isVariableType(statement.tokens[statementIndex].token, Token::INT))) {
		if (isTokenType(statement, Token::ARTH_OPERATOR)) {
			if (isIntValue(statement)) return true;
			else return false;
		} 
		return true;
	}

	//(VALUE)
	if (isTokenType(statement, Token::PAREN) 
		&& isSubtype(statement.tokens[statementIndex], (int) Token::LPAREN)) {
		if (isIntValue(statement)) {
			if (isTokenType(statement, Token::PAREN)
				&& isSubtype(statement.tokens[statementIndex], (int) Token::RPAREN)) {
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

	if (isTokenType(statement, Token::BOOL) ||
	   	(isTokenType(statement, Token::IDENTIFIER) 
		&& variableExists(statement.tokens[statementIndex].token)
		&& isVariableType(statement.tokens[statementIndex].token, Token::BOOLEAN))) {
		if (isTokenType(statement, Token::BOOL_OPERATOR)) {
			if (isBoolValue(statement)) return true;
			else return false;
		} 
		return true;
	}

	//(VALUE)
	if (isTokenType(statement, Token::PAREN) 
		&& isSubtype(statement.tokens[statementIndex], (int) Token::LPAREN)) {
		if (isBoolValue(statement)) {
			if (isTokenType(statement, Token::PAREN)
				&& isSubtype(statement.tokens[statementIndex], (int) Token::RPAREN)) {
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

