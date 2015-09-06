#include "Script.h"

#include "FileReader.h"
#include "stdio.h"

void Script::readScript(const char *path) {
	FileReader file;
	file.openFile(path);
	char *line = file.getLine();
	Statement statement;
	while (line != NULL) {
		scriptStatements.push_back(statement);
		scriptStatements[scriptStatements.size() - 1].calculateDepth(line);
		scriptStatements[scriptStatements.size() - 1].tokens = lex.tokenize(line);
		line = file.getLine();
	}
	printf("Completed Reading Script.\n");
	file.closeFile();
}

void Script::parse() {
	parser.parse(scriptStatements);
}

std::vector<int> Script::compile() {
	return compiler.compile(scriptStatements);
}
