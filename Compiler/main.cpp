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
	statements.push_back(statement);

	for (int i = 0; i < statements.size(); i++) {
		statements[i].setStatement(reader.getLine());
		statements[i].tokenizeStatement();
	}

	Parser parser;
	parser.parse(statements, mem);

	for (int i = 0; i < mem.globalFunctions.size(); i++) {
		printf("Function: %i, %s, %i\n", i, mem.globalFunctions[i].id, mem.globalFunctions[i].numArgs);
		for (int j = 0; j < mem.globalFunctions[i].numArgs; j++) {
			printf("Arg: %s", mem.globalFunctions[i].args[j].id);
		}
	}

	Compiler compiler;
	std::vector<int> bytecode = compiler.compile(statements, mem);

	printf("\nBytecode: \n");
	for (int i = 0; i < bytecode.size(); i++) {
		printf("%i\n", bytecode[i]);	
	}

	return 0;
}
