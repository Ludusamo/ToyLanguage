#include <stdio.h>
#include <vector>

#include "FileReader.h"
#include "Statement.h"
#include "Parser.h"
#include "Compiler.h"

#include "ErrorHandler.h"

int main() {
	Memory mem;
	mem.createFunction("Test", 0, 0, 0);
	int index = mem.getFunction("Test");
	printf("%i\n", index);
	printf("%s\n", mem.globalFunctions[index].id);

	FileReader reader;
	reader.openFile("res/test.ls");

	Statement statement;
	std::vector<Statement> statements;
	statements.push_back(statement);
	statements.push_back(statement);
	statements.push_back(statement);
	statements.push_back(statement);

	for (int i = 0; i < 4; i++) {
		statements[i].setStatement(reader.getLine());
		statements[i].tokenizeStatement();
	}

	Parser parser;
	parser.parse(statements, mem);

	Compiler compiler;
	std::vector<int> bytecode = compiler.compile(statements, mem);

	printf("\nBytecode: \n");
	for (int i = 0; i < bytecode.size(); i++) {
		printf("%i\n", bytecode[i]);	
	}

	return 0;
}
