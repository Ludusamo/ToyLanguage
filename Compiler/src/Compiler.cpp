#include "Compiler.h"

#include <iostream>

std::vector<int> Compiler::compile(std::vector<Statement> &statements) {
	if (lineno + 1 == statements.size()) return bytecode;
	lineno++;	
	currentDepth = statements[lineno].depth;
	
	int numLocalsPopped = mem.popVariableLayers(currentDepth, statements[lineno - 1].depth);
	for (int i = 0; i < numLocalsPopped; i++) {
		bytecode.push_back(POP);
	}

	int index = lineno;
	if (statements[lineno].depth < statements[lineno - 1].depth &&
		placeholderIndex.size() > 0) {
		bytecode[placeholderIndex[placeholderIndex.size() - 1]] = bytecode.size();
		placeholderIndex.pop_back();
	}

	switch(statements[lineno].type) {
	case Statement::DECL:
		compileDeclaration(statements[lineno]);
		break;
	case Statement::FUNC:
		compileGlobalFunction(statements[lineno]);
		while (statements[lineno + 1].depth >= currentDepth) {
			lineno++;
			currentDepth = statements[lineno].depth;
			if (statements[lineno].type == Statement::DECL)
				compileDeclaration(statements[lineno]);
			else if (statements[lineno].type == Statement::IF)
				compileIfStatement(statements[lineno]);
			else if (statements[lineno].type == Statement::RET)
				compileReturnStatement(statements[lineno], statements[index].tokens[0].subtype);
		}
		mem.returnVariables(statements[index].tokens[1].token);
		break;
	case Statement::IF:
		compileIfStatement(statements[lineno]);
		break;
	}
	compile(statements);
	return bytecode;
}

void Compiler::compileDeclaration(Statement &statement) {
	int varIndex = mem.createVariable(statement.tokens[1].token, statement.tokens[0].subtype, currentDepth);
	
	if (statement.tokens.size() > 2) {
		statementIndex = 2;
		switch (statement.tokens[0].subtype) {
		case Token::INT:	
			compileIntValue(statement);
			break;
		case Token::BOOLEAN:
			compileBoolValue(statement);
			break;
		}
	} else {
		bytecode.push_back(PUSH);
		bytecode.push_back(0);
	}

	// Store globally
	if (currentDepth == 0) {
		bytecode.push_back(GSTORE);
		bytecode.push_back(varIndex);
	}
}

void Compiler::compileGlobalFunction(Statement &statement) {
	Memory::Function f;
	f.id = statement.tokens[1].token;
	f.addr = bytecode.size();
	if (statement.tokens.size() > 4) {
		for (int i = 3; i < statement.tokens.size(); i+=3) {
			int addr = mem.createVariable(statement.tokens[i+1].token, statement.tokens[i].subtype, statement.depth + 1);
			bytecode.push_back(PUSH);
			bytecode.push_back(0);
		}
	}
	mem.addGlobalFunction(f);
}

void Compiler::compileReturnStatement(Statement &statement, int returnType) {
	statementIndex = 0;
	if (returnType == Token::VOID) {
		bytecode.push_back(PUSH);
		bytecode.push_back(0);
	} else if (returnType == Token::INT) {
		compileIntValue(statement);
	} else if (returnType == Token::BOOLEAN) {
		compileBoolValue(statement);
	}
	bytecode.push_back(RET);
}

void Compiler::compileIfStatement(Statement &statement) {
	statementIndex = 0;
	compileBoolValue(statement);	
	bytecode.push_back(BRF);
	placeholderIndex.push_back(bytecode.size());
	bytecode.push_back(0);
}

