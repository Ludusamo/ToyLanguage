#include "Compiler.h"

#include <iostream>

std::vector<int> Compiler::compile(std::vector<Statement> &statements, Memory &mem) {
	bytecode.clear();
	for (int i = 0; i < statements.size(); i++) {
		switch(statements[i].type) {
		case Statement::DECL:
			compileGlobalDeclaration(statements[i], mem);
			break;
		case Statement::IF:
			compileIfStatement(statements[i], mem);
			break;
		}
	}
	return bytecode;
}

void Compiler::compileGlobalDeclaration(Statement &statement, Memory &mem) {
	// Creating a storing variable
	int varIndex = mem.getVariable(statement.getToken(1).token);
	bytecode.push_back(varIndex);
	bytecode.push_back(GSTORE);

	if (statement.tokens.size() > 2) {
		statementIndex = 2;
		switch (statement.getToken(0).subtype) {
		case Token::INT:	
			compileIntValue(statement, mem);
			break;
		case Token::BOOLEAN:
			compileBoolValue(statement, mem);
			break;
		}
	} else {
		bytecode.push_back(0);
		bytecode.push_back(PUSH);
	}
}

void Compiler::compileIfStatement(Statement &statement, Memory &mem) {
	
}

void Compiler::compileIntValue(Statement &statement, Memory &mem) {
	statementIndex++;
	if (statement.getToken(statementIndex).type == Token::NUMBER) {	
		int index = statementIndex;
		compileIntValue(statement, mem);
		bytecode.push_back(StringUtil::atoi(statement.tokens[index].token));
		bytecode.push_back(PUSH);
	}

	if (statement.getToken(statementIndex).type == Token::IDENTIFIER) {
		//bytecode.push_back(mem.getVariabl
	}

	if (statement.getToken(statementIndex).type == Token::ARTH_OPERATOR) {
		switch (statement.getToken(statementIndex).subtype) {
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
		compileIntValue(statement, mem);	
	}

	if (statement.getToken(statementIndex).type == Token::PAREN
		&& statement.getToken(statementIndex).subtype == Token::LPAREN) {
		int parenCount = 1;
		for (int i = statementIndex + 1; i < statement.tokens.size(); i++) {
			if (statement.getToken(i).type == Token::PAREN) {
				if (statement.getToken(i).subtype == Token::LPAREN) {
					parenCount++;
				}
				if (statement.getToken(i).subtype == Token::RPAREN) {	
					parenCount--;
					if (parenCount == 0)
						compileIntValue(statement, mem);
				}
			}
		}
		compileIntValue(statement, mem);
	}
}

void Compiler::compileBoolValue(Statement &statement, Memory &mem) {
	statementIndex++;
	if (statement.getToken(statementIndex).type == Token::NUMBER) {	
		int index = statementIndex;
		compileBoolValue(statement, mem);
		bytecode.push_back(StringUtil::atoi(statement.tokens[index].token));
		bytecode.push_back(PUSH);
	}

	if (statement.getToken(statementIndex).type == Token::BOOL) {
		compileBoolValue(statement, mem);
		int boolVal = StringUtil::equal(statement.getToken(statementIndex).token, "true") ? 1 : 0;
		bytecode.push_back(boolVal);
		bytecode.push_back(PUSH);
	}

	if (statement.getToken(statementIndex).type == Token::ARTH_OPERATOR) {
		switch (statement.getToken(statementIndex).subtype) {
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
		compileBoolValue(statement, mem);	
	}

	if (statement.getToken(statementIndex).type == Token::BOOL_OPERATOR) {
		printf("BOOL OP %i\n", statement.getToken(statementIndex).subtype);
		switch (statement.getToken(statementIndex).subtype) {
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
		compileBoolValue(statement, mem);	
	}

	if (statement.getToken(statementIndex).type == Token::PAREN
		&& statement.getToken(statementIndex).subtype == Token::LPAREN) {
		int parenCount = 1;
		for (int i = statementIndex + 1; i < statement.tokens.size(); i++) {
			if (statement.getToken(i).type == Token::PAREN) {
				if (statement.getToken(i).subtype == Token::LPAREN) {
					parenCount++;
				}
				if (statement.getToken(i).subtype == Token::RPAREN) {	
					parenCount--;
					if (parenCount == 0)
						compileBoolValue(statement, mem);
				}
			}
		}
		compileBoolValue(statement, mem);
	}
}
