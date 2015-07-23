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
	Parser parser;
	parser.parse(statement, mem);

	Compiler compiler;
	std::vector<int> bytecode = compiler.compileDeclaration(statement, mem);

	printf("\n\n");
	statement.setStatement(reader.getLine());
	statement.tokenizeStatement();
	parser.parse(statement, mem);
	compiler.compileDeclaration(statement, mem);

	/*for (int i = bytecode.size() - 1; i != -1; i--) {
		printf("%i\n", bytecode[i]);
	}*/

	return 0;
}
