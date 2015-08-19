#include "Compiler.h"

#include <iostream>

std::vector<int> Compiler::compile(std::vector<Statement> &statements, Memory &mem) {
	if (lineno + 1 == statements.size()) return bytecode;
	lineno++;	
	switch(statements[lineno].type) {
	case Statement::DECL:
		compileGlobalDeclaration(statements[lineno], mem);
		break;
	case Statement::IF:
		int index = lineno;
		compileIfStatement(statements[index], mem);
		int initialBytecodeSize = bytecode.size(); // The index in bytecode where the if branch statement is
		while (statements[index].depth < statements[lineno + 1].depth) {
			compile(statements, mem);	
		}
		bytecode[placeholderIndex[placeholderIndex.size() - 1]] = bytecode.size() - initialBytecodeSize;
		placeholderIndex.pop_back();
		break;
	}
	compile(statements, mem);
	return bytecode;
}

void Compiler::compileGlobalDeclaration(Statement &statement, Memory &mem) {
	// Creating a storing variable
	int varIndex = mem.getVariable(statement.tokens[1].token, 0);	

	if (statement.tokens.size() > 2) {
		statementIndex = 2;
		switch (statement.tokens[0].subtype) {
		case Token::INT:	
			compileIntValue(statement, mem);
			break;
		case Token::BOOLEAN:
			compileBoolValue(statement, mem);
			break;
		}
	} else {
		bytecode.push_back(PUSH);
		bytecode.push_back(0);
	}
	bytecode.push_back(GSTORE);
	bytecode.push_back(varIndex);
}

void Compiler::compileGlobalFunction(Statement &statement, Memory &mem) {
	statementIndex = 0;
	
}

void Compiler::compileIfStatement(Statement &statement, Memory &mem) {
	statementIndex = 0;
	compileBoolValue(statement, mem);	
	bytecode.push_back(BRF);
	placeholderIndex.push_back(bytecode.size());
	bytecode.push_back(0);
}

void Compiler::compileIntValue(Statement &statement, Memory &mem) {
	if (statementIndex == statement.tokens.size() - 1) return;
	statementIndex++;
	if (statement.tokens[statementIndex].type == Token::NUMBER) {	
		bytecode.push_back(PUSH);
		bytecode.push_back(StringUtil::atoi(statement.tokens[statementIndex].token));
		compileIntValue(statement, mem);
		
	}

	if (statement.tokens[statementIndex].type == Token::IDENTIFIER) {
		bytecode.push_back(GLOAD);
		bytecode.push_back(mem.getVariable(statement.tokens[statementIndex].token, 0));
		compileIntValue(statement, mem);		
	}

	if (statement.tokens[statementIndex].type == Token::ARTH_OPERATOR) {
		int index = statementIndex;
		compileIntValue(statement, mem);	
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
						compileIntValue(statement, mem);
						statementIndex = bufferIndex;
					}
				}
			}
		}
		compileIntValue(statement, mem);
	}
}

void Compiler::compileBoolValue(Statement &statement, Memory &mem) {
	if (statementIndex == statement.tokens.size() - 1) return;
	statementIndex++;
	if (statement.tokens[statementIndex].type == Token::NUMBER) {	
		bytecode.push_back(PUSH);
		bytecode.push_back(StringUtil::atoi(statement.tokens[statementIndex].token));
		compileBoolValue(statement, mem);	
	}

	if (statement.tokens[statementIndex].type == Token::BOOL) {
		int boolVal = StringUtil::equal(statement.tokens[statementIndex].token, "true") ? 1 : 0;	
		bytecode.push_back(PUSH);
		bytecode.push_back(boolVal);
		compileBoolValue(statement, mem);
	}

	if (statement.tokens[statementIndex].type == Token::IDENTIFIER) {
		bytecode.push_back(GLOAD);
		bytecode.push_back(mem.getVariable(statement.tokens[statementIndex].token, 0));
		compileIntValue(statement, mem);	
	}

	if (statement.tokens[statementIndex].type == Token::ARTH_OPERATOR) {
		int index = statementIndex;
		compileBoolValue(statement, mem);	
		switch (statement.tokens[statementIndex].subtype) {
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
		compileBoolValue(statement, mem);	
		switch (statement.tokens[statementIndex].subtype) {
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
						compileBoolValue(statement, mem);
						statementIndex = bufferIndex;
					}
				}
			}
		}
		compileBoolValue(statement, mem);
	}
}
