#include "Compiler.h"

#include <iostream>

std::vector<int> Compiler::compileDeclaration(Statement &statement) {
	int varIndex = mem.createVariable(statement.tokens[1].token);
	bytecode.push_back(varIndex);
	bytecode.push_back(GSTORE);
	if (statement.tokens.size() > 2) compileValue(statement, 3);
	else {
		bytecode.push_back(0);
		bytecode.push_back(PUSH);
	}
	return bytecode;
}

void Compiler::compileValue(Statement &statement, int index) {
	if (statement.getToken(index).type == Token::NUMBER) {	
		compileValue(statement, index + 1);
		bytecode.push_back(StringUtil::atoi(statement.tokens[index].token));
		bytecode.push_back(PUSH);
	}

	if (statement.getToken(index).type == Token::OPERATOR) {
		switch (statement.getToken(index).subtype) {
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
		compileValue(statement, index + 1);	
	}

	if (statement.getToken(index).type == Token::PAREN) {
		compileValue(statement, index + 1);
	}
}
