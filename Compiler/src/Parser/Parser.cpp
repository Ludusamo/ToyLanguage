#include "Parser/Parser.h"

bool Parser::parse(std::vector<Statement> &statements) {
	if (parsingIndex == statements.size() - 1 || currentDepth > statements[parsingIndex + 1].depth) {
		printf("hi\n");
		currentDepth = statements[parsingIndex + 1].depth;
		return true;
	}
	parsingIndex++;
	previousDepth = currentDepth;
	currentDepth = statements[parsingIndex].depth;
	statementIndex = -1;

	mem.popVariableLayers(currentDepth, previousDepth);

	if (endOfStatement(statements[parsingIndex])) {
		printf("Blank line\n");
		statements[parsingIndex].tagType(Statement::NONE);	
	} else if (isDeclaration(statements[parsingIndex])) {
		printf("Is declaration\n");
		mem.createVariable(statements[parsingIndex].tokens[1].token, statements[parsingIndex].tokens[0].subtype, currentDepth);
		statements[parsingIndex].tagType(Statement::DECL);
	} else if (isAssignment(statements[parsingIndex])) {
		printf("Is assignment\n");
		statements[parsingIndex].tagType(Statement::ASSIGN);
	} else if (isFunctionDeclaration(statements[parsingIndex])) {
		printf("Is function\n");
		statements[parsingIndex].tagType(Statement::FUNC);
		bufferIndex = parsingIndex;
		if (parse(statements))
			mem.returnVariables(statements[bufferIndex].tokens[1].token);
	} else if (isFunctionCall(statements[parsingIndex])) {
		printf("Is function call\n");
		statements[parsingIndex].tagType(Statement::FUNC_CALL);
	} else if (isIfStatement(statements[parsingIndex])) {
		printf("Is if\n");
		statements[parsingIndex].tagType(Statement::IF);
		parse(statements);
		if (isElseStatement(statements[parsingIndex + 1])) {
			parsingIndex++;
			currentDepth = statements[parsingIndex].depth;
			statements[parsingIndex].tagType(Statement::ELSE);
			parse(statements);
		}
	} else if (isWhileStatement(statements[parsingIndex])) {
		printf("is while.\n");
		statements[parsingIndex].tagType(Statement::WHILE);	
		parse(statements);	
	} else if (isReturnStatement(statements[parsingIndex], statements[bufferIndex].tokens[0].subtype)) {
		printf("Is return\n");
		statements[parsingIndex].tagType(Statement::RET);
		printf("is return statement\n");
	}
	if (parse(statements)) return true;
	return false;
}

bool Parser::isIfStatement(Statement &statement) {
	statementIndex = -1;
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

bool Parser::isElseStatement(Statement &statement) {
	statementIndex = -1;
	if (isTokenType(statement, Token::CONTROL) 
		&& isSubtype(statement.tokens[statementIndex], Token::ELSE)) {
		return true;	
	}
	return false;
}

bool Parser::isWhileStatement(Statement &statement) {
	statementIndex = -1;
	if (isTokenType(statement, Token::CONTROL) 
		&& isSubtype(statement.tokens[statementIndex], Token::WHILE)) {
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
	statementIndex = -1;
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
			case Token::CHAR:
				if (isCharValue(statement)) return true;
				break;
			}
		} else if (endOfStatement(statement)) {
			return true;
		}
	}
	return false;
}

bool Parser::isAssignment(Statement &statement) {
	statementIndex = -1;
	if (isTokenType(statement, Token::IDENTIFIER) 
		&& variableExists(statement.tokens[statementIndex].token)) {
		if (isTokenType(statement, Token::ARTH_OPERATOR) 
			&& isSubtype(statement.tokens[statementIndex], (int) Token::ASSIGNMENT)) {

			int varType = mem.getVariableType(statement.tokens[0].token, currentDepth);
			if (varType == Token::INT) {
				if (isIntValue(statement)) return true;
			}
			if (varType == Token::BOOLEAN) {
				if (isBoolValue(statement)) return true;
			}
		}
	}
	return false;

}

bool Parser::isFunctionDeclaration(Statement &statement) {
	statementIndex = -1;
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
	statementIndex = -1;
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
			Memory::Function f = mem.globalFunctions[mem.getFunction(statement.tokens[statementIndex - 1].token)];
			for (int i = 0; i < f.numArgs; i++) {
				if (f.argTypes[i] == Token::INT) {
					if (!isIntValue(statement)) {
						return false;
					}
				} else if (f.argTypes[i] == Token::BOOLEAN) {
					if (!isBoolValue(statement)) {
						return false;
					}
				}
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
	if (statement.tokens[statementIndex].type == type) {
		return true;
	}
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
	printf("%s\n", id);
	int functionIndex = mem.getFunction(id); 
	if (functionIndex == -1) {
		return false;
	}
	return true;
}

bool Parser::isVariableType(const char *id, int type) {
	printf("%s %i\n", id, type);
	return (mem.getVariableType(id, currentDepth) == type);
}

bool Parser::isIntValue(Statement &statement) {
	int bufferIndex = statementIndex;
	printf("Int: %i\n", statementIndex);
	statementIndex -= 2;
	if (isFunctionCall(statement)) {
		statementIndex -= 2;
		if (mem.globalFunctions[mem.getFunction(statement.tokens[statementIndex].token)].returnType == Token::INT) {
			statementIndex = bufferIndex;
			if (isTokenType(statement, Token::ARTH_OPERATOR)) {
				if (isIntValue(statement)) return true;
				else return false;
			}
			return true;
		}
	}
	statementIndex = bufferIndex;

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
	int bufferIndex = statementIndex;
	printf("Bool: %i\n", statementIndex);
	if (isFunctionCall(statement)) {
		if (mem.globalFunctions[mem.getFunction(statement.tokens[statementIndex].token)].returnType == Token::BOOLEAN) {
			statementIndex = bufferIndex;
			if (isTokenType(statement, Token::BOOL_OPERATOR)) {
				if (isBoolValue(statement)) return true;
				else return false;
			}
			return true;
		}
	}
	statementIndex = bufferIndex;

	//VALUE
	if (isIntValue(statement)) {
		if (isTokenType(statement, Token::BOOL_OPERATOR)) {
			if (isIntValue(statement)) return true;
			return false;
		}
		return true;
	}
	statementIndex = bufferIndex;

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

bool Parser::isCharValue(Statement &statement) {
	statementIndex -= 2;
	if (isFunctionCall(statement)) {
		statementIndex -= 2;
		if (mem.globalFunctions[mem.getFunction(statement.tokens[statementIndex].token)].returnType == Token::CHAR) {
			statementIndex = bufferIndex;
			if (isTokenType(statement, Token::ARTH_OPERATOR)) {
				if (isCharValue(statement)) return true;
				else return false;
			}
			return true;
		}
	}
	statementIndex = bufferIndex;

	if (isTokenType(statement, Token::S_QUOTE) 
		&& isTokenType(statement, Token::IDENTIFIER)) {
		printf("hi\n");
		if (strlen(statement.tokens[statementIndex].token) == 1) {
			if (isTokenType(statement, Token::S_QUOTE)) {
				return true;
			}
		}	
		return false;
	}

	if (isIntValue(statement)) return true;

	return false;
}

bool Parser::endOfStatement(Statement &statement) {
	return (statement.tokens.size() <= statementIndex + 1);	
}
