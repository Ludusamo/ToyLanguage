#include <stdio.h>
#include <vector>

#include "FileReader.h"
#include "Statement.h"
#include "Parser.h"
#include "Compiler.h"

#include "ErrorHandler.h"

int main() {
	Memory mem;

	FileReader reader;
	reader.openFile("res/test.ls");

	Statement statement;
	std::vector<Statement> statements;
	statements.push_back(statement);

	for (int i = 0; i < 1; i++) {
		statements[i].setStatement(reader.getLine());
		statements[i].tokenizeStatement();
	}

	Parser parser;
	parser.parse(statements, mem);

	for (int i = 0; i < mem.globalFunctions.size(); i++) {
		printf("%i %s\n", i, mem.globalFunctions[i].id);
	}

	Compiler compiler;
	std::vector<int> bytecode = compiler.compile(statements, mem);

	printf("\nBytecode: \n");
	for (int i = 0; i < bytecode.size(); i++) {
		printf("%i\n", bytecode[i]);	
	}

	return 0;
}
