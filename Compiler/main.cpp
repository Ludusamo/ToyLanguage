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
	statements.push_back(statement);
	statements.push_back(statement);

	for (int i = 0; i < 4; i++) {
		statements[i].setStatement(reader.getLine());
		statements[i].tokenizeStatement();
	}

	Parser parser;
	parser.parse(statements, mem);

	printf("Num variables: %i\n", mem.variables.size());
	for (int i = 0; i < mem.variables.size(); i++) {
		printf("%s\n", mem.variables[i].id);
	}

	Compiler compiler;
	std::vector<int> bytecode = compiler.compile(statements, mem);

	printf("\nBytecode: \n");
	for (int i = bytecode.size() - 1; i >= 0; i--) {
		printf("%i\n", bytecode[i]);	
	}

	return 0;
}
