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
	statement.setStatement(reader.getLine());
	statement.tokenizeStatement();
	std::vector<Statement> statements;
	statements.push_back(statement);

	Parser parser;
	parser.parse(statements, mem);

	Compiler compiler;
	std::vector<int> bytecode = compiler.compile(statements, mem);

	printf("\nBytecode: \n");
	for (int i = bytecode.size() - 1; i >= 0; i--) {
		printf("%i\n", bytecode[i]);	
	}

	return 0;
}
