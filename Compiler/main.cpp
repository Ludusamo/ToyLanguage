#include "BitUtil.h"
#include "Parser.h"
#include "Statement.h"
#include "StringUtil.h"
#include <stdio.h>
#include <iostream>
#include "Token.h"
#include <vector>
#include "Debug.h"
#include "FileReader.h"
#include "Compiler.h"

int main() {
	FileReader reader;
	reader.openFile("res/test.ls");
	Statement statement;
	statement.setStatement(reader.getLine());
	statement.tokenizeStatement();
	printf("%s\n", statement.tokens[0].token);
	Parser parser;
	parser.parse(statement);

	Compiler compiler;
	std::vector<int> bytecode = compiler.compileDeclaration(statement);

	for (int i = bytecode.size() - 1; i != -1; i--) {
		printf("%i\n", bytecode[i]);
	}
	
	return 0;
}
