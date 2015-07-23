#include "Compiler.h"

#include <iostream>

std::vector<int> Compiler::compileDeclaration(Statement &statement, Memory &mem) {
	bytecode.clear();
	int varIndex = mem.createVariable(statement.tokens[1].token, statement.tokens[0].subtype);
	bytecode.push_back(varIndex);
	bytecode.push_back(GSTORE);
	if (statement.tokens.size() > 2) {
		switch (statement.getToken(0).subtype) {
		case Token::INT:	
			compileIntValue(statement, 3);
			break;
		case Token::BOOLEAN:
			compileBoolValue(statement, 3);
			break;
		}
	} else {
		bytecode.push_back(0);
		bytecode.push_back(PUSH);
	}
	return bytecode;
}

std::vector<int> Compiler::compileIfStatement(Statement &statement) {

}

void Compiler::compileIntValue(Statement &statement, int index) {
	if (statement.getToken(index).type == Token::NUMBER) {	
		compileIntValue(statement, index + 1);
		bytecode.push_back(StringUtil::atoi(statement.tokens[index].token));
		bytecode.push_back(PUSH);
	}

	if (statement.getToken(index).type == Token::ARTH_OPERATOR) {
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
		compileIntValue(statement, index + 1);	
	}

	if (statement.getToken(index).type == Token::PAREN
		&& statement.getToken(index).subtype == Token::LPAREN) {
		int parenCount = 1;
		for (int i = index + 1; i < statement.tokens.size(); i++) {
			if (statement.getToken(i).type == Token::PAREN) {
				if (statement.getToken(i).subtype == Token::LPAREN) {
					parenCount++;
				}
				if (statement.getToken(i).subtype == Token::RPAREN) {	
					parenCount--;
					if (parenCount == 0)
						compileIntValue(statement, i + 1);
				}
			}
		}
		compileIntValue(statement, index + 1);
	}
}

void Compiler::compileBoolValue(Statement &statement, int index) {
	if (statement.getToken(index).type == Token::NUMBER) {	
		compileBoolValue(statement, index + 1);
		bytecode.push_back(StringUtil::atoi(statement.tokens[index].token));
		bytecode.push_back(PUSH);
	}

	if (statement.getToken(index).type == Token::BOOL) {
		compileBoolValue(statement, index + 1);
		int boolVal = StringUtil::equal(statement.getToken(index).token, "true") ? 1 : 0;
		bytecode.push_back(boolVal);
		bytecode.push_back(PUSH);
	}

	if (statement.getToken(index).type == Token::ARTH_OPERATOR) {
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
		compileBoolValue(statement, index + 1);	
	}

	if (statement.getToken(index).type == Token::BOOL_OPERATOR) {
		printf("BOOL OP %i\n", statement.getToken(index).subtype);
		switch (statement.getToken(index).subtype) {
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
		compileBoolValue(statement, index + 1);	
	}

	if (statement.getToken(index).type == Token::PAREN
		&& statement.getToken(index).subtype == Token::LPAREN) {
		int parenCount = 1;
		for (int i = index + 1; i < statement.tokens.size(); i++) {
			if (statement.getToken(i).type == Token::PAREN) {
				if (statement.getToken(i).subtype == Token::LPAREN) {
					parenCount++;
				}
				if (statement.getToken(i).subtype == Token::RPAREN) {	
					parenCount--;
					if (parenCount == 0)
						compileBoolValue(statement, i + 1);
				}
			}
		}
		compileBoolValue(statement, index + 1);
	}
}