void Compiler::compileIntValue(Statement &statement) {
	if (statementIndex == statement.tokens.size() - 1) return;
	statementIndex++;
	if (statement.tokens[statementIndex].type == Token::NUMBER) {	
		bytecode.push_back(PUSH);
		bytecode.push_back(StringUtil::atoi(statement.tokens[statementIndex].token));
		compileIntValue(statement);	
	}

	if (statement.tokens[statementIndex].type == Token::IDENTIFIER) {
		bytecode.push_back(GLOAD);
		bytecode.push_back(mem.getVariable(statement.tokens[statementIndex].token, currentDepth));
		compileIntValue(statement);		
	}

	if (statement.tokens[statementIndex].type == Token::ARTH_OPERATOR) {
		int index = statementIndex;
		compileIntValue(statement);	
		switch (statement.tokens[index].subtype) {
		case Token::ADD:
			bytecode.push_back(ADDI);
			break;
		case Token::SUB:
			bytecode.push_back(SUBI);
			break;
		case Token::MUL:
			bytecode.push_back(MULI);
			break;
		case Token::DIV:
			bytecode.push_back(DIVI);
			break;
		}
	}

	if (statement.tokens[statementIndex].type == Token::PAREN
		&& statement.tokens[statementIndex].subtype == Token::LPAREN) {
		compileIntValue(statement);
		int parenCount = 1;
		for (int i = statementIndex + 1; i < statement.tokens.size(); i++) {
			if (statement.tokens[i].type == Token::PAREN) {	
				if (statement.tokens[i].subtype == Token::LPAREN) {
					parenCount++;
				}
				if (statement.tokens[i].subtype == Token::RPAREN) {	
					parenCount--;
					if (parenCount == 0) {
						int bufferIndex = statementIndex;
						statementIndex = i;
						statementIndex = bufferIndex;
					}
				}
			}
		}
		compileIntValue(statement);
	}
}

void Compiler::compileBoolValue(Statement &statement) {
	if (statementIndex == statement.tokens.size() - 1) return;
	statementIndex++;
	if (statement.tokens[statementIndex].type == Token::NUMBER) {	
		bytecode.push_back(PUSH);
		bytecode.push_back(StringUtil::atoi(statement.tokens[statementIndex].token));
		compileBoolValue(statement);	
	}

	if (statement.tokens[statementIndex].type == Token::BOOL) {
		int boolVal = StringUtil::equal(statement.tokens[statementIndex].token, "true") ? 1 : 0;	
		bytecode.push_back(PUSH);
		bytecode.push_back(boolVal);
		compileBoolValue(statement);
	}

	if (statement.tokens[statementIndex].type == Token::IDENTIFIER) {
		bytecode.push_back(GLOAD);
		bytecode.push_back(mem.getVariable(statement.tokens[statementIndex].token, currentDepth));
		compileIntValue(statement);	
	}

	if (statement.tokens[statementIndex].type == Token::ARTH_OPERATOR) {
		int index = statementIndex;
		compileBoolValue(statement);	
		switch (statement.tokens[index].subtype) {
		case Token::ADD:
			bytecode.push_back(ADDI);
			break;
		case Token::SUB:
			bytecode.push_back(SUBI);
			break;
		case Token::MUL:
			bytecode.push_back(MULI);
			break;
		case Token::DIV:
			bytecode.push_back(DIVI);
			break;
		}
	}

	if (statement.tokens[statementIndex].type == Token::BOOL_OPERATOR) {
		int index = statementIndex;
		compileBoolValue(statement);	
		switch (statement.tokens[index].subtype) {
		case Token::EQ:
			bytecode.push_back(EQ);
			break;
		case Token::LT:
			bytecode.push_back(LT);
			break;
		case Token::GT:
			bytecode.push_back(GT);
			break;
		case Token::LTEQ:
			bytecode.push_back(LTE);
			break;
		case Token::GTEQ:
			bytecode.push_back(GTE);
			break;
		}
	}

	if (statement.tokens[statementIndex].type == Token::PAREN
		&& statement.tokens[statementIndex].subtype == Token::LPAREN) {
		compileBoolValue(statement);
		int parenCount = 1;
		for (int i = statementIndex + 1; i < statement.tokens.size(); i++) {
			if (statement.tokens[statementIndex].type == Token::PAREN) {
				if (statement.tokens[i].subtype == Token::LPAREN) {
					parenCount++;
				}
				if (statement.tokens[i].subtype == Token::RPAREN) {	
					parenCount--;
					if (parenCount == 0) {
						int bufferIndex = statementIndex;
						statementIndex = i;
						statementIndex = bufferIndex;
					}
				}
			}
		}
		compileBoolValue(statement);
	}
}
