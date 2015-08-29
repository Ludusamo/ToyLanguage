#include <stdio.h>
#include <vector>

#include "FileReader.h"
#include "Statement.h"
#include "Parser.h"
#include "Compiler.h"
#include "LexicalAnalyzer/LexicalAnalyzer.h"

#include "ErrorHandler.h"

int main() {
	FileReader reader;
	reader.openFile("res/test.ls");

	Statement statement;
	std::vector<Statement> statements;
	statements.push_back(statement);
	statements.push_back(statement);
	statements.push_back(statement);
	statements.push_back(statement);
	statements.push_back(statement);
	statements.push_back(statement);

	LexicalAnalyzer lex;
	for (int i = 0; i < statements.size(); i++) {
		const char *statement = reader.getLine();
		statements[i].calculateDepth(statement);
		statements[i].tokens = lex.tokenize(statement);
	}

	printf("==================\n");

	Parser parser;
	parser.parse(statements);

	printf("===================\n");

	Compiler compiler;
	std::vector<int> bytecode = compiler.compile(statements);

	printf("\nBytecode: \n");
	for (int i = 0; i < bytecode.size(); i++) {
		printf("%i\n", bytecode[i]);	
	}

	return 0;
}
